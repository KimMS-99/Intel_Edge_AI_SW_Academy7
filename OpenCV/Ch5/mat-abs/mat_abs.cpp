#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image1 = imread("../image/abs_test1.jpg", 0); // 명암도 영상 로드
	Mat image2 = imread("../image/abs_test2.jpg", 0);
	CV_Assert(image1.data && image2.data); // 예외처리

	Mat dif_img, abs_dif1, abs_dif2;

	image1.convertTo(image1, CV_16S); // 행렬 형변환(uchar -> short)
	image2.convertTo(image2, CV_16S);
	subtract(image1, image2, dif_img); // 뺄셈 수행

	Rect roi(10, 10, 7, 3);
	cout << "[dif_img] = " << endl
		 << dif_img(roi) << endl;

	abs_dif1 = abs(dif_img);

	image1.convertTo(image1, CV_8U); // 행렬 형변환(short -> uchar)
	image2.convertTo(image2, CV_8U);
	dif_img.convertTo(dif_img, CV_8U);
	abs_dif1.convertTo(abs_dif1, CV_8U);

	absdiff(image1, image2, abs_dif2); // 차분 절댓값 계산

	cout << "[dif_img] = " << endl
		 << dif_img(roi) << endl
		 << endl;
	cout << "[abs_dif1] = " << endl
		 << abs_dif1(roi) << endl;
	cout << "[abs_dif2] = " << endl
		 << abs_dif2(roi) << endl;

	imshow("image1", image1);
	imshow("image2", image2);
	imshow("dif_img", dif_img);
	imshow("abs_dif1", abs_dif1);
	imshow("abs_dif2", abs_dif2);
	waitKey();

	return 0;
}
