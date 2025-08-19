#include <opencv2/opencv.hpp>
#include <opencv2/freetype.hpp> // freetype 헤더 포함

using namespace cv;
using namespace std;

int main()
{
	Mat image1(300, 400, CV_8U, Scalar(255)); // 흰색바탕 영상 생성
	Mat image2(300, 400, CV_8U, Scalar(100)); // 회색바탕 영상 생성
	string title1 = "white";
	string title2 = "gray";

	// FreeType2 모듈 생성
	// - OpenCV를 WITH_FREETYPE=ON 옵션으로 빌드해야 함.
	Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
	// 한글 폰트 데이터 로드
	// - macOS에서 기본 한글 폰트 위치는 /System/Library/Fonts/AppleSDGothicNeo.ttc 등임
	ft2->loadFontData("/System/Library/Fonts/AppleSDGothicNeo.ttc", 0); // macOS 기본 한글 폰트 경로

	// 한글 텍스트 이미지에 출력
	// - 텍스트 내용: "안녕하세요 OpenCV"
	// - 위치: (20, 150) 픽셀
	// - 폰트 크기: 30 (픽셀 기준)
	// - 색상: 빨간색 (B=0, G=0, R=255)
	// - 두께: -1 (filled, 즉 내부 채움)
	// - 선형 보간: LINE_AA (anti-aliasing)
	// - 마지막 인자 true : UTF-8 인코딩 텍스트임을 명시
	ft2->putText(image1, "안녕하세요 OpenCV", Point(20, 150), 30, Scalar(0, 0, 255), -1, LINE_AA, true);

	namedWindow(title1, WINDOW_AUTOSIZE);
	namedWindow(title2, WINDOW_NORMAL);

	moveWindow(title1, 100, 200); // 윈도우 이동
	moveWindow(title2, 300, 200);

	imshow(title1, image1); // 행렬 원소를 영상으로 표시
	imshow(title2, image2);

	waitKey();
	destroyAllWindows(); // 열린 모든 윈도우 제거

	return 0;
}