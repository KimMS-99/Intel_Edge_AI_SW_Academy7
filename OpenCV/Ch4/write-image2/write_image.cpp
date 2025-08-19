#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat img8 = imread("../image/read_color.jpg", IMREAD_COLOR);
	Mat img16, img32;
	CV_Assert(img8.data);
	img8.convertTo(img16, CV_16U, 65535 / 255.0); // 형변환 및 원소 스케일 조정
	img8.convertTo(img32, CV_32F, 1 / 255.0f);

	Rect roi(10, 10, 3, 3); // 화소값 확인 위한 관심영역
	cout << "img8 행렬의 일부 " << endl
		 << img8(roi) << endl
		 << endl;
	cout << "img16 행렬의 일부 " << endl
		 << img16(roi) << endl
		 << endl;
	cout << "img32 행렬의 일부 " << endl
		 << img32(roi) << endl;

	imwrite("../image/write_test_16.tif", img16); // 행렬 영상파일로 저장
	imwrite("../image/write_test_32.tif", img32);

	imshow("img16", img16);
	imshow("img32", img32);
	waitKey();
	return 0;
}