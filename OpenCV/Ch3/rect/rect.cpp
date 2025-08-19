#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Size2d sz(100.5, 60.6);						// 사각형 크기
	Point2f pt1(20.f, 30.f), pt2(100.f, 200.f); // 시작 좌표 및 종료 좌표

	// Rect_ 객체 기본 선언 방식
	Rect_<int> rect1(10, 10, 30, 50);			// 시작좌표(10, 10)에서 너비와 높이(30,50)인 사각형 선언
	Rect_<float> rect2(pt1, pt2);				// 시작 좌표와 종료 좌표로 선언
	Rect_<double> rect3(Point2d(20.5, 10), sz); // 시작 좌표와 Size_ 객체로 선언

	// 간결 선언 방식 & 연산 적용
	Rect rect4 = rect1 + (Point)pt1;	// 시작 좌표 변경 -> 평행이동
	Rect2f rect5 = rect2 + (Size2f)sz;	// 사각형 덧셈 -> 크기 변경
	Rect2d rect6 = rect1 & (Rect)rect2; // 두 사각형 교차영역

	// 결과 출력
	cout << "rect3 = " << rect3.x << "," << rect3.y << ", ";
	cout << rect3.width << "x" << rect3.height << endl;
	// 상단 왼쪽 좌표, 하단 오른쪽 좌표
	cout << "rect4 = " << rect4.tl() << "  " << rect4.br() << endl;
	cout << "rect5 크기 = " << rect5.size() << endl;
	cout << "[rect6] = " << rect6 << endl; // 콘솔창에 Rect 객체 정보 출력
	return 0;
}