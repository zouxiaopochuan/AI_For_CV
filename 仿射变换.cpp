#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src = imread("lena.jpg");
	imshow("lena", src);
	Mat dst_warp, dst_warpRotateScale;
	Point2f srcPoints[3];
	Point2f dstPoints[3];
	//第一种仿射变换：三点法
	srcPoints[0] = Point2f(0, 0);
	srcPoints[1] = Point2f(0, src.rows - 1);
	srcPoints[2] = Point2f(src.cols - 1, 0);

	dstPoints[0] = Point2f(0, src.rows * 0.3);
	dstPoints[1] = Point2f(src.cols * 0.25, src.rows * 0.75);
	dstPoints[2] = Point2f(src.cols * 0.75, src.rows * 0.25);
	
	Mat M1 = getAffineTransform(srcPoints, dstPoints);
	warpAffine(src, dst_warp, M1, src.size());

	//第二种仿射变换：直接指定角度和比例
	Point2f center(src.cols / 2, src.rows / 2);
	double angle = 45;
	double scale = 0.5;
	Mat M2 = getRotationMatrix2D(center, angle, scale);
	warpAffine(dst_warp, dst_warpRotateScale, M2, src.size());

	imshow("仿射变换1", dst_warp);
	imshow("仿射变换2", dst_warpRotateScale);
	waitKey();
	return 0;

}