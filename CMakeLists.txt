cmake_minimum_required(VERSION 3.16)
project(TaskManager)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(core)
include_directories(cli)


############## cli ########################################################
file(GLOB_RECURSE cli_CPP_SOURCES "cli/*.cpp")
file(GLOB_RECURSE cli_HEADERS "cli/*.h")
############## core ########################################################
file(GLOB_RECURSE core_CPP_SOURCES "core/*.cpp")
file(GLOB_RECURSE core_HEADERS "core/*.h")
############## tests ########################################################
file(GLOB core_TEST_SOURCES "tests/core/*.cpp")
file(GLOB cli_TEST_SOURCES "tests/cli/*.cpp")

############## protobuf ########################################################
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/Proto/*.proto )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})
message("Generated ${PROTO_SRCS} ${PROTO_HDRS}")

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

############## boost ########################################################
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.74.0 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

############## googletest ########################################################
include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

include_directories(tests)
add_executable(coreTests ${core_TEST_SOURCES} ${core_CPP_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(cliTests  ${core_TEST_SOURCES} ${core_CPP_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS}
        ${cli_CPP_SOURCES}   ${cli_TEST_SOURCES})

target_link_libraries(coreTests GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${Protobuf_LIBRARIES})
gtest_discover_tests(coreTests)

target_link_libraries(cliTests GTest::GTest GTest::Main  ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${Protobuf_LIBRARIES})
gtest_discover_tests(cliTests)

############## main exe ########################################################

add_executable(TaskManager ${core_HEADERS} ${core_CPP_SOURCES}
        ${cli_HEADERS} ${cli_CPP_SOURCES}
        ${PROTO_SRCS} ${PROTO_HDRS}
        main.cpp )

target_link_libraries(TaskManager ${Protobuf_LIBRARIES})
