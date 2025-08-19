#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat BGR_img = imread("../image/color_model.jpg", IMREAD_COLOR);
	CV_Assert(BGR_img.data); // 영상 파일 예외처리

	Scalar white(255, 255, 255); // 흰색
	Mat CMY_img = white - BGR_img;
	Mat CMY_arr[3];
	split(CMY_img, CMY_arr);

	Mat black;							// 검은색 채널
	min(CMY_arr[0], CMY_arr[1], black); // 원소 간 최솟값 저장
	min(black, CMY_arr[2], black);

	CMY_arr[0] = CMY_arr[0] - black;
	CMY_arr[1] = CMY_arr[1] - black;
	CMY_arr[2] = CMY_arr[2] - black;

	imshow("black", black);
	imshow("Yellow", CMY_arr[0]);
	imshow("Magenta", CMY_arr[1]);
	imshow("Cyan", CMY_arr[2]);
	waitKey();
	return 0;
}