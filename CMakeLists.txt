cmake_minimum_required(VERSION 3.16)
project(TaskManager)
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/libs.cmake)
include(cmake/proto.cmake)
include(cmake/project.cmake)
include(cmake/unit_tests.cmake)

