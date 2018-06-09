#include "utils.h"
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    sandbox::check_args(argc, argv);

    cv::imshow("transform_image", sandbox::load_image(argv[1]));

    cv::waitKey(0);

    return 0;
}