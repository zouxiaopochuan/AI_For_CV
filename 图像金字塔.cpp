#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat img = imread("lena.jpg");
	imshow("原始图", img);

	Mat upSample, downSample;
	pyrUp(img, upSample, Size(img.cols * 2, img.rows * 2));
	pyrDown(img, downSample, Size(img.cols * 0.5, img.rows * 0.5));

	imshow("上采样", upSample);
	imshow("下采样", downSample);

	waitKey();
	return 0;
	
}