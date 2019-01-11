#ifndef ANGRU_MAIL_H_
#define ANGRU_MAIL_H_

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace angru{
namespace wrapper{

class Mail
{
public:
    typedef std::function<void(bool, const std::string &)> SendCallback;

private:
    struct Impl;
    std::shared_ptr<Impl> m_pimpl;

public:
    Mail();
    Mail(const std::string &from, const std::string &to,
         const std::string &subject, const std::string &body,
         const std::vector<std::string> &attachments = {  });
    virtual ~Mail();

public:
    std::string GetFrom();
    std::string GetTo();
    std::string GetSubject();
    std::string GetBody();
    const std::vector<std::string> &GetAttachments();
    void SetFrom(const std::string &from);
    void SetTo(const std::string &to);
    void SetSubject(const std::string &subject);
    void SetBody(const std::string &body);
    void SetAttachments(const std::vector<std::string> &attachments);

    bool GetDeleteLater() const;
    void SetDeleteLater(const bool del) const;

public:
    bool Send() const;
    bool Send(std::string &out_error) const;

    void SendAsync(const SendCallback callback = nullptr);
};

} // wrapper
} // angru

#endif //ANGRU_MAIL_H_
