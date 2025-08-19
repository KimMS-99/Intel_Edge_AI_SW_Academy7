#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image1(50, 512, CV_8UC1, Scalar(0)); // 50행, 512열 영상 생성
	Mat image2(50, 512, CV_8UC1, Scalar(0));

	for (int i = 0; i < image1.rows; i++) // 행렬 전체 조회
	{
		for (int j = 0; j < image1.cols; j++)
		{
			image1.at<uchar>(i, j) = j / 2;			// 화소값 점진적 증가
			image2.at<uchar>(i, j) = (j / 20) * 10; // 계단현상 증가
		}
	}

	imshow("image1", image1);
	imshow("image2", image2);
	waitKey();

	return 0;
}
