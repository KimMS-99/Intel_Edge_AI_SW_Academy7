#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
Point ptOld;
void on_mouse(int event, int x, int y, int flags, void *);

int main(void)
{
	img = imread("lenna.bmp");

	if (img.empty())
	{
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("img");
	setMouseCallback("img", on_mouse);

	imshow("img", img);
	waitKey();

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void *)
{
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y); // 마우스 왼쪽 버튼이 눌린 좌표를 ptOld에 저장.
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;
		break;
	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl;
		break;
	// 마우스가 움직이는 경우 왼쪽 버튼이 눌려있으면 img영상 위에 노란색 직선을 이어 그림.
	case EVENT_MOUSEMOVE:
		if (flags & EVENT_FLAG_LBUTTON)
		{
			line(img, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;
	default:
		break;
	}
}
