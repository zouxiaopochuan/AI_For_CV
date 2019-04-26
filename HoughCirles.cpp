#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("circle.jpg");
	imshow("原始图", image);

	Mat grayImage;
	//cvtColor(image, grayImage, COLOR_GRAY2BGR);
	Canny(image, grayImage, 50, 200, 3);
	GaussianBlur(grayImage, grayImage, Size(9, 9), 2, 2);
	
	
	vector<Vec3f> circles;
	HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1.5, grayImage.rows/5, 150, 100, 0, 110);

	
	for (size_t i = 0; i < circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

		int radius = cvRound(circles[i][2]);
		circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(image, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
	imshow("边缘检测后的图", image);
	waitKey();
	return 0;
}