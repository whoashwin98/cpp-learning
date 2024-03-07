cmake_minimum_required(VERSION 3.27)
project(DummyStatic)

set(CMAKE_CXX_STANDARD 17)

add_library(DummyStatic STATIC library.cpp)
