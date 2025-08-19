#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/color.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat bgr[3];
	split(image, bgr); // 3채널 행렬에서 채널 분리

	imshow("image", image);
	// imshow()에 단일 채널 이미지를 넣으면 자동으로 Grayscale로 출력
	imshow("blue channel", bgr[0]); // 단일 채널(B)만 출력하므로 자동으로 Grayscale로 표시됨
	imshow("green channel", bgr[1]);
	imshow("red channel", bgr[2]);

	waitKey(0);
	return 0;
}