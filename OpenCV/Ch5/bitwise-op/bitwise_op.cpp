#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image1(250, 250, CV_8U, Scalar(0)); // 300행 300열 검은색 영상 생성
	Mat image2(250, 250, CV_8U, Scalar(0));
	// Mat image1(250, 250, CV_8UC3, Scalar(255, 0, 0)); // 파란색
	// Mat image2(250, 250, CV_8UC3, Scalar(0, 0, 255)); // 빨간색
	Mat image3, image4, image5, image6;

	Point center = image1.size() / 2;			 // 영상 중심좌표 계산
	circle(image1, center, 80, Scalar(255), -1); // 중심에 원 그리기
	// 흰색 사각형 그리기
	rectangle(image2, Point(0, 0), Point(125, 250), Scalar(255), -1);

	// 비트 연산
	bitwise_or(image1, image2, image3);	 // 원소 간 논리합 (OR)
	bitwise_and(image1, image2, image4); // 원소 간 논리곱 (AND)
	bitwise_xor(image1, image2, image5); // 원소 간 배타적 논리합 (XOR)
	bitwise_not(image1, image6);		 // 행렬 반전 (NOT)

	imshow("image1", image1), imshow("image2", image2);
	imshow("bitwise_or", image3);
	imshow("bitwise_and", image4);
	imshow("bitwise_xor", image5);
	imshow("bitwise_not", image6);
	waitKey();
	return 0;
}