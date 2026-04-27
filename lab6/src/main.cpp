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

    cv::namedWindow("Window");

    cv::createTrackbar("Blur", "Window", &blurValue, 31);

    while (true) {

        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        int key = cv::waitKey(10);
        if (key == 27) break;

        mode = keyProcessor.process(key);

        if (blurValue % 2 == 0) blurValue++;

        cv::Mat output = processor.process(frame, mode, blurValue);

        cv::imshow("Window", output);
    }

    return 0;
}
