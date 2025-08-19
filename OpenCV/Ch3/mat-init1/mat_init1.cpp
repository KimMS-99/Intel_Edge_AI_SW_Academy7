#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat m1 = Mat::ones(3, 5, CV_8UC1);	// 모든 원소를 1로 초기화
	Mat m2 = Mat::zeros(3, 5, CV_8UC1); // 모든 원소를 0으로 초기화
	Mat m3 = Mat::eye(3, 3, CV_8UC1);	// 단위 행렬 생성

	cout << "[m1] = " << endl
		 << m1 << endl;
	cout << "[m2] = " << endl
		 << m2 << endl;
	cout << "[m3] = " << endl
		 << m3 << endl;
	return 0;
}