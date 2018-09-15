cmake_minimum_required(VERSION 3.4.1)

set(OpenCV_DIR D:/usr/Android/OpenCV-android-sdk/sdk/native/jni)
find_package(OpenCV REQUIRED)
set(OpenCV_STATIC ON)

include_directories(D:/usr/include ${OpenCV_INCLUDE_DIRS})

add_library(native-lib SHARED
src/main/cpp/native-lib.cpp
src/main/cpp/Renderer.cpp)

target_link_libraries(native-lib GLESv2 jnigraphics ${OpenCV_LIBS})