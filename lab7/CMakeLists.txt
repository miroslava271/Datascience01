cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(app
    src/main.cpp
    src/CameraProvider.cpp
    src/FrameProcessor.cpp
    src/KeyProcessor.cpp
    src/FaceDetector.cpp
)

target_include_directories(app PRIVATE include)

target_link_libraries(app ${OpenCV_LIBS} pthread)