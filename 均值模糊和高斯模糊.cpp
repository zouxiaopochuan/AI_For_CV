#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("lena.jpg");
	imshow("lena", image);

	Mat DstPic;
	blur(image, DstPic, Size(5, 5));
	imshow("均值模糊", DstPic);

	Mat gblur;
	//最后一个参数表示高斯卷积核的方差,0表示标准差的高斯卷积核
	GaussianBlur(image, gblur, Size(5, 5),0);
	imshow("高斯模糊", gblur);

	waitKey();
	return 0;
	
}