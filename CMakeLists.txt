cmake_minimum_required(VERSION 3.16)
project(TaskManager)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(core)
include_directories(cli)

############## cli ########################################################
file(GLOB_RECURSE cli_SOURCES "cli/*.cpp")
file(GLOB_RECURSE cli_HEADERS "cli/*.h")
############## core ########################################################
file(GLOB_RECURSE core_SOURCES "core/*.cpp")
file(GLOB_RECURSE core_HEADERS "core/*.h")
############## tests ########################################################
file(GLOB core_TEST_SOURCES "tests/core/*.cpp")
file(GLOB cli_TEST_SOURCES "tests/cli/*.cpp")
file(GLOB_RECURSE tests_MOCKS "tests/*.h")

############## protobuf ########################################################
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/Proto/*.proto )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})
message("Generated ${PROTO_SRCS} ${PROTO_HDRS}")

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

############## grpc ########################################################
# Since FetchContent uses add_subdirectory under the hood, we can use
# the grpc targets directly from this build.

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

# Proto file
get_filename_component(service_proto "Proto/TaskServiceTransport.proto" ABSOLUTE)
get_filename_component(service_proto_path "${service_proto}" PATH)

# Generated sources
set(service_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/TaskServiceTransport.pb.cc")
set(service_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/TaskServiceTransport.pb.h")
set(service_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/TaskServiceTransport.grpc.pb.cc")
set(service_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/TaskServiceTransport.grpc.pb.h")
add_custom_command(
        OUTPUT "${service_proto_srcs}" "${service_proto_hdrs}" "${service_grpc_srcs}" "${service_grpc_hdrs}"
        COMMAND protoc
        ARGS -I "${service_proto_path}"
        --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        ${service_proto}
        DEPENDS ${service_proto})

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

############## boost ########################################################
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.68.0 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

############## googletest ########################################################
include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

include_directories(tests)
add_executable(coreTests ${core_HEADERS} ${core_SOURCES} ${core_TEST_SOURCES} ${PROTO_SRCS}
                         ${PROTO_HDRS} ${service_proto_srcs} ${service_grpc_srcs})
add_executable(cliTests  ${core_HEADERS} ${core_SOURCES} ${cli_HEADERS} ${cli_SOURCES}
                         ${PROTO_SRCS} ${PROTO_HDRS}  ${tests_MOCKS} ${cli_TEST_SOURCES})
add_executable(allTests  ${core_HEADERS} ${core_SOURCES} ${cli_HEADERS} ${cli_SOURCES}
                         ${PROTO_SRCS} ${PROTO_HDRS}  ${tests_MOCKS} ${core_TEST_SOURCES} ${cli_TEST_SOURCES}
                         ${service_proto_srcs} ${service_grpc_srcs})

target_link_libraries(coreTests GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${Protobuf_LIBRARIES}
                         ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
gtest_discover_tests(coreTests)

target_link_libraries(cliTests GTest::GTest GTest::Main  ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
                         ${Protobuf_LIBRARIES} ${cli_TEST_MOCKS} )
gtest_discover_tests(cliTests)

target_link_libraries(allTests GTest::GTest GTest::Main  ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${Protobuf_LIBRARIES}
                         ${cli_TEST_MOCKS} ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
gtest_discover_tests(allTests)


############ Server #####################################################
add_executable(Server Server.cpp
        ${cli_SOURCES} ${cli_HEADERS}
        ${core_SOURCES} ${core_HEADERS}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${service_proto_srcs}
        ${service_grpc_srcs})

target_link_libraries(Server
        ${Protobuf_LIBRARIES}
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

############ Client #####################################################
add_executable(Client Client.cpp
        ${cli_HEADERS} ${cli_SOURCES}
        ${core_HEADERS} ${core_SOURCES}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${service_proto_srcs}
        ${service_grpc_srcs})

target_link_libraries(Client
        ${Protobuf_LIBRARIES}
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})
