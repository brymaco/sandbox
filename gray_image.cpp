#include "utils.h"
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    sandbox::check_args(argc, argv);

    auto image = sandbox::load_image(argv[1]);
    cv::imshow("Original", image);
    cv::waitKey(0);

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::imshow("Gray", image);
    cv::waitKey(0);

    return 0;
}