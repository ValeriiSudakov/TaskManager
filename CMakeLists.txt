cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest)
add_executable(TaskManager main.cpp src/Task.cpp src/Task.h src/TaskEntity.cpp src/TaskEntity.h src/FullTask.cpp
        src/FullTask.h src/TaskService.cpp src/TaskService.h src/TaskID.cpp src/TaskID.h)
include_directories(src)

enable_testing()

add_executable(TestsExecutable tests/TestTask.cpp src/FullTask.cpp src/Task.cpp src/TaskEntity.cpp src/TaskService.cpp
        tests/TestTaskService.cpp)
target_link_libraries(TestsExecutable gtest gtest_main)
