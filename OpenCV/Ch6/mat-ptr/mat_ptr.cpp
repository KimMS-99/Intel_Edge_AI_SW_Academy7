#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat m1(3, 5, CV_8UC1);		 // uchar형 행렬 선언
	Mat m2(m1.size(), CV_32FC1); // float형 행렬 선언

	// cout << "m1 = " << "\n"
	// 	 << m1 << "\n"
	// 	 << "\n";
	// cout << "m2 = " << "\n"
	// 	 << m2 << endl;

	for (int i = 0, k = 0; i < m1.rows; i++)
	{
		// uchar형은 반환자료형 생략 가능.
		uchar *ptr_m1 = m1.ptr(i); // m1 행렬의 i행 주소 반환
		float *ptr_m2 = m2.ptr<float>(i);
		for (int j = 0; j < m1.cols; j++)
		{
			ptr_m1[j] = j;			  // 배열 접근 방식
			*(ptr_m2 + j) = (float)j; // 포인터 접근 방식
		}
	}
	cout << "m1 = " << "\n"
		 << m1 << "\n"
		 << "\n";
	cout << "m2 = " << "\n"
		 << m2 << endl;
	return 0;
}