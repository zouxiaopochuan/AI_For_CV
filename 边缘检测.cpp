#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("lena.jpg", IMREAD_GRAYSCALE);
	imshow("lena", image);

	Mat eImage;
	blur(image, eImage, Size(3, 3));
	//第三第四个参数为高低阈值
	Canny(eImage, eImage, 3, 50, 3);
	imshow("边缘提取", eImage);

	waitKey();
	return 0;
	
}