#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Provide a path to an image.\n";
        return -1;
    }

    cv::Mat image;
    image = cv::imread(argv[1], 1);
    if (!image.data) {
        std::cout << "No data.\n";
        return -1;
    }

    cv::namedWindow("Show Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Show Image", image);

    cv::waitKey(0);

    return 0;
}