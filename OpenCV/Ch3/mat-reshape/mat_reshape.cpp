#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 행렬 정보 콘솔창 출력 함수(채널 수, 크기, 행, 열)
void print_matInfo(string m_name, Mat m) // 채널 정보 출력
{
	cout << "[ " << m_name << " 행렬]" << endl;
	cout << "    채널수  = " << m.channels() << endl;
	cout << "    행 x 열 = " << m.rows << " x " << m.cols << endl
		 << endl;
}

int main()
{
	Mat m1(2, 6, CV_8U);	   // 2행, 6열 char 행렬 선언
	Mat m2 = m1.reshape(2);	   // 2채널 행렬로 변경 생성
	Mat m3 = m1.reshape(3, 2); // 3채널, 2행 행렬로 변경 생성

	cout << "m1 = " << m1.cols << endl;
	cout << "m2 = " << m2.cols << endl;

	print_matInfo("m1(2, 6)", m1);
	print_matInfo("m2 = m1_reshape(2)", m2);
	print_matInfo("m3 = m1_reshape(3, 2)", m3);

	m1.create(3, 5, CV_16S); // Mat::create()는 기존 행렬을 새로 생성
	print_matInfo("m1.create(3, 5)", m1);
	return 0;
}