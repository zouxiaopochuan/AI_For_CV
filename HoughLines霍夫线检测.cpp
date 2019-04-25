#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("line.jpg");
	imshow("原始图", image);

	Mat midImage, dstImage;
	Canny(image, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	
	//存放的是线的极坐标表示 r,theta
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI / 180, 300, 0, 0);

	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0];//圆的半径r
		float theta = lines[i][1];//直线的角度
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);

		imshow("边缘检测后的图",midImage);
		imshow("最终效果图", dstImage);
	}

	waitKey();
	return 0;
}