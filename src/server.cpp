#include "pkg.grpc.pb.h"

#include "grpcpp/server.h"
#include "grpcpp/server_builder.h"

#include "fmt/core.h"

#include <thread>

class Service : public api::PackageManager::Service {
  grpc::Status GetInfo(grpc::ServerContext *context,
                       const api::PkgRequest *request,
                       api::PkgInfo *response) override {
    (void) context;
    fmt::print("Request package info for: {}\n", request->name());
    response->set_info("Not found: " + request->name());
    return grpc::Status::OK;
  }
};

int main(int argc, char* argv[]) {
  (void) argc;
  (void) argv;

  fmt::print("app: {}\nfmt version: {}\ngrpc version: {}\n",
             argv[0], FMT_VERSION, grpc_version_string());

  grpc::ServerBuilder builder;
  std::unique_ptr<grpc::Server> server;
  Service service;
  builder.AddListeningPort("localhost:50051", grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  server = builder.BuildAndStart();
  std::this_thread::sleep_for(std::chrono::seconds(10));
  server->Shutdown();

  return 0;
}
