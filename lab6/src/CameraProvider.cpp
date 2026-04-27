#include "../include/CameraProvider.hpp"

CameraProvider::CameraProvider() {
    cap.open(0);
}

cv::Mat CameraProvider::getFrame() {
    cv::Mat frame;
    cap >> frame;
    return frame;
}

