// EdgeDetection.cpp : Defines the entry point for the console application.
//
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <cmath>

cv::Mat ApplyGaussian(const cv::Mat& src);
cv::Mat CalculateGradients(const cv::Mat& src);

int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "No file supplied. Exiting." << std::endl;
		return -1;
	}

	std::string imgFile{ argv[1] };
	cv::Mat img = cv::imread(imgFile, cv::IMREAD_GRAYSCALE);

	if (img.empty()) {
		std::cerr << "Failed to read image file. Exiting." << std::endl;
		return -1;
	}

	cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Original Image", img);

	// TODO: Add naive edge detection here.
	// Steps:
	// 1. Smooth the image using a gaussian blurring filter. (or just use Sobel filter for both 1 and 2)
	// 2. Calculate the gradients of the image. (Use the naive filter at first, Sobel operator later)
	// 3. Use high and low thresholds for thinning the edges
	cv::Mat smoothedImg = ApplyGaussian(img);
	// Display smoothed image
	cv::namedWindow("Smoothed", cv::WINDOW_AUTOSIZE);
	cv::imshow("Smoothed", smoothedImg);

	// TODO: need to change this to pass the smoothedImg as a 64FC1 depth
	smoothedImg.convertTo(smoothedImg, CV_64FC1);
	cv::Mat gradients =  CalculateGradients(smoothedImg);
	gradients.convertTo(gradients, CV_8UC1);
	cv::namedWindow("Gradients", cv::WINDOW_AUTOSIZE);
	cv::imshow("Gradients", gradients);

	cv::waitKey(0);
	
    return 0;
}

// Apply a 3x3 Gaussian filter to smooth the input image. Returns the resulting smoothed image.
cv::Mat ApplyGaussian(const cv::Mat& src) {
	cv::Mat dst;
	cv::GaussianBlur(src, dst, cv::Size(3, 3), 2);
	return dst;
}

// To calculate the gradient magnitude using a simple filter that samples adjacent pixels
cv::Mat CalculateGradients(const cv::Mat& src) {
	// Assert that we only wish to accept double images
	CV_Assert(src.depth() == CV_64FC1);

	// Gradient magnitude^2 = dz/dx ^2 + dz/dy ^2

	cv::Mat gradients(src.rows, src.cols, CV_64FC1, 1);
	std::cout << "Size of the original matrix: " << src.total() << std::endl;
	std::cout << "Size of the gradients matrix: " << gradients.total() << std::endl;

	const double* prev, *curr, *next;

	// Iterate over each row in the image.
	for (int i = 0; i < src.rows; ++i) {

		if (i == 0) {
			prev = src.ptr<double>(i);
		}
		else {
			prev = src.ptr<double>(i - 1);
		}

		curr = src.ptr<double>(i);

		if (i == src.rows - 1) {
			next = src.ptr<double>(i);
		}
		else {
			next = src.ptr<double>(i + 1);
		}

		double* gradRow = gradients.ptr<double>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			double dx;
			if (j == 0) {
				dx = (curr[j + 1] - curr[j]) / 2;
			}
			else if (j == src.cols - 1) {
				dx = (curr[j] - curr[j - 1]) / 2;
			}
			else {
				dx = (curr[j + 1] - curr[j - 1]) / 2;
			}

			double dy = (next[j] - prev[j]) / 2;

			gradRow[j] = std::hypot(dx, dy);
		}
	}

	return gradients;
}

