#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat img, templ, result;
	img = imread("lena.jpg");
	templ = imread("mouth.jpg");
	
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	result.create(result_cols, result_rows, CV_32FC1);

	//标准平方差匹配
	matchTemplate(img, templ, result, TM_SQDIFF_NORMED);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal = -1;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	Point matchLoc;
	
	cout << "匹配度：" << minVal << endl;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	cout << "匹配度:" << minVal << endl;
	matchLoc = minLoc;
	rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows),
		Scalar(0, 255, 0), 2, 8, 0);

	imshow("img", img);
	waitKey(0);

	return 0;
}