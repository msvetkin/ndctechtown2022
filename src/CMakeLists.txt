find_package(fmt CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)


add_library(api pkg.proto)

target_link_libraries(api
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

target_include_directories(api PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(_GRPC_PLUGIN_CPP gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET api LANGUAGE cpp)
protobuf_generate(TARGET api
  LANGUAGE grpc
  GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
  PLUGIN "protoc-gen-grpc=${_GRPC_PLUGIN_CPP}")

add_executable(client client.cpp)
target_link_libraries(client PRIVATE fmt::fmt api)

add_executable(server server.cpp)
target_link_libraries(server PRIVATE fmt::fmt api)
