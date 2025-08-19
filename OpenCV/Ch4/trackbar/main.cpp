#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_level_change(int pos, void *userdata);

int main(void)
{
	Mat img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("image");
	// 트랙바를 생성하고 트랙바 콜백 함수를 등록
	createTrackbar("level", "image", 0, 16, on_level_change, (void *)&img);

	imshow("image", img);
	waitKey();

	return 0;
}

void on_level_change(int pos, void *userdata)
{
	Mat img = *(Mat *)userdata;

	// 트랙바 위체 pos에 16을 곱한 결과를 img 영상의 전체 픽셀 값으로 설정
	img.setTo(pos * 16);
	imshow("image", img);
}
