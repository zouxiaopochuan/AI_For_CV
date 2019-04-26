#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("line.jpg");
	imshow("原始图", image);

	Mat midImage, dstImage;
	Canny(image, midImage, 100, 150, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	
	//存放的是线的极坐标表示 r,theta
	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 30, 40, 5);

	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);
		
	}
	imshow("边缘检测后的图", midImage);
	imshow("最终效果图", dstImage);

	waitKey();
	return 0;
}