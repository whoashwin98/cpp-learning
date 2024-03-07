cmake_minimum_required(VERSION 3.27)
project(DummyDynamic)

set(CMAKE_CXX_STANDARD 17)

add_library(DummyDynamic SHARED library.cpp)
