#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void calc_Histo(const Mat &image, Mat &hist, int bins, int range_max = 256)
{
	int histSize[] = {bins};			   // 히스토그램 계급개수
	float range[] = {0, (float)range_max}; // 채널 화소값 범위
	int channels[] = {0};				   // 채널 목록 - 단일 채널
	const float *ranges[] = {range};

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

int main()
{
	Mat image = imread("../image/pixel_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat hist, hist_img;
	calc_Histo(image, hist, 256); // 히스토그램 계산

	cout << hist.t() << endl;

	imshow("image", image);
	waitKey();
	return 0;
}