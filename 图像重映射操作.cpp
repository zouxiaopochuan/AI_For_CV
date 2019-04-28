#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("lena.jpg");
	imshow("lena", image);

	Mat dstImage, map_x, map_y;
	dstImage.create(image.size(), image.type());
	map_x.create(image.size(), CV_32FC1);
	map_y.create(image.size(), CV_32FC1);

	for (int j = 0; j < image.rows; j++) {
		for (int i = 0; i < image.cols; i++) {
			map_x.at<float>(j, i) = static_cast<float>(image.cols - i);
			map_y.at<float>(j, i) = static_cast<float>(j);
		}
	}
	remap(image, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	imshow("重映射效果图", dstImage);

	waitKey();
	return 0;

}