#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/bright.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Rect roi(0, 0, 10, 10); // 관심영역 설정
	cout << "image roi\n"
		 << image(roi) << endl;

	Mat dst1 = image + 100; // 영상 밝게
	Mat dst2 = image - 100; // 영상 어둡게
	Mat dst3 = 255 - image; // 영상 반전

	cout << "dst1 roi\n"
		 << dst1(roi) << endl;
	cout << "dst2 roi\n"
		 << dst2(roi) << endl;
	cout << "dst3 roi\n"
		 << dst3(roi) << endl;

	Mat dst4(image.size(), image.type());
	Mat dst5(image.size(), image.type());

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			// dst4.at<uchar>(i, j) = image.at<uchar>(i, j) + 100; // 영상 밝게, 오버플로우로 값이 255보다 크면 255 고정이 아닌 값이 나옴 즉, 255 + 100 = 100 의 값이 나옴
			// ccv::saturate_cast<uchar>(value) 음수는 0으로 255보다 크면 255로 고정
			dst4.at<uchar>(i, j) = saturate_cast<uchar>(image.at<uchar>(i, j) + 100); // 위에 문제를 해결한 255보다 크면 255로 고정
			dst5.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);						  // 영상 반전
		}
	}

	imshow("image", image);
	imshow("dst1 - Bright", dst1);
	imshow("dst2 - Dark", dst2);
	imshow("dst3 - Inverted", dst3); // 반전
	imshow("dst4 - Bright", dst4);
	imshow("dst5 - Inverted", dst5); // 반전

	waitKey();
	return 0;
}