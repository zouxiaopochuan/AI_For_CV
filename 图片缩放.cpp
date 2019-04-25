#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat imge = imread("lena.jpg");
	imshow("原始图", imge);

	Mat reimge;
	
	//长宽都变为原来的2倍
	resize(imge, reimge, Size(), 2, 2);
	imshow("尺寸调整后", reimge);

	waitKey();
	return 0;
	
}