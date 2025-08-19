#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat m = (Mat_<uchar>(2, 4) << 1, 2, 3, 4, 5, 6, 7, 8); // 2행 4열 행렬
	cout << "[m] = " << endl
		 << m << endl
		 << endl;

	m.resize(1); // 행렬의 행수 1로 변경 -> 행렬이 2행에서 1행으로
	cout << "m.resize(1) = " << endl
		 << m << endl;
	m.resize(3); // 행수 3으로 변경 -> 1행에서 3행으로 증가
	cout << "m.resize(3) = " << endl
		 << m << endl
		 << endl;
	m.resize(5, Scalar(50)); // 행수를 5행으로 변경, 추가된 행의 원소값 50지정
	cout << "m.resize(5) = " << endl
		 << m << endl;
	return 0;
}