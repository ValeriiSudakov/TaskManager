enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
get_filename_component(GTEST_LIB_DIR ${GTEST_LIBRARY} DIRECTORY)
link_directories(${GTEST_LIB_DIR})

############## tests sources ########################################################
file(GLOB CORE_TEST_SOURCES "tests/core/*.cpp")
file(GLOB CLI_TEST_SOURCES "tests/cli/*.cpp")
file(GLOB_RECURSE CLI_TESTS_MOCKS "tests/*.h")

include_directories(tests)

############## core tests target ########################################################
file(GLOB CORE_TESTS_SOURCES ${core_SOURCES} ${CORE_TEST_SOURCES} ${PROTO_SRCS})

add_executable(coreTests ${CORE_TESTS_SOURCES})
target_include_directories(coreTests PRIVATE ${core_HEADERS})
target_link_libraries(coreTests gtest gtest_main
                                gRPC::grpc++ gRPC::grpc++_reflection
                                ${Protobuf_LIBRARIES} proto_files)

gtest_discover_tests(coreTests)

############## cli tests target ########################################################
file(GLOB CLI_TESTS_SOURCES ${core_SOURCES} ${cli_SOURCES} ${CLI_TEST_SOURCES} ${PROTO_SRCS})

add_executable(cliTests ${CLI_TESTS_SOURCES})
target_include_directories(cliTests PRIVATE ${core_HEADERS} ${cli_HEADERS} ${CLI_TESTS_MOCKS})
target_link_libraries(cliTests gtest gtest_main gmock
                               gRPC::grpc++ gRPC::grpc++_reflection
                               ${Protobuf_LIBRARIES} proto_files)

gtest_discover_tests(cliTests)

############## all tests target ########################################################
add_executable(allTests ${CORE_TESTS_SOURCES} ${CLI_TESTS_SOURCES})
target_include_directories(cliTests PRIVATE ${core_HEADERS} ${cli_HEADERS} ${CLI_TESTS_MOCKS})
target_link_libraries(allTests gtest gtest_main gmock
                               gRPC::grpc++ gRPC::grpc++_reflection
                               ${Protobuf_LIBRARIES} proto_files)
gtest_discover_tests(allTests)
