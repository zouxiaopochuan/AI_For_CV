#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 70;
int max_thresh = 175;

void on_CornerHarris(int, void*);

int main(int argc, char** argv) {
	g_srcImage = imread("lena.jpg");

	imshow("原始图", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);

	namedWindow("角点检测", WINDOW_AUTOSIZE);
	createTrackbar("阈值：", "角点检测", &thresh, max_thresh, on_CornerHarris);

	on_CornerHarris(0, 0);

	waitKey(0);
	return 0;
}

void on_CornerHarris(int, void*) {
	Mat dstImage;
	Mat normImage;
	Mat scaledImage;
	
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	//进行角点检测
	//第三个参数表示领域的大小，第四个参数辨识sobel算子孔径大小，第五个表示Harris参数
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);

	for (int j = 0; j < normImage.rows; j++) {
		for (int i = 0; i < normImage.cols; i++) {
			if ((int)normImage.at<float>(j, i) > thresh + 80) {
				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	imshow("角点检测", g_srcImage1);
	
}