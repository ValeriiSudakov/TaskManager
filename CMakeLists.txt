cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(core)
include_directories(cli)

############## core ########################################################
file(GLOB core_CPP_SOURCES "core/API/*.cpp" "core/Date/*.cpp" "core/Memory_Model/*.cpp"
        "core/Memory_Model/Storage/*.cpp" "core/Memory_Model/Task/*.cpp")

file(GLOB core_HEADERS "core/API/*.h" "core/Date/*.h" "core/Memory_Model/*.h"
        "core/Memory_Model/Storage/*.h" "core/Memory_Model/Task/*.h")

############## cli ########################################################
file(GLOB cli_CPP_SOURCES "cli/*.cpp" "cli/States/*.cpp" "cli/States/EditSystemStates/*.cpp"
        "cli/States/ShowStates/*.cpp" "cli/States/InputStates/*.cpp" "cli/StatesControllers/*.cpp")

file(GLOB cli_HEADERS "cli/*.h" "cli/States/*.h" "cli/States/EditSystemStates/*.h"
        "cli/States/ShowStates/*.h" "cli/States/InputStates/*.h" "cli/StatesControllers/*.h")

############## tests ########################################################
file(GLOB core_TEST_SOURCES "tests/*.cpp")


add_executable(TaskManager ${core_HEADERS} ${core_CPP_SOURCES}
                           ${cli_HEADERS} ${cli_CPP_SOURCES}
                            main.cpp)

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
add_executable(coreTests ${core_TEST_SOURCES} ${core_CPP_SOURCES})

target_link_libraries(coreTests GTest::GTest GTest::Main)
gtest_discover_tests(coreTests)

