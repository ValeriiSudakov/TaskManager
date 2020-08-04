cmake_minimum_required(VERSION 3.16)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(TaskManager main.cpp "src/Memory Model/Task.cpp" "src/Memory Model/Task.h" "src/Memory Model/TaskEntity.cpp"
        "src/Memory Model/TaskEntity.h" src/API/TaskService.cpp src/API/TaskService.h "src/Memory Model/TaskID.cpp"
        "src/Memory Model/TaskID.h" "src/Memory Model/Date.cpp" "src/Memory Model/Date.h" "src/Memory Model/TaskView.cpp"
        "src/Memory Model/TaskView.h" src/API/TaskDTO.cpp src/API/TaskDTO.h "src/Memory Model/TaskIDGenerate.cpp"
        "src/Memory Model/TaskIDGenerate.h" "src/Memory Model/TaskRepository.cpp" "src/Memory Model/TaskRepository.h"
        "src/Memory Model/TaskStorage.cpp" "src/Memory Model/TaskStorage.h")

#set(BOOST_ROOT "D:/c++/libs/boost")
#include_directories(${Boost_INCLUDE_DIR})

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

include_directories(tests)
add_executable(TestsExe tests/TestTask.cpp "src/Memory Model/Task.cpp" "src/Memory Model/TaskEntity.cpp"
        src/API/TaskService.cpp tests/TestTaskService.cpp tests/TestTaskID.cpp "src/Memory Model/TaskID.cpp"
        "src/Memory Model/Date.cpp" "src/Memory Model/TaskView.cpp" tests/TestDate.cpp tests/TestTaskView.cpp src/API/TaskDTO.cpp
        src/API/TaskDTO.h tests/TestTaskDTO.cpp "src/Memory Model/TaskIDGenerate.cpp"
        "src/Memory Model/TaskRepository.cpp " "src/Memory Model/TaskStorage.cpp"
        tests/TestTaskStorage.cpp tests/TestTaskRepository.cpp)

target_link_libraries(TestsExe GTest::GTest GTest::Main)
gtest_discover_tests(TestsExe)
