#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat BGR_img = imread("../image/color_model.jpg", IMREAD_COLOR);
	CV_Assert(BGR_img.data);

	Scalar white(255, 255, 255);
	Mat CMY_img = white - BGR_img;
	Mat CMY_arr[3];
	split(CMY_img, CMY_arr); // 채널 분리

	imshow("BGR_img", BGR_img);
	imshow("CMY_img", CMY_img);
	imshow("Yellow", CMY_arr[0]);  // 노랑색 채널
	imshow("Magenta", CMY_arr[1]); // 다홍색 채널
	imshow("Cyan", CMY_arr[2]);	   // 청록색 채널
	waitKey();
	return 0;
}