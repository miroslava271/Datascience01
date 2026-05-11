cmake_minimum_required(VERSION 3.10)
project(OpenCVApp)

find_package(OpenCV REQUIRED)

include_directories(include)

add_executable(app
    src/main.cpp
    src/CameraProvider.cpp
    src/KeyProcessor.cpp
    src/FrameProcessor.cpp
    src/Display.cpp
)

target_link_libraries(app ${OpenCV_LIBS})
