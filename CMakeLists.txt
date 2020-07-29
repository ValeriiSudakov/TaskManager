cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest)
add_executable(TaskManager main.cpp src/Task.cpp src/Task.h src/TaskEntity.cpp src/TaskEntity.h
        src/TaskService.cpp src/TaskService.h src/TaskID.cpp src/TaskID.h src/Date.cpp src/Date.h src/TaskOutput.cpp src/TaskOutput.h src/TaskView.cpp src/TaskView.h src/TaskDTO.cpp src/TaskDTO.h)
include_directories(src)

enable_testing()

add_executable(TestsExecutable tests/TestTask.cpp src/Task.cpp src/TaskEntity.cpp src/TaskService.cpp
        tests/TestTaskService.cpp tests/TestTaskID.cpp src/TaskID.cpp src/Date.cpp src/TaskView.cpp tests/TestDate.cpp src/TaskOutput.cpp tests/TestTaskView.cpp src/TaskDTO.cpp src/TaskDTO.h tests/TestTaskDTO.cpp)
target_link_libraries(TestsExecutable gtest gtest_main)
