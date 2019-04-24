#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("lena.jpg");
	imshow("lena", image);
	
	Mat element = getStructuringElement(MORPH_RECT, Size(2, 2));
	Mat DstPic;
	erode(image, DstPic, element);
	imshow("腐蚀效果图", DstPic);
	waitKey();
	return 0;
	
}