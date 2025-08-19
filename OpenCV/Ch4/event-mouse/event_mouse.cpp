#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void onMouse(int, int, int, int, void *); // 마우스 콜백 함수

int main()
{
	int param = 100;
	Mat image(200, 300, CV_8U);
	image.setTo(255); // image 행렬 초기화 - 흰색 바탕

	imshow("mouse event1", image);
	imshow("mouse event2", image);

	setMouseCallback("mouse event1", onMouse, &param);
	setMouseCallback("mouse event2", onMouse, &param);

	waitKey(0);
	return 0;
}

// 콜백 함수 구현
void onMouse(int event, int x, int y, int flags, void *param)
{
	int p = *(int *)param;
	cout << "x : " << x << ", y : " << y << ", flags : " << flags
		 << ", param" << p << endl;

	switch (event) // switch문으로 event값에 따라 버튼 종류를 구분
	{
	case EVENT_LBUTTONDOWN:
		cout << "마우스 왼쪽버튼 누르기" << endl;
		break;
	case EVENT_RBUTTONDOWN:
		cout << "마우스 오른쪽버튼 누르기" << endl;
		break;
	case EVENT_RBUTTONUP:
		cout << "마우스 오른쪽버튼 떼기" << endl;
		break;
	case EVENT_LBUTTONDBLCLK:
		cout << "마우스 왼쪽버튼 더블클릭" << endl;
		break;
	case EVENT_MBUTTONDOWN:
		cout << "마우스 중간버튼 누르기" << endl;
	}
}