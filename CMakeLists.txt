cmake_minimum_required(VERSION 3.19)
project(DSA2_Dijkstra)

set(CMAKE_CXX_STANDARD 11)

add_executable(DSA2_Dijkstra main.cpp cmake-build-debug/heap.cpp cmake-build-debug/heap.h cmake-build-debug/main.cpp cmake-build-debug/hash.cpp cmake-build-debug/hash.h cmake-build-debug/graph.cpp cmake-build-debug/graph.h)