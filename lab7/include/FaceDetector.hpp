#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <thread>
#include <mutex>
#include <atomic>

class FaceDetector {
private:
    cv::dnn::Net net;

    cv::Mat frame;
    std::vector<cv::Rect> faces;

    std::thread worker;
    std::mutex mtx;
    std::atomic<bool> running;

    void loop();

public:
    FaceDetector();
    ~FaceDetector();

    void updateFrame(const cv::Mat& f);
    std::vector<cv::Rect> getFaces();
};