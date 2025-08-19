#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	float data[] = {
		1.2f,
		2.3f,
		3.2f,
		4.5f,
		5.f,
		6.5f,
	};
	// Mat 객체 선언 방법
	Mat m1(2, 3, CV_8U);			   // 2행, 3열 uchar형 행렬 선언, 채널 미지정시 1채널
	Mat m2(2, 3, CV_8U, Scalar(300));  // uchar형이라 255이상은 255로 저장
	Mat m3(2, 3, CV_16S, Scalar(300)); // short형 -> 300으로 저장
	Mat m4(2, 3, CV_32F, data);		   // 배열 원소로 초기화

	// Size 객체로 Mat 객체 선언 방법
	Size sz(2, 3);
	Mat m5(Size(2, 3), CV_64F); // 2X3 크기 행렬 선언 3행 2열
	Mat m6(sz, CV_32F, data);	// Size_ 객체로 초기화

	cout << "[m1] =" << endl
		 << m1 << endl;
	cout << "[m2] =" << endl
		 << m2 << endl;
	cout << "[m3] =" << endl
		 << m3 << endl;
	cout << "[m4] =" << endl
		 << m4 << endl
		 << endl;
	cout << "[m5] =" << endl
		 << m5 << endl;
	cout << "[m6] =" << endl
		 << m6 << endl;
	return 0;
}