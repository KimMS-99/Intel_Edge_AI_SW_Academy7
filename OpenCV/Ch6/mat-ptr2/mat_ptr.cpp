#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	uchar data[] = {
		1,
		2,
		3,
		1,
		2,
		3,
		1,
		2,
		3,
	};

	Mat m1(3, 3, CV_8UC1, data);  // 배열로 행렬 초기화
	Mat m2(m1.size(), m1.type()); // m1 행렬과 같은 크기와 타입
	Mat m3(m1.size(), CV_32FC3);  // 3채널 float형 행렬 선언

	MatConstIterator_<uchar> it_m1 = m1.begin<uchar>(); // 반복자 선언, 읽기 전용(Const)
	MatIterator_<uchar> it_m2 = m2.begin<uchar>();		// 읽기 / 쓰기 가능
	Mat_<Vec3f>::iterator it_m3 = m3.begin<Vec3f>();

	for (; it_m1 != m1.end<uchar>(); ++it_m1, ++it_m2, ++it_m3)
	{
		*it_m2 = *it_m1;

		(*it_m3)[0] = *it_m1 * 0.5f;
		(*it_m3)[1] = *it_m1 * 0.3f;
		(*it_m3)[2] = *it_m1 * 0.2f;
	}

	cout << "m1 = " << endl
		 << m1 << endl;
	cout << "m2 = " << endl
		 << m2 << endl;
	cout << "m3 = " << endl
		 << m3 << endl;
	return 0;
}