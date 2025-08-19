#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void mask_setTo();
void mask_copyTo();
void time_inverse();
void useful_func();

int main(void)
{
	mask_setTo();
	mask_copyTo();
	time_inverse();
	useful_func();

	return 0;
}

void mask_setTo()
{
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);

	if (src.empty() || mask.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	// 마스크 연산을 지원하는 함수
	// mask 영상에서 픽셀 값이 0이 아닌 위치에서만 src 영상 픽셀을 노란색으로 설정
	src.setTo(Scalar(0, 255, 255), mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

void mask_copyTo()
{
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);

	if (src.empty() || mask.empty() || dst.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	// 영상의 픽셀 값이 0이 아닌 위치에서만 *this 행렬 원소 값을 행렬 m(첫 번째 인자)로 복사
	// mask 영상에서 흰색 영역 위치에서만 src 영상 픽셀 값을 dst로 복사
	src.copyTo(dst, mask);

	imshow("src", src);
	imshow("dst", dst);
	imshow("mask", mask);

	waitKey();
	destroyAllWindows();
}

void time_inverse()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;
	tm.start(); // 시간 측정 시작

	// 영상의 모든 픽셀을 반전시킴
	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}

	tm.stop(); // 시간 측정을 종료
	// 측정된 시간을 콘솔 창에 출력
	cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;
}

void useful_func()
{
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (img.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	cout << "Sum: " << (int)sum(img)[0] << endl;
	cout << "Mean: " << (int)mean(img)[0] << endl;

	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);

	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;

	Mat src = Mat_<float>({1, 5}, {-1.f, -0.5f, 0.f, 0.5f, 1.f});

	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);

	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;

	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;
}