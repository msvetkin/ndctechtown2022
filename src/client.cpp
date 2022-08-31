#include "pkg.grpc.pb.h"

#include "grpc/grpc.h"
#include "grpcpp/create_channel.h"

#include "fmt/core.h"

int main(int argc, char* argv[]) {
  (void) argc;
  (void) argv;

  fmt::print("app: {}\nfmt version: {}\ngrpc version: {}\n",
             argv[0], FMT_VERSION, grpc_version_string());

  api::PkgRequest request;
  api::PkgInfo response;
  request.set_name("fmt");

  auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
  std::unique_ptr<api::PackageManager::Stub> stub = api::PackageManager::NewStub(channel);
  grpc::ClientContext context;
  grpc::Status status = stub->GetInfo(&context, request, &response);

  fmt::print("status: [{}]\n",  status.ok());

  if (status.ok()) {
    fmt::print("response: {}\n",  response.info());
  }

  return 0;
}
