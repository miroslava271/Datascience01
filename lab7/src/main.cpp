#include <opencv2/opencv.hpp>
#include <chrono>

#include "CameraProvider.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"
#include "FaceDetector.hpp"

int main() {

    CameraProvider camera;
    FrameProcessor processor;
    KeyProcessor keyProcessor;
    FaceDetector detector;

    KeyProcessor::Mode mode = KeyProcessor::ORIGINAL;

    int blurValue = 5;
    int brightnessValue = 0;

    cv::namedWindow("Window");

    cv::createTrackbar("Blur", "Window", &blurValue, 31);
    cv::createTrackbar("Brightness", "Window", &brightnessValue, 100);

    // FPS smoothing
    auto lastTime = std::chrono::high_resolution_clock::now();
    double fps = 0.0;

    while (true) {

        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        // send frame to worker thread
        detector.updateFrame(frame);

        // get async results
        auto faces = detector.getFaces();

        int key = cv::waitKey(1);
        if (key == 27) break;

        if (key != -1)
            mode = keyProcessor.process(key);

        // processing filters
        cv::Mat output = processor.process(frame, mode, blurValue, brightnessValue);

        // draw faces
        for (const auto& f : faces) {
            cv::rectangle(output, f, cv::Scalar(0, 255, 0), 2);
        }

        // FPS calculation (stable)
        auto now = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();

        if (ms > 0) {
            double instant = 1000.0 / ms;
            fps = fps * 0.9 + instant * 0.1; // smoothing
        }

        lastTime = now;

        cv::putText(output,
            "FPS: " + std::to_string((int)fps),
            cv::Point(20, 40),
            cv::FONT_HERSHEY_SIMPLEX,
            1,
            cv::Scalar(0, 255, 0),
            2);

        cv::imshow("Window", output);
    }

    return 0;
}