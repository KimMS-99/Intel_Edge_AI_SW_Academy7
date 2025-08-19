#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void differOp(Mat img, Mat &dst, int mask_size) // 차연산자 에지 검출
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2); // 마스크 절반 크기

	for (int i = h_m.y; i < img.rows - h_m.y; i++) // 입력 영상 순회
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++) // 영상의 끝단에서 마스크 절반 크기 제외
		{
			vector<uchar> mask;
			for (int u = 0; u < mask_size; u++) // aktmzm qjadnl tnsghl
			{
				for (int v = 0; v < mask_size; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					mask.push_back(img.at<uchar>(y, x)); // dlqfur ghkth aktmzmdp wjwkd
				}
			}

			uchar max = 0;
			for (int k = 0; k < (int)mask.size() / 2; k++) // 전체 원소 절반만 순회
			{
				int start = mask[k];				 // 시작방향 원소
				int end = mask[mask.size() - k - 1]; // 종료방향 원소

				uchar difference = abs(start - end); // 차분 계산
				if (difference > max)
					max = difference; // 차분 최댓값 저장
			}
			dst.at<uchar>(i, j) = max; // 출력화소에 차분 최댓값 저장
		}
	}
}

int main()
{
	Mat image = imread("../image/edge_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat edge;
	differOp(image, edge, 3); // 차 연산자 에지검출 호출

	imshow("image", image);
	imshow("edge", edge);
	waitKey();
	return 0;
}
