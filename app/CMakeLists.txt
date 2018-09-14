cmake_minimum_required(VERSION 3.4.1)

include_directories(D:/usr/include)

add_library(native-lib SHARED
src/main/cpp/native-lib.cpp
src/main/cpp/Renderer.cpp
src/main/cpp/data0.cpp
src/main/cpp/data1.cpp
src/main/cpp/data2.cpp
src/main/cpp/data3.cpp
src/main/cpp/data4.cpp
src/main/cpp/data5.cpp)

target_link_libraries(native-lib GLESv2)