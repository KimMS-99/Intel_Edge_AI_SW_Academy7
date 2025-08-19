#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/bit_test.jpg", IMREAD_COLOR);
	Mat logo = imread("../image/logo.jpg", IMREAD_COLOR);
	CV_Assert(image.data && logo.data);					// 예외처리
	Mat logo_th, masks[5], background, foreground, dst; // 결과 행렬

	// imshow("image", image);
	// imshow("logo", logo);
	// waitKey();

	// logo 행렬에 이진화 수행, 70보다 큰 화소는 255로 변경, 나머지는 0
	threshold(logo, logo_th, 70, 255, THRESH_BINARY); // 로고 영상 이진화
	split(logo_th, masks);							  // 로고영상 채널 분리

	// imshow("logo_th", logo_th);

	// masks[0]과 masks[1]에 대해 비트 OR 연산을 수행하여 masks[3]에 저장
	bitwise_or(masks[0], masks[1], masks[3]); // 전경통과 마스크
	// imshow("masks[3]", masks[3]);

	// masks[2] (R 채널)과 masks[3]을 OR 연산해 masks[3]에 저장
	bitwise_or(masks[2], masks[3], masks[3]);
	// imshow("masks[3]", masks[3]);

	// masks[3]의 반전 결과를 masks[4]에 저장
	bitwise_not(masks[3], masks[4]); // 배경통과 마스크
	// imshow("masks[4]", masks[4]);
	// waitKey(); // imshow를 이용하여 코드 구조 이해

	Point center1 = image.size() / 2; // 영상 중심좌표
	Point center2 = logo.size() / 2;  // 로고 중심좌표
	Point start = center1 - center2;
	Rect roi(start, logo.size()); // 로고가 위치할 관심영역

	cout << "center1 : " << center1 << "\n";
	cout << "center2 : " << center2 << "\n";
	cout << "start : " << start << endl;

	// 비트곱과 마스킹을 이용한 관심 영역의 복사
	// 로고 영상과 마스크의 AND 연산으로 전경 픽셀만 남김
	bitwise_and(logo, logo, foreground, masks[3]);
	// masks[4] (배경 마스크)를 이용해 원본 이미지의 관심 영역에서 배경만 추출
	bitwise_and(image(roi), image(roi), background, masks[4]);

	add(background, foreground, dst); // 로고 전경과 배경 합성
	dst.copyTo(image(roi));			  // 로고 합성 영상을 관심영역에 복사

	imshow("background", background);
	imshow("foreground", foreground);
	imshow("dst", dst);
	imshow("image", image);
	waitKey();
	return 0;
}