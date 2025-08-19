#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void filter(Mat img, Mat &dst, Mat mask) // 회선 수행 함수
{
	dst = Mat(img.size(), CV_32F, Scalar(0)); // 회선 결과 저장 행렬
	Point h_m = mask.size() / 2;			  // 마스크 중심 좌표

	for (int i = h_m.y; i < img.rows - h_m.y; i++) // 입력 행렬 반복 순회
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float sum = 0;
			for (int u = 0; u < mask.rows; u++) // 마스크 원소 순회
			{
				for (int v = 0; v < mask.cols; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					sum += mask.at<float>(u, v) * img.at<uchar>(y, x); // 회선 수식
				}
			}
			dst.at<float>(i, j) = sum; // 회선 누적값 출력화소 저장
		}
	}
}

int main()
{
	Mat image = imread("../image/filter_blur.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data); // 영상파일 예외 처리

	float data[] = // 블러링 마스크 원소 지정
		{
			1 / 9.f,
			1 / 9.f,
			1 / 9.f,
			1 / 9.f,
			1 / 9.f,
			1 / 9.f,
			1 / 9.f,
			1 / 9.f,
			1 / 9.f,
		};

	float data1[] = // 블러링 마스크 원소 지정
		{
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
			1 / 25.f,
		};

	Mat mask(3, 3, CV_32F, data);
	Mat blur;

	Mat mask1(5, 5, CV_32F, data1);
	Mat blur1;

	filter(image, blur, mask);
	blur.convertTo(blur, CV_8U); // 윈도우 영상 표시 위해

	filter(image, blur1, mask1);
	blur1.convertTo(blur1, CV_8U); // 윈도우 영상 표시 위해

	imshow("image", image);
	imshow("blur", blur), imshow("blur1", blur1);
	waitKey();
	return 0;
}