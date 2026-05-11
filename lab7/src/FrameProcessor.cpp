#include "FrameProcessor.hpp"

cv::Mat FrameProcessor::process(const cv::Mat& frame,
                                KeyProcessor::Mode mode,
                                int blurValue,
                                int brightnessValue)
{
    cv::Mat result = frame.clone();

    // 🔥 BRIGHTNESS (slider)
    if (brightnessValue != 0) {
        result.convertTo(result, -1, 1.0, brightnessValue);
    }

    switch (mode) {

        case KeyProcessor::GRAY:
            cv::cvtColor(result, result, cv::COLOR_BGR2GRAY);
            cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);
            break;

        case KeyProcessor::BLUR: {
            int k = blurValue;

            if (k < 1) k = 1;
            if (k % 2 == 0) k++;

            cv::GaussianBlur(result, result, cv::Size(k, k), 0);
            break;
        }

        case KeyProcessor::CANNY: {
            cv::Mat gray;
            cv::cvtColor(result, gray, cv::COLOR_BGR2GRAY);
            cv::Canny(gray, result, 50, 150);
            cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);
            break;
        }

        case KeyProcessor::INVERT:
            cv::bitwise_not(result, result);
            break;

        case KeyProcessor::SOBEL: {
            cv::Mat gray, gx, gy;
            cv::cvtColor(result, gray, cv::COLOR_BGR2GRAY);

            cv::Sobel(gray, gx, CV_16S, 1, 0);
            cv::Sobel(gray, gy, CV_16S, 0, 1);

            cv::convertScaleAbs(gx, gx);
            cv::convertScaleAbs(gy, gy);

            cv::addWeighted(gx, 0.5, gy, 0.5, 0, result);
            cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);
            break;
        }

        case KeyProcessor::THRESHOLD: {
            cv::Mat gray;
            cv::cvtColor(result, gray, cv::COLOR_BGR2GRAY);
            cv::threshold(gray, result, 127, 255, cv::THRESH_BINARY);
            cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);
            break;
        }

        default:
            break;
    }

    return result;
}