cmake_minimum_required(VERSION 3.30)
project(SnakeWKP C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "G:/SDL2-2.30.10-mingw/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(SnakeWKP main.c initSnake.c game.c draw.c file.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})