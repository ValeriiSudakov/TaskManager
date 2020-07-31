cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest)
add_executable(TaskManager main.cpp "src/Memory Model/Task.cpp" "src/Memory Model/Task.h" "src/Memory Model/TaskEntity.cpp" "src/Memory Model/TaskEntity.h"
        src/API/TaskService.cpp src/API/TaskService.h "src/Memory Model/TaskID.cpp" "src/Memory Model/TaskID.h" "src/Memory Model/Date.cpp" "src/Memory Model/Date.h"
        src/API/TaskView.cpp src/API/TaskView.h src/API/TaskDTO.cpp src/API/TaskDTO.h src/API/TaskIDGenerate.cpp src/API/TaskIDGenerate.h
        src/API/TaskRepository.cpp src/API/TaskRepository.h)
include_directories(src)

enable_testing()

add_executable(TestsExecutable tests/TestTask.cpp "src/Memory Model/Task.cpp" "src/Memory Model/TaskEntity.cpp" src/API/TaskService.cpp
        tests/TestTaskService.cpp tests/TestTaskID.cpp "src/Memory Model/TaskID.cpp" "src/Memory Model/Date.cpp" src/API/TaskView.cpp
        tests/TestDate.cpp tests/TestTaskView.cpp src/API/TaskDTO.cpp src/API/TaskDTO.h tests/TestTaskDTO.cpp
        src/API/TaskIDGenerate.cpp src/API/TaskIDGenerate.h src/API/TaskRepository.cpp tests/TestTaskRepository.cpp)
target_link_libraries(TestsExecutable gtest gtest_main)
