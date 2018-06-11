#include "utils.h"
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    sandbox::check_args(argc, argv);

    auto image = sandbox::load_image(argv[1]);
    cv::imshow("Original", image);
    cv::waitKey(0);

    cv::Mat kernel =
        (cv::Mat_<char>(3,3) << 0,-1,0, -1,5,-1, 0,-1,0);

    cv::filter2D(image, image, image.depth(), kernel);
    cv::imshow("Filtered", image);
    cv::waitKey(0);

    return 0;
}