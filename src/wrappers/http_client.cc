#include "wrappers/http_client.h"

#include <iostream>
#include <string>

#include "tools/system.h"

using namespace Pistache;
using namespace Pistache::Http;

namespace angru{
namespace wrapper{

void HttpClient::Setup(){
}
void HttpClient::Get(std::string const page, std::string& body, Pistache::Http::Code &code){

    //page = "http://api.timezonedb.com/v2.1/get-time-zone?key=97IQ2W4BJCT5&format=json&by=zone&zone=America/Chicago";
    //page = "http://51.68.208.142/data.json";

    Http::Client client;

    auto opts = Http::Client::options()
        .threads(1)
        .maxConnectionsPerHost(8);
    client.init(opts);

    std::vector<Async::Promise<Http::Response>> responses;
    std::atomic<size_t> completedRequests(0);
    std::atomic<size_t> failedRequests(0);

    //auto start = std::chrono::system_clock::now();
    std::cout << page << '\n';
    auto resp = client.get(page).send();
    std::cout << "1" << '\n';
      resp.then([&](Http::Response response) {
          code = response.code();
          if(code == Pistache::Http::Code::Ok)
            body = response.body();
      }, Async::IgnoreException);
      responses.push_back(std::move(resp));

    auto sync = Async::whenAll(responses.begin(), responses.end());
    Async::Barrier<std::vector<Http::Response>> barrier(sync);
    barrier.wait_for(std::chrono::seconds(5));

    client.shutdown();
}

} // wrapper
} // angru

/*std::string page = "http://api.timezonedb.com/v2.1/get-time-zone?key=97IQ2W4BJCT5&format=json&by=zone&zone=America/Chicago";
std::string body="";
Pistache::Http::Code code;
HTTP_Client::get(page, body, code);
std::cout << body << '\n';
return 1;*/

/*int HTTP_Client::sampledo(int argc, char const *argv[])
{
  if (argc < 2) {
        std::cerr << "Usage: http_client page [count]" << std::endl;
        return 1;
    }

    std::string page = argv[1];
    //page = "http://api.timezonedb.com/v2.1/get-time-zone?key=97IQ2W4BJCT5&format=json&by=zone&zone=America/Chicago";
    page = "http://51.68.208.142/data.json";
    int count = 5;
    if (argc == 3) {
        count = std::stoi(argv[2]);
    }

    Http::Client client;

    auto opts = Http::Client::options()
        .threads(1)
        .maxConnectionsPerHost(8);
    client.init(opts);

    std::vector<Async::Promise<Http::Response>> responses;
    std::atomic<size_t> completedRequests(0);
    std::atomic<size_t> failedRequests(0);

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < count; ++i) {
      std::cout << page << '\n';
        auto resp = client.get(page).cookie(Http::Cookie("FOO", "bar")).send();
        resp.then([&](Http::Response response) {
                ++completedRequests;
            std::cout << "Response code = " << response.code() << std::endl;
            auto body = response.body();
            if (!body.empty())
               std::cout << "Response body = " << body << std::endl;
        }, Async::IgnoreException);
        responses.push_back(std::move(resp));
    }
    auto sync = Async::whenAll(responses.begin(), responses.end());
    Async::Barrier<std::vector<Http::Response>> barrier(sync);
    barrier.wait_for(std::chrono::seconds(5));

    auto end = std::chrono::system_clock::now();

    std::cout << "Summary of execution" << std::endl
              << "Total number of requests sent     : " << count << std::endl
              << "Total number of responses received: " << completedRequests.load() << std::endl
              << "Total number of requests failed   : " << failedRequests.load() << std::endl
              << "Total time of execution           : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
  client.shutdown();
}*/

/*
//std::string page = "http://api.timezonedb.com/v2.1/get-time-zone?key=97IQ2W4BJCT5&format=json&by=zone&zone=America/Chicago";
std::string page = "https://www.mp3juices.cc/";
std::string body;
Pistache::Http::Code code;
HTTP_Client::get(page, body, code);
std::cout << code << '\n';
*/
