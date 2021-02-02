cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Evolution)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(SimulatedEvolution src/main.cpp src/evolution.cpp src/controller.cpp src/renderer.cpp src/microbe.cpp src/gene.cpp)
target_link_libraries(SimulatedEvolution Threads::Threads)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SimulatedEvolution ${SDL2_LIBRARIES})










