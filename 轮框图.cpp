#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("circle.jpg");
	namedWindow("My original");
	imshow("My original", image);
	Mat gray;
	cvtColor(image, gray, COLOR_RGB2GRAY);
	
	int thresh_size = (100 / 4) * 2 + 1;
	adaptiveThreshold(gray, gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C,
		THRESH_BINARY_INV, thresh_size, thresh_size / 3);

	imshow("gray", gray);
	vector<vector<Point>> contours;
	findContours(gray, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	vector<vector<Point>> contours1;
	for (int i = 0; i < contours.size(); i++) {
		contours1.push_back(contours[i]);
	}

	Mat hole(gray.size(), CV_8U, Scalar(0));
	drawContours(hole, contours1, -1, Scalar(255), FILLED);
	namedWindow("My hole");
	imshow("My hole", hole);

	Mat crop(image.rows, image.cols, CV_8UC3);
	image.copyTo(crop, hole);
	namedWindow("My warpPerspective");
	imshow("My warpPerspective", crop);

	waitKey();

	return 0;
}