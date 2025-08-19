#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/sum_test.jpg", 1); // 컬러 영상 로드
	CV_Assert(image.data);							// 예외 처리

	Mat mask(image.size(), CV_8U, Scalar(0));
	mask(Rect(20, 40, 70, 70)).setTo(255); // 마스킹 영역 지정 - 해당 영역 계산

	Scalar sum_value = sum(image);
	Scalar mean_value1 = mean(image);
	Scalar mean_value2 = mean(image, mask); // 마스크 1 영역만 평균 계산

	cout << "[sum_value] = " << sum_value << endl;
	cout << "[mean_value1] = " << mean_value1 << endl;
	cout << "[mean_value2] = " << mean_value2 << endl
		 << endl;

	Mat mean, stddev;
	meanStdDev(image, mean, stddev); // 평균과 표준편차 결과 저장
	cout << "[mean] = " << mean << endl;
	cout << "[stddev] = " << stddev << endl
		 << endl;

	// 마스크 원소 중 1인 위치만 image 행렬 평균/표준편차 계산
	meanStdDev(image, mean, stddev, mask);
	cout << "[mean] = " << mean << endl;
	cout << "[stddev] = " << stddev << endl;

	imshow("image", image), imshow("mask", mask);
	waitKey();
	return 0;
}