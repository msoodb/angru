#include "wrappers/http_client.h"

#include <iostream>
#include <string>

#include "tools/system.h"

using namespace Pistache;
using namespace Pistache::Http;

namespace angru{
namespace wrapper{

void HttpClient::Setup(){
  //std::string page="http://api.timezonedb.com:80/v2.1/get-time-zone";
  std::string page="http://jsonplaceholder.typicode.com:80/todos/1";
  Pistache::Http::Uri::Query query;
  query.add("key","97IQ2W4BJCT5");
  query.add("format","json");
  query.add("by","zone");
  query.add("zone","America/Chicago");
  //std::string body;
  Pistache::Http::Code code;

  int count = 1;

  Pistache::Http::Client client;

  auto opts = Pistache::Http::Client::options()
      .threads(1)
      .maxConnectionsPerHost(8);
  client.init(opts);
  std::vector<Pistache::Async::Promise<Pistache::Http::Response>> responses;

  std::atomic<size_t> completedRequests(0);
  std::atomic<size_t> failedRequests(0);

  auto start = std::chrono::system_clock::now();

  for (int i = 0; i < count; ++i) {
      auto resp = client.get(page).cookie(Pistache::Http::Cookie("FOO", "bar")).send();
      resp.then([&](Pistache::Http::Response response) {
              ++completedRequests;
          std::cout << "Response code = " << response.code() << std::endl;
          auto body = response.body();
          if (!body.empty())
             std::cout << "Response body = " << body << std::endl;
      }, Pistache::Async::IgnoreException);
      responses.push_back(std::move(resp));
  }

  auto sync = Pistache::Async::whenAll(responses.begin(), responses.end());
  Pistache::Async::Barrier<std::vector<Pistache::Http::Response>> barrier(sync);

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
void HttpClient::Get(std::string page, std::string body, Pistache::Http::Code code){
}

} // wrapper
} // angru
