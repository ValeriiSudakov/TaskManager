cmake_minimum_required(VERSION 3.16)
project(TaskManager)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

include_directories(core)
include_directories(cli)


############## cli ########################################################
file(GLOB cli_CPP_SOURCES "cli/*.cpp" "cli/States/*.cpp" "cli/States/EditSystemStates/*.cpp"
        "cli/States/ShowStates/*.cpp" "cli/States/InputStates/*.cpp" "cli/StatesControllers/*.cpp"
        "cli/Factory/*.cpp" "cli/States/Menus/*.cpp")

file(GLOB cli_HEADERS "cli/*.h" "cli/States/*.h" "cli/States/EditSystemStates/*.h"
        "cli/States/ShowStates/*.h" "cli/States/InputStates/*.h" "cli/StatesControllers/*.h"
        "cli/Factory/*.h" "cli/States/Menus/*.h")

############## core ########################################################
file(GLOB core_CPP_SOURCES "core/API/*.cpp" "core/Date/*.cpp" "core/Memory_Model/*.cpp"
        "core/Memory_Model/Storage/*.cpp" "core/Memory_Model/Task/*.cpp"
        "core/Memory_Model/Storage/Serialize/Proto/*.cpp")

file(GLOB core_HEADERS "core/API/*.h" "core/Date/*.h" "core/Memory_Model/*.h"
        "core/Memory_Model/Storage/*.h" "core/Memory_Model/Task/*.h"
        "core/Memory_Model/Storage/Serialize/Proto/*.h")

############## tests ########################################################
file(GLOB core_TEST_SOURCES "tests/core/*.cpp")
file(GLOB cli_TEST_SOURCES "tests/cli/*.cpp")


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

############## protobuf ########################################################
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/core/Memory_Model/Storage/Serialize/Proto/*.proto )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})
message("Generated ${PROTO_SRCS} ${PROTO_HDRS}")

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

############## googletest ########################################################
include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

include_directories(tests)
add_executable(coreTests ${core_TEST_SOURCES} ${core_CPP_SOURCES}
        ${PROTO_SRCS} ${PROTO_HDRS})

add_executable(cliTests  ${core_TEST_SOURCES} ${core_CPP_SOURCES}
        ${cli_CPP_SOURCES}   ${cli_TEST_SOURCES}
        ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(coreTests GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        ${Protobuf_LIBRARIES})
gtest_discover_tests(coreTests)

target_link_libraries(cliTests GTest::GTest GTest::Main  ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        ${Protobuf_LIBRARIES})
gtest_discover_tests(cliTests)


############## main exe ########################################################

add_executable(TaskManager ${core_HEADERS} ${core_CPP_SOURCES}
                           ${cli_HEADERS} ${cli_CPP_SOURCES}
                           ${PROTO_SRCS} ${PROTO_HDRS}
                           main.cpp )

target_link_libraries(TaskManager ${Protobuf_LIBRARIES})

