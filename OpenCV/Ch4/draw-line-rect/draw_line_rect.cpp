#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#include "../../setMouseCallback.h"

int main()
{
	Scalar white(255, 255, 255), yellow(0, 255, 255), blue(255, 0, 0); // 생상 건언
	Scalar red = Scalar(0, 0, 255);									   // 흰색 색상
	Scalar green = Scalar(0, 255, 0);

	Mat image(400, 600, CV_8UC3, white);
	Point pt1(50, 130), pt2(200, 300), pt3(300, 150), pt4(400, 50); // 좌표 선언
	Rect rect(pt3, Size(200, 150));

	line(image, pt1, pt2, red);					// 직선 그리기
	line(image, pt3, pt4, green, 2, LINE_AA);	// 안티에일리싱 선
	line(image, pt3, pt4, green, 3, LINE_8, 1); // 8방향 연결선, 1비트 시프트

	rectangle(image, rect, blue, 2);				 // 사각형 그리기
	rectangle(image, rect, blue, FILLED, LINE_4, 1); // 4방향 연결선, 1비트 시프트
	rectangle(image, pt1, pt2, red, 3);

	imshow("Line & Rect", image);
	setMouseCallback("Line & Rect", onMouse, 0);
	waitKey(0);
	return 0;
}