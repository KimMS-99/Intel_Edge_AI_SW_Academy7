#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void homogenOp(Mat img, Mat &dst, int mask_size) // 유사연산자 에지 검출
{
	dst = Mat(img.size(), CV_8U, Scalar(0)); // 결과 행렬
	Point h_m(mask_size / 2, mask_size / 2); // 마스크 절반 크기

	for (int i = h_m.y; i < img.rows - h_m.y; i++) // 입력 영상 순회
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++) // 입력영상의 상하좌우 마스크 절반 크기(h_m)화소 제외
		{
			uchar max = 0;
			for (int u = 0; u < mask_size; u++)
			{
				for (int v = 0; v < mask_size; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					uchar difference = abs(img.at<uchar>(i, j) - img.at<uchar>(y, x));
					if (difference > max)
						max = difference; // 마스크 범위내 차분 중 최댓값
				}
			}
			dst.at<uchar>(i, j) = max; // 출력화소 저장
		}
	}
}

int main()
{
	Mat image = imread("../image/edge_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat edge;
	homogenOp(image, edge, 3); // 유사연산자 에지검출

	imshow("image", image);
	imshow("edge-homogenOp", edge);
	waitKey();
	return 0;
}
