#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (image.empty()) {
		cout << "read image failure" << endl;
		return -1;
	}

	int th = 100;
	Mat global;
	threshold(image, global, th, 255, THRESH_BINARY_INV);

	int blockSize = 25;
	int constValue = 10;
	Mat local;
	adaptiveThreshold(image, local, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, blockSize, constValue);
	
	imshow("全局二值化", global);
	imshow("局部二值化", local);
	waitKey(0);
	return 0;
	
}