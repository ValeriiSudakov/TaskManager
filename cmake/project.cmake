include_directories(${SRC_ROOT}/cli)
include_directories(${SRC_ROOT}/core)

############## cli ########################################################
file(GLOB_RECURSE cli_SOURCES "${SRC_ROOT}/cli/*.cpp")
file(GLOB_RECURSE cli_HEADERS "${SRC_ROOT}/cli/*.h")
############## core ########################################################
file(GLOB_RECURSE core_SOURCES "${SRC_ROOT}/core/*.cpp")
file(GLOB_RECURSE core_HEADERS "${SRC_ROOT/}core/*.h")

############ Server #####################################################
add_executable(Server ${SRC_ROOT}/Server.cpp ${cli_SOURCES} ${core_SOURCES} ${PROTO_SRCS} ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(Server PRIVATE ${cli_HEADERS} ${core_HEADERS} ${PROTO_HDRS})
target_link_libraries(Server gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)

############ Client #####################################################
add_executable(Client ${SRC_ROOT}/Client.cpp ${cli_SOURCES} ${core_SOURCES} ${PROTO_SRCS} ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(Client PRIVATE ${cli_HEADERS} ${core_HEADERS} ${PROTO_HDRS})
target_link_libraries(Client gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)