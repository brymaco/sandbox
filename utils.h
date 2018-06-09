#pragma once

#include <opencv2/opencv.hpp>
#include <exception>

#if defined(DEBUG)
    #define NOISY
#endif

#if defined(NOISY)
    #include <iostream>
    #define PRINT(x) (std::cout << (x))
#else
    #define PRINT(x)
#endif

namespace sandbox {

    void check_args(int argc, char** argv) {
        if (argc != 2) {
            throw std::invalid_argument("Provide a path to an image.");
        }
    }

    cv::Mat load_image(const std::string& path) {
        const auto image = cv::imread(path);
        if (!image.data) {
            throw std::runtime_error("No image data.");
        }
        return image;
    }
}