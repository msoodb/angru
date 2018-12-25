struct HelloHandler : public Pistache::Http::Handler {
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter writer) {
        writer.send(Pistache::Http::Code::Ok, "Hello, World!");
    }
};

try
{
  Pistache::Http::listenAndServe<HelloHandler>("*:9080");
}
catch(const angru::system::exception::error& e)
{
  std::cerr<<"Error: "<<e.what()<<std::endl;
  return 1;
}
catch(...)
{
  std::cerr<<"Error: unknown exception"<<std::endl;
  return 2;
}
