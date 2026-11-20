cmake_minimum_required(VERSION 3.21)

project(AutoManage2 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_library(automanage2 STATIC automanage2.c)
target_include_directories(automanage2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test testMain.c)
target_link_libraries(test PRIVATE automanage2)