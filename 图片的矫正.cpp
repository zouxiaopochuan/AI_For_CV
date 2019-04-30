#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void GetContoursPic(const char* pSrcFileName, const char* pDstFileName) {
	Mat srcImg = imread(pSrcFileName);
	imshow("原始图", srcImg);
	Mat gray, binImg;
	cvtColor(srcImg, gray, COLOR_RGB2GRAY);
	imshow("灰度图", gray);
	//二值化
	threshold(gray, binImg, 100, 200, THRESH_BINARY);
	imshow("二值化", binImg);

	vector<vector<Point> > contours;
	vector<Rect> boundRect(contours.size());
	findContours(binImg, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	cout <<"coutrours的值："<< contours.size() << endl;
	
	for (int i = 0; i < contours.size(); i++) {
		//需要获取的坐标
		Point2f rectpoint[4];
		
		RotatedRect rect = minAreaRect(Mat(contours[i]));
		rect.points(rectpoint);
		float angle = rect.angle;
		cout << angle << endl;

		int line1 = sqrt((rectpoint[1].y - rectpoint[0].y) * (rectpoint[1].y - rectpoint[0].y) + 
			(rectpoint[1].x - rectpoint[0].x) * (rectpoint[1].x - rectpoint[0].x));
		int line2 = sqrt((rectpoint[3].y - rectpoint[0].y) * (rectpoint[3].y - rectpoint[0].y) + 
			(rectpoint[3].y - rectpoint[0].y) * (rectpoint[3].y - rectpoint[0].y));
		if (line1 * line2 < 600) continue;

		//为了让正方形横着放,所以旋转角度不一样的。竖放的，给他加90度，翻过来
		if (line1 > line2) angle = 90 + angle;

		//新建一个感兴趣的区域，大小和原图一样大
		Mat RoiSrcImg(srcImg.rows, srcImg.cols, CV_8UC3);
		RoiSrcImg.setTo(0);

		drawContours(binImg, contours, -1, Scalar(255), FILLED);

		srcImg.copyTo(RoiSrcImg, binImg);
		namedWindow("RoiSrcImg", 1);
		imshow("RoiSrcImg", RoiSrcImg);

		//创建一个旋转后的图像
		Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
		RatationedImg.setTo(0);
		//对RoiSrcImg进行旋转
		Point2f center = rect.center;
		Mat M2 = getRotationMatrix2D(center, angle, 1);
		warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));
		imshow("旋转之后", RatationedImg);
		imwrite("r.jpg", RatationedImg);//将矫正后的图片保存下来
	}


}
int main(int argc, char** argv) {
	GetContoursPic("fapiao.png", "jiaozhen.jpg");
	waitKey(0);
	return 0;
}

