#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawLines();
void drawPolys();
void drawText1();
void drawText2();

int main(void)
{
	drawLines();
	drawPolys();
	drawText1();
	drawText2();

	return 0;
}

// 직선 그리기
void drawLines()
{
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	// 수평 방향의 직선 세 개를 서로 다른 색상과 두께로 그림.
	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);

	// 대각선 방향의 직선 세 개를 서로 다른 생상과 직선 타입으로 그림.
	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);

	// 수평 방향의 화살표 세 개를 서로 다른 색상, 길이, 화살표 길이로 그림.
	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

	// 다양한 모양의 마커를 그림.
	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

// 도형 그리기
void drawPolys()
{
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	// 사각형을 두께 2인 선으로 그림
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2);
	// 사각형을 내부를 채워서 그림
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1);

	// 반지름 30인 원을 내부를 채워서 그림
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA);
	// 반지름 6인 원을 두께 3인 선으로 그림
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);

	// 타원을 0도부터 270도까지 내부를 채워서 그림
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), FILLED, LINE_AA);
	// 타원을 두께 2인 선으로 그림
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);

	// 계단 모양의 다각형을 두께 2인 선으로 그림
	vector<Point> pts;
	pts.push_back(Point(250, 250));
	pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300));
	pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350));
	pts.push_back(Point(250, 350));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

// 다양한 폰트로 문자열 출력
void drawText1()
{
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));

	putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 400), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}

// 영상의 중앙에 문자열 출력
void drawText2()
{
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX; // 폰트 종류
	double fontScale = 2.0;				 // 크기 비율
	int thickness = 1;					 // 선 두께

	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();

	// sizeText와 sizeImg크기 정보를 이용하여 문자열을 출력할 좌표를 계산
	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(0, 255, 0), 1);

	imshow("img", img);
	waitKey();

	destroyAllWindows();
}