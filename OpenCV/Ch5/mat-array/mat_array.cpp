#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/flip_test.jpg", IMREAD_COLOR); // 컬러 읽기 모드
	CV_Assert(image.data);										// 예외 처리

	Mat x_axis, y_axis, xy_axis, rep_img, trans_img;
	flip(image, x_axis, 0); // x축 기준 상하 뒤집기
	flip(image, y_axis, 1); // y축 기준 좌우 뒤집기
	flip(image, xy_axis, -1);

	repeat(image, 1, 2, rep_img); // 반복 복사
	transpose(image, trans_img);  // 행렬 전치

	imshow("image", image), imshow("x_axis", x_axis); // 행렬을 영상으로 표시
	imshow("y_axis", y_axis), imshow("xy_axis", xy_axis);
	imshow("rep_img", rep_img), imshow("trans_img", trans_img);

	waitKey();
	return 0;
}