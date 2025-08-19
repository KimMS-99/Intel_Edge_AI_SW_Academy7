#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat gau_img;
String title = "canny edge";
Range th(50, 100);

void onTheshold(int value, void *)
{

	Mat canny;
	Canny(gau_img, canny, th.start, th.end); // 캐니 에지 수행
	imshow(title, canny);
}

int main()
{
	Mat image = imread("../image/color_space.jpg", 0);
	CV_Assert(image.data);

	GaussianBlur(image, gau_img, Size(5, 5), 0.3);
	namedWindow(title);
	createTrackbar("th1", title, &th.start, 255, onTheshold);
	createTrackbar("th2", title, &th.end, 255, onTheshold);

	onTheshold(0, 0);
	imshow("image", image);
	waitKey();
	return 0;
}