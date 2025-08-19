#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat img8 = imread("../image/read_color.jpg", IMREAD_COLOR);
	CV_Assert(img8.data); // 영상파일 예외 처리

	vector<int> params_jpg, params_png;
	params_jpg.push_back(IMWRITE_JPEG_QUALITY);
	params_jpg.push_back(50);
	params_png.push_back(IMWRITE_PNG_COMPRESSION); // PNG 압축레벨 설정
	params_png.push_back(9);

	imwrite("../image/write_test1.jpg", img8);			   // 행렬 영상파일로 저장
	imwrite("../image/write_test2.jpg", img8, params_jpg); // 지정화질로 저장
	imwrite("../image/write_test.png", img8, params_png);
	imwrite("../image/write_test.bmp", img8); // BMP 파일 저장
	return 0;
}