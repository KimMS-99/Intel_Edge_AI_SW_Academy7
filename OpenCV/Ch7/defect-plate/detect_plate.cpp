#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	while (1)
	{
		int no;
		cout << "차량 영상 번호( 0:종료 ) : ";
		cin >> no;
		if (no == 0)
			break;

		string fname = format("../test_car/%02d.jpg", no); // 영상 파일 이름 구성
		Mat image = imread(fname, 1);
		if (image.empty())
		{
			cout << to_string(no) + "번 영상 파일이 없습니다. " << endl;
			continue;
		}

		Mat gray, sobel, th_img, morph;
		// 모폴로지 연산 마스크 - 번호판 모양으로 가로로 길게 지정
		Mat kernel(5, 31, CV_8UC1, Scalar(1)); // 닫힘 연산 마스크
		cvtColor(image, gray, COLOR_BGR2GRAY); // 명암도 영상 변환

		blur(gray, gray, Size(5, 5)); // 블러링
		imshow("blur", gray);
		// 수징(dx)마스크 적용하여 수직 에지 검출
		Sobel(gray, gray, CV_8U, 1, 0, 3); // 소벨 에지 검출
		imshow("Sobel", gray);

		threshold(gray, th_img, 120, 255, THRESH_BINARY); // 이진화 수행
		// 가로로 마스크로 팽창연산 수행 - 수직엣지 가로로 길게 메워지게 됨
		morphologyEx(th_img, morph, MORPH_CLOSE, kernel); // 닫힘 연산 수행

		imshow("image", image);
		imshow("binary image", th_img), imshow("close operator", morph);
		waitKey();
	}
	return 0;
}