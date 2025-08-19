#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string title = "Draw Event";
Mat image;

void onMouse(int event, int x, int y, int flags, void *param)
{
	static Point pt(-1, -1);

	if (event == EVENT_LBUTTONDOWN)
	{
		if (pt.x < 0) // 왼쪽 버튼 첫 클릭시 사각형 시작좌표 저장
		{
			pt = Point(x, y);
		}
		else // 왼쪽 버튼 두번째 클릭시 사각형 그리기
		{
			rectangle(image, pt, Point(x, y), Scalar(0, 0, 255), 2);
			imshow(title, image);
			pt = Point(-1, -1);
		}
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		if (pt.x < 0) // 오른쪽 버튼 첫 클릭시 원 시작좌표 저장
		{
			pt = Point(x, y);
		}
		else // 오른쪽 버튼 두번째 클릭시 원 그리기
		{
			Point2d pt2 = pt - Point(x, y);
			int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y); // 두 좌표간 거리
			circle(image, pt, radius, Scalar(0, 255, 0), 2);

			imshow(title, image);
			pt = Point(-1, -1);
		}
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		if (pt.x < 0)
		{
			pt = Point(x, y);
		}
		else
		{
			Point2d pt2 = pt - Point(x, y);
			int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y); // 두 좌표간 거리
			circle(image, pt, radius, Scalar(150), 2);

			imshow(title, image);
			pt = Point(-1, -1);
		}
	}
}

int main()
{
	image = Mat(300, 500, CV_8UC3, Scalar(255, 255, 255));
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);

	while (1)
	{
		int key = waitKey(100);
		if (key == 27)
			break;
		if (key == 'w' || key == 'W')
		{
			imwrite("../image/event_draw.jpg", image);
			imwrite("../image/event_draw.png", image);
		}
	}

	return 0;
}