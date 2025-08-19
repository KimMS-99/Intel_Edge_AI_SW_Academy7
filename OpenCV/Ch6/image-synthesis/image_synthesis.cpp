#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image1 = imread("../image/add2.jpg", IMREAD_GRAYSCALE);
	Mat image2 = imread("../image/add1.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!(image1.empty() || image2.empty())); // 예외처리

	double alpha = 0.6, beta = 0.7; // 가중치 합성 시 사용할 비율

	Mat add_img1 = image1 + image2;						  // 영상 합성, 255넘으면 255로 처리
	Mat add_img2 = image1 * 0.5 + image2 * 0.5;			  // 두 영상에 동일한 가중치를 주어 평균값을 계산 (투명하게 겹치는 효과)
	Mat add_img3 = image1 * alpha + image2 * (1 - alpha); // 서로 다른 비율의 가중치를 이용한 두 영상 합성, alpha값을 조절하여 어떤 이미지를 부각시킬지 정할 수 있음.

	Mat add_img4, sub_img1, sub_img2;
	addWeighted(image1, alpha, image2, beta, 0, add_img4); // opencv함수 이용하여 영상 합성

	imshow("image1", image1), imshow("image2", image2);
	imshow("add_img1", add_img1), imshow("add_img2", add_img2);
	imshow("add_img3", add_img3), imshow("add_img4", add_img4);
	waitKey(0);
	return 0;
}