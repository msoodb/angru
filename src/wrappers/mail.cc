#include "wrappers/mail.h"

#include <iostream>
#include <chrono>
#include <queue>

#include <boost/bind.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>
#include <vmime/base.hpp>
#include "tools/log.h"
#include "tools/make_unique.h"


#define WORKER_THREAD_STOP_IDLE_MILLISECONDS        10000.0
#define UNKNOWN_ERROR                               "Unknown error!"

namespace angru{
namespace wrapper{


using namespace std;

struct Mail::Impl
{
public:
    static std::queue<Mail *> MailQueue;
    static std::queue<Mail::SendCallback> MailCallbackQueue;
    static bool WorkerThreadIsRunning;
    static boost::mutex MailMutex;
    static boost::mutex WorkerMutex;
    static std::unique_ptr<boost::thread> WorkerThread;

public:
    static void DoWork();

public:
    std::string From;
    std::string To;
    std::string Subject;
    std::string Body;
    std::vector<std::string> Attachments;

    bool DeleteLater;

public:
    Impl();
    ~Impl();
};

std::queue<Mail *> Mail::Impl::MailQueue;
std::queue<Mail::SendCallback> Mail::Impl::MailCallbackQueue;
bool Mail::Impl::WorkerThreadIsRunning = false;
boost::mutex Mail::Impl::MailMutex;
boost::mutex Mail::Impl::WorkerMutex;
std::unique_ptr<boost::thread> Mail::Impl::WorkerThread;

void Mail::Impl::DoWork()
{
    LOG_INFO << "Mail worker thread started";

    try {
        auto lastJobTime = std::chrono::high_resolution_clock::now();

        bool isMailQueueEmpty = false;
        Mail *mail = nullptr;
        Mail::SendCallback callback = nullptr;

        for (;;) {
            boost::this_thread::interruption_point();

            {
                boost::lock_guard<boost::mutex> lock(WorkerMutex);
                (void)lock;

                if (!WorkerThreadIsRunning)
                    break;
            }

            boost::this_thread::disable_interruption di;

            {
                boost::lock_guard<boost::mutex> lock(MailMutex);
                (void)lock;

                isMailQueueEmpty = !(MailQueue.size() > 0);

                if (!isMailQueueEmpty) {
                    mail = MailQueue.front();
                    callback = MailCallbackQueue.front();
                }
            }

            if (!isMailQueueEmpty) {
                std::string error;
                bool rc = mail->Send(error);
                if (callback != nullptr) {
                    callback(rc, error);
                }

                {
                    boost::lock_guard<boost::mutex> lock(MailMutex);
                    (void)lock;

                    MailQueue.pop();
                    MailCallbackQueue.pop();
                }

                if (mail->GetDeleteLater()) {
                    delete mail;
                }

                lastJobTime = std::chrono::high_resolution_clock::now();
            }

            boost::this_thread::restore_interruption ri(di);
            (void)ri;
            boost::this_thread::interruption_point();

            boost::this_thread::sleep_for(boost::chrono::nanoseconds(1));

            if (isMailQueueEmpty) {
                if ((std::chrono::duration<double, std::milli>(
                         std::chrono::high_resolution_clock::now() - lastJobTime)).count() // elapsed in milliseconds
                        > WORKER_THREAD_STOP_IDLE_MILLISECONDS) {
                    {
                        boost::lock_guard<boost::mutex> lock(WorkerMutex);
                        (void)lock;

                        WorkerThreadIsRunning = false;
                        break;
                    }
                }
            }
        }
    }

    catch (boost::exception &ex) {
        LOG_ERROR << boost::diagnostic_information(ex);
    }

    catch (std::exception &ex) {
        LOG_ERROR << ex.what();
    }

    catch (...) {
        LOG_ERROR << UNKNOWN_ERROR;
    }

    LOG_INFO <<"Mail worker thread stopped";
}

Mail::Mail()
    : m_pimpl(std::make_shared<Mail::Impl>())
{

}

Mail::Mail(const std::string &from, const std::string &to,
           const std::string &subject, const std::string &body,
           const std::vector<std::string> &attachments)
    : m_pimpl(std::make_shared<Mail::Impl>())
{
    m_pimpl->From = from;
    m_pimpl->To = to;
    m_pimpl->Subject = subject;
    m_pimpl->Body = body;
    SetAttachments(attachments);
}

Mail::~Mail() = default;

std::string Mail::GetFrom(){
    return m_pimpl->From;
}

std::string Mail::GetTo(){
    return m_pimpl->To;
}

std::string Mail::GetSubject(){
    return m_pimpl->Subject;
}

std::string Mail::GetBody(){
    return m_pimpl->Body;
}

const std::vector<std::string> &Mail::GetAttachments(){
    return m_pimpl->Attachments;
}

void Mail::SetFrom(const std::string &from){
    m_pimpl->From = from;
}

void Mail::SetTo(const std::string &to){
    m_pimpl->To = to;
}

void Mail::SetSubject(const std::string &subject){
    m_pimpl->Subject = subject;
}

void Mail::SetBody(const std::string &body){
    m_pimpl->Body = body;
}

void Mail::SetAttachments(const std::vector<std::string> &attachments){
    m_pimpl->Attachments.clear();
    for (auto a : attachments) {
        m_pimpl->Attachments.push_back(a);
    }
}

bool Mail::GetDeleteLater() const{
    return m_pimpl->DeleteLater;
}

void Mail::SetDeleteLater(const bool del) const{
    m_pimpl->DeleteLater = del;
}

bool Mail::Send() const{
    std::string err;
    return Send(err);
}

bool Mail::Send(std::string &out_error) const{
    try {
        vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
        vmime::messageBuilder mb;

        mb.setExpeditor(vmime::mailbox(m_pimpl->From));
        mb.getRecipients().appendAddress(vmime::make_shared<vmime::mailbox>(m_pimpl->To));

        mb.setSubject(*vmime::text::newFromString(m_pimpl->Subject, vmime::charsets::UTF_8));

        mb.constructTextPart(vmime::mediaType(vmime::mediaTypes::TEXT, vmime::mediaTypes::TEXT_HTML));
        mb.getTextPart()->setCharset(vmime::charsets::UTF_8);
        mb.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(m_pimpl->Body));

        if (m_pimpl->Attachments.size() > 0) {
            for (auto a : m_pimpl->Attachments) {
                vmime::shared_ptr <vmime::attachment> att = vmime::make_shared <vmime::fileAttachment>
                        (a, vmime::mediaType("application/octet-stream"),
                         vmime::text(filesystem::path(a).stem().string()));
                mb.appendAttachment(att);
            }
        }

        vmime::shared_ptr<vmime::message> msg = mb.construct();

        vmime::utility::url url("smtp://localhost");
#if VMIME_API_MODE == VMIME_LEGACY_API
        vmime::shared_ptr<vmime::net::session> sess = vmime::make_shared<vmime::net::session>();
#else
        vmime::shared_ptr<vmime::net::session> sess = vmime::net::session::create();
#endif  // VMIME_API_MODE == VMIME_LEGACY_API
        vmime::shared_ptr<vmime::net::transport> tr = sess->getTransport(url);

        tr->connect();
        tr->send(msg);
        tr->disconnect();

        return true;
    }

    catch (vmime::exception &ex) {
        out_error.assign(ex.what());
    }

    catch(std::exception &ex) {
        out_error.assign(ex.what());
    }

    catch (...) {
        out_error.assign(UNKNOWN_ERROR);
    }

    return false;
}

void Mail::SendAsync(const SendCallback callback)
{
    try {
        {
            boost::lock_guard<boost::mutex> lock(Impl::MailMutex);
            (void)lock;

            Impl::MailQueue.push(this);
            Impl::MailCallbackQueue.push(callback);
        }

        {
            boost::lock_guard<boost::mutex> lock(Impl::WorkerMutex);
            (void)lock;

            if (!Impl::WorkerThreadIsRunning) {
                Impl::WorkerThreadIsRunning = true;

                Impl::WorkerThread = angru::system::make_unique<boost::thread>(Mail::Impl::DoWork);
                Impl::WorkerThread->detach();
            }
        }
    }

    catch (boost::exception &ex) {
        LOG_ERROR << boost::diagnostic_information(ex);
    }

    catch (std::exception &ex) {
        LOG_ERROR << ex.what();
    }

    catch (...) {
        LOG_ERROR << UNKNOWN_ERROR;
    }
}

Mail::Impl::Impl()
    : DeleteLater(false)
{

}

Mail::Impl::~Impl() = default;

} // wrapper
} // angru
