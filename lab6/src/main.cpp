#include <opencv2/opencv.hpp>
#include "CameraProvider.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"

int main() {

    CameraProvider camera;
    FrameProcessor processor;
    KeyProcessor keyProcessor;

    KeyProcessor::Mode mode = KeyProcessor::ORIGINAL;

    int blurValue = 5;
    int brightnessValue = 0;

    cv::namedWindow("Window");

    cv::createTrackbar("Blur", "Window", &blurValue, 31);
    cv::createTrackbar("Brightness", "Window", &brightnessValue, 100);

    while (true) {

        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        int key = cv::waitKey(10);
        if (key == 27) break;

        if (key != -1) {
            mode = keyProcessor.process(key);
        }

        cv::Mat output = processor.process(frame, mode, blurValue, brightnessValue);

        cv::imshow("Window", output);
    }

    return 0;
}
