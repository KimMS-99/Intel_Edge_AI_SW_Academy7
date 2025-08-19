#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void bgr2hsi(Mat img, Mat &hsv) // BGR 컬러 -> HSI 컬러
{
	hsv = Mat(img.size(), CV_32FC3); // HSI 행렬 - 3채널, float형

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			float B = img.at<Vec3b>(i, j)[0]; // 파란색 화소값
			float G = img.at<Vec3b>(i, j)[1]; // 녹색 화소값
			float R = img.at<Vec3b>(i, j)[2]; // 빨간색 화소값

			float s = 1 - 3 * min(R, min(G, B)) / (R + B + G); // 채도 계산
			float v = (R + G + B) / 3.0f;

			float tmp1 = ((R - G) + (R - B)) * 0.5f;
			float tmp2 = sqrt((R - G) * (R - B) + (G - B) * (G - B));
			float angle = (float)acos(tmp1 / tmp2) * (180.f / CV_PI);
			float h = (B <= G) ? angle : 360 - angle; // 색상 계산

			hsv.at<Vec3f>(i, j) = Vec3f(h / 2, s * 255, v);
		}
	}
	hsv.convertTo(hsv, CV_8U);
}

int main()
{
	Mat BGR_img = imread("../image/color_space.jpg", IMREAD_COLOR);
	CV_Assert(BGR_img.data);

	Mat HSI_img, HSV_img, hsi[3], hsv[3];

	bgr2hsi(BGR_img, HSI_img);				   // BGR에서 HSV 변환
	cvtColor(BGR_img, HSV_img, COLOR_BGR2HSV); // OpenCV 함수
	split(HSI_img, hsi);					   // 채널 분리
	split(HSV_img, hsv);

	imshow("BGR_img", BGR_img);
	imshow("Hue", hsi[0]); // 사용자 정의함수 이용
	imshow("Saturation", hsi[1]);
	imshow("Intensity", hsi[2]);
	imshow("OpenCV_Hue", hsv[0]); // OpenCV 제공함수 이용
	imshow("OpenCV_Saturation", hsv[1]);
	imshow("OpenCV_Value", hsv[2]);
	waitKey();
	return 0;
}