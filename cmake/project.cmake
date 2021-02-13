include_directories(core)
include_directories(cli)

############## cli ########################################################
file(GLOB_RECURSE cli_SOURCES "cli/*.cpp")
file(GLOB_RECURSE cli_HEADERS "cli/*.h")
############## core ########################################################
file(GLOB_RECURSE core_SOURCES "core/*.cpp")
file(GLOB_RECURSE core_HEADERS "core/*.h")

############ Server #####################################################
add_executable(Server Server.cpp ${cli_SOURCES} ${core_SOURCES} ${PROTO_SRCS} ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(Server PRIVATE ${cli_HEADERS} ${core_HEADERS} ${PROTO_HDRS})
target_link_libraries(Server gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)

############ Client #####################################################
add_executable(Client Client.cpp ${cli_SOURCES} ${core_SOURCES} ${PROTO_SRCS} ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(Client PRIVATE ${cli_HEADERS} ${core_HEADERS} ${PROTO_HDRS})
target_link_libraries(Client gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)