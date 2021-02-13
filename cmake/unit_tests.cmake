enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
get_filename_component(GTEST_LIB_DIR ${GTEST_LIBRARY} DIRECTORY)
link_directories(${GTEST_LIB_DIR})

include_directories(tests)
add_executable(coreTests ${core_SOURCES} ${core_TEST_SOURCES} ${PROTO_SRCS}  ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(coreTests PRIVATE ${core_HEADERS} ${PROTO_HDRS})
target_link_libraries(coreTests GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)
gtest_discover_tests(coreTests)

add_executable(cliTests ${core_SOURCES} ${cli_SOURCES} ${cli_TEST_SOURCES} ${PROTO_SRCS} ${tests_MOCKS}
        ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(cliTests PRIVATE ${core_HEADERS} ${cli_HEADERS} ${PROTO_HDRS})
target_link_libraries(cliTests GTest::GTest GTest::Main  ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        ${cli_TEST_MOCKS} gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)
gtest_discover_tests(cliTests)

add_executable(allTests ${core_SOURCES} ${cli_SOURCES} ${PROTO_SRCS} ${tests_MOCKS} ${core_TEST_SOURCES} ${cli_TEST_SOURCES}
        ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(cliTests PRIVATE ${core_HEADERS} ${cli_HEADERS} ${PROTO_HDRS} ${core_HEADERS} ${cli_HEADERS} ${PROTO_HDRS})
target_link_libraries(allTests GTest::GTest GTest::Main  ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        ${cli_TEST_MOCKS} gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)
gtest_discover_tests(allTests)
