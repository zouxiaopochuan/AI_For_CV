#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("lenaSrc.jpg");

	imshow("原图", image);
	Mat imageGray;
	cvtColor(image, imageGray, COLOR_RGB2GRAY, 0);

	Mat imageMask = Mat(image.size(), CV_8UC1, Scalar::all(0));

	//通过阈值处理生成Mask
	threshold(imageGray, imageMask, 250, 255, THRESH_BINARY);
	Mat Kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	//对Mask膨胀处理,增加Mask面积
	dilate(imageMask, imageMask, Kernal);

	inpaint(image, imageMask, image, 5, INPAINT_TELEA);
	imshow("Mask", imageMask);
	imshow("修复后", image);

	waitKey();

	return 0;
}