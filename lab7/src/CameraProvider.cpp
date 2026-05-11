#include "../include/CameraProvider.hpp"
#include <iostream>

CameraProvider::CameraProvider() {
    // MAC FIX: використовуємо AVFoundation
    cap.open(0, cv::CAP_AVFOUNDATION);

    if (!cap.isOpened()) {
        std::cout << "ERROR: Camera not opened!" << std::endl;
    } else {
        std::cout << "Camera successfully opened!" << std::endl;
    }
}

cv::Mat CameraProvider::getFrame() {
    cv::Mat frame;

    if (!cap.isOpened()) {
        return frame; // пустий кадр
    }

    cap >> frame;
    return frame;
}

bool CameraProvider::isOpened() const {
    return cap.isOpened();
}
