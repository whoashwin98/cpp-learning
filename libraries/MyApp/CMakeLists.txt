cmake_minimum_required(VERSION 3.27)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp "/Users/ashwin-pt7517/Desktop/C++ Learning/libraries/ComplexStatic/cmake-build-debug/libComplexStatic.a")
target_link_libraries(MyApp "/Users/ashwin-pt7517/Desktop/C++ Learning/libraries/ComplexShared/cmake-build-debug/libComplexShared.dylib")
target_link_libraries(MyApp "/Users/ashwin-pt7517/Desktop/C++ Learning/libraries/DummyStatic/cmake-build-debug/libDummyStatic.a")
target_link_libraries(MyApp "//Users/ashwin-pt7517/Desktop/C++ Learning/libraries/DummyDynamic/cmake-build-debug/libDummyDynamic.dylib")
