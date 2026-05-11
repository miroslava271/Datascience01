#include "FaceDetector.hpp"

FaceDetector::FaceDetector() {
    net = cv::dnn::readNetFromCaffe(
    "../deploy.prototxt",
    "../res10_300x300_ssd_iter_140000.caffemodel"
);

    running = true;
    worker = std::thread(&FaceDetector::loop, this);
}

FaceDetector::~FaceDetector() {
    running = false;
    if (worker.joinable())
        worker.join();
}

void FaceDetector::updateFrame(const cv::Mat& f) {
    std::lock_guard<std::mutex> lock(mtx);
    frame = f.clone();
}

std::vector<cv::Rect> FaceDetector::getFaces() {
    std::lock_guard<std::mutex> lock(mtx);
    return faces;
}

void FaceDetector::loop() {

    while (running) {

        cv::Mat f;

        {
            std::lock_guard<std::mutex> lock(mtx);
            if (frame.empty()) continue;
            f = frame.clone();
        }

        cv::Mat blob = cv::dnn::blobFromImage(
            f, 1.0, cv::Size(300,300),
            cv::Scalar(104,177,123)
        );

        net.setInput(blob);
        cv::Mat det = net.forward();

        std::vector<cv::Rect> newFaces;

        float* data = (float*)det.data;

        for (int i = 0; i < det.size[2]; i++) {

            float conf = data[i * 7 + 2];

            if (conf > 0.5) {

                int x1 = data[i*7+3] * f.cols;
                int y1 = data[i*7+4] * f.rows;
                int x2 = data[i*7+5] * f.cols;
                int y2 = data[i*7+6] * f.rows;

                newFaces.emplace_back(cv::Rect(cv::Point(x1,y1), cv::Point(x2,y2)));
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            faces = newFaces;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}