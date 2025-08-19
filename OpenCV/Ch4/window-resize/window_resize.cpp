#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image(300, 400, CV_8U, Scalar(255)); // 흰색 바탕 영상 생성
	string title1 = "Window-resize 1 AUTOSIZE";
	string title2 = "Window-resize 2 NORMAL";
	image = 128; // image의 픽셀값 128로 설정

	// 이미지의 좌상단 (0,0) 위치에서 시작해서 가로 3, 세로 3 크기의 영역(ROI) 지정
	// Rect(x, y, width, height) - 사각형 영역 정의
	// 이 영역에 해당하는 부분을 원본 이미지에서 잘라내어 새로운 Mat 객체로 생성(참조)
	// 즉, imageRoi는 image의 3x3 크기 부분 이미지(좌상단 영역)를 나타냄
	Mat imageRoi = image(Rect(0, 0, 3, 3));
	cout << imageRoi << endl;

	namedWindow(title1, WINDOW_AUTOSIZE); // 윈도우 크기 변경 불가
	namedWindow(title2, WINDOW_NORMAL);	  // 윈도우 크기 변경 가능
	resizeWindow(title1, 500, 200);		  // 창크기 변경
	resizeWindow(title2, 500, 200);

	imshow(title1, image);
	imshow(title2, image);
	waitKey();
	return 0;
}