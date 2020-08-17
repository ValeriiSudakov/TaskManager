cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(core)

add_executable(TaskManager main.cpp
        core/Memory_Model/Task/Task.cpp
        core/Memory_Model/Task/Task.h
        core/Memory_Model/Task/TaskEntity.cpp
        core/Memory_Model/Task/TaskEntity.h
        core/API/TaskService.cpp
        core/API/TaskService.h
        core/API/TaskID.cpp
        core/API/TaskID.h
        core/Date/Date.cpp
        core/Date/Date.h
        core/Memory_Model/Storage/TaskView.cpp
        core/Memory_Model/Storage/TaskView.h
        core/API/TaskDTO.cpp core/API/TaskDTO.h
        core/Memory_Model/Task/TaskIDGenerate.cpp
        core/Memory_Model/Task/TaskIDGenerate.h
        core/Memory_Model/Storage/TaskRepository.cpp
        core/Memory_Model/Storage/TaskRepository.h
        core/Memory_Model/Storage/TaskStorage.cpp
        core/Memory_Model/Storage/TaskStorage.h
        core/API/AddTaskResult.h core/API/Priority.h
        core/Memory_Model/Storage/TaskRepositoryInterface.h
        core/Memory_Model/Storage/TaskStorageInterface.h
        core/Memory_Model/Storage/TaskViewInterface.h core/Convertor.h core/Convertor.cpp)



set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.74.0 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

include_directories(tests)
add_executable(TestsExe tests/TestTask.cpp
        core/Memory_Model/Task/Task.cpp
        core/Memory_Model/Task/TaskEntity.cpp
        core/API/TaskService.cpp
        tests/TestTaskService.cpp
        tests/TestTaskID.cpp
        core/API/TaskID.cpp
        core/Date/Date.cpp
        core/Memory_Model/Storage/TaskView.cpp
        tests/TestDate.cpp
        tests/TestTaskView.cpp
        core/API/TaskDTO.cpp
        core/API/TaskDTO.h
        tests/TestTaskDTO.cpp
        core/Memory_Model/Task/TaskIDGenerate.cpp
        core/Memory_Model/Storage/TaskRepository.cpp
        core/Memory_Model/Storage/TaskStorage.cpp
        tests/TestTaskStorage.cpp
        tests/TestTaskRepository.cpp core/Convertor.cpp tests/TestConvertor.cpp)

target_link_libraries(TestsExe GTest::GTest GTest::Main)
gtest_discover_tests(TestsExe)
