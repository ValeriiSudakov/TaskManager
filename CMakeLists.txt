cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

add_executable(TaskManager main.cpp
        src/Memory_Model/Task/Task.cpp
        src/Memory_Model/Task/Task.h
        src/Memory_Model/Task/TaskEntity.cpp
        src/Memory_Model/Task/TaskEntity.h
        src/API/TaskService.cpp
        src/API/TaskService.h
        src/Memory_Model/Task/TaskID.cpp
        src/Memory_Model/Task/TaskID.h
        src/Memory_Model/Date/Date.cpp
        src/Memory_Model/Date/Date.h
        src/Memory_Model/Storage/TaskView.cpp
        src/Memory_Model/Storage/TaskView.h
        src/API/TaskDTO.cpp src/API/TaskDTO.h
        src/Memory_Model/Task/TaskIDGenerate.cpp
        src/Memory_Model/Task/TaskIDGenerate.h
        src/Memory_Model/Storage/TaskRepository.cpp
        src/Memory_Model/Storage/TaskRepository.h
        src/Memory_Model/Storage/TaskStorage.cpp
        src/Memory_Model/Storage/TaskStorage.h src/Memory_Model/Task/AddTaskResult.h)


#set(BOOST_ROOT "/home/valeriisudakov/Libs/boost/version.hpp")
#include_directories(${Boost_INCLUDE_DIR})

find_package(Boost 1.74.0 REQUIRED system)

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

include_directories(tests)
add_executable(TestsExe tests/TestTask.cpp
        src/Memory_Model/Task/Task.cpp
        src/Memory_Model/Task/TaskEntity.cpp
        src/API/TaskService.cpp
        tests/TestTaskService.cpp
        tests/TestTaskID.cpp
        src/Memory_Model/Task/TaskID.cpp
        src/Memory_Model/Date/Date.cpp
        src/Memory_Model/Storage/TaskView.cpp
        tests/TestDate.cpp
        tests/TestTaskView.cpp
        src/API/TaskDTO.cpp
        src/API/TaskDTO.h
        tests/TestTaskDTO.cpp
        src/Memory_Model/Task/TaskIDGenerate.cpp
        src/Memory_Model/Storage/TaskRepository.cpp
        src/Memory_Model/Storage/TaskStorage.cpp
        tests/TestTaskStorage.cpp
        tests/TestTaskRepository.cpp)

target_link_libraries(TestsExe GTest::GTest GTest::Main)
gtest_discover_tests(TestsExe)
