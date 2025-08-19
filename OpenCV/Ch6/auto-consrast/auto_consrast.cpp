#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/minMax.jpg", IMREAD_GRAYSCALE);

	double minVal, maxVal;
	minMaxIdx(image, &minVal, &maxVal); // 최댓값, 최솟값 가져오기

	double ratio = (maxVal - minVal) / 255.0; // 최솟값과 최댓값의 차분에 대한 비율
	Mat dst = (image - minVal) / ratio;

	cout << "최소값  = " << minVal << endl;
	cout << "최대값  = " << maxVal << endl;

	imshow("image", image);
	imshow("dst", dst);
	waitKey();
	return 0;
}
