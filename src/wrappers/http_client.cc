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
    int count =1;
    Http::Client client;

    auto opts = Http::Client::options()
        .threads(1)
        .maxConnectionsPerHost(8);
    client.init(opts);
    auto resp = client.get("http://httpbin.org/get").send();
    std::cout << "2" << '\n';

    std::vector<Async::Promise<Http::Response>> responses;

    std::atomic<size_t> completedRequests(0);
    std::atomic<size_t> failedRequests(0);

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < count; ++i) {
        resp = client.get(page).cookie(Http::Cookie("FOO", "bar")).send();
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
}

} // wrapper
} // angru
