#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	double a = 32.12345678, b = 2.7;
	short c = 400;
	float d = 10.f, e = 11.f, f = 13.f;

	Mat_<int> m1(2, 4); // 2행 4열 int형 행렬 선언
	// cout << "[m1] = " << m1 << endl;
	Mat_<uchar> m2(3, 4, 100); // 행렬 선언 및 100으로 원소 초기화
	Mat_<short> m3(4, 5, c);   // 4행 5열 short형 선언, 원소를 변수 c로 초기화

	m1 << 1, 2, 3, 4, 5, 6; // 스트림 << 연산자로 m1 행렬의 원소에 값을 한 번에 지정
	Mat m4 = (Mat_<double>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat m5 = (Mat_<float>(2, 3) << a, b, c, d, e, f); // 변수로 원소 값 초기화ㅡ 소수점 일부 소실

	cout << "[m1]=" << endl
		 << m1 << endl;
	cout << "[m2]=" << endl
		 << m2 << endl
		 << endl;
	cout << "[m3]=" << endl
		 << m3 << endl
		 << endl;
	cout << "[m4]=" << endl
		 << m4 << endl;
	cout << "[m5]=" << endl
		 << m5 << endl;
	return 0;
}