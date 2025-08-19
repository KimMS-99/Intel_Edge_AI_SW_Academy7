#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void MatOp1();
void MatOp2();
void MatOp3();
void MatOp4();
void MatOp5();
void MatOp6();
void MatOp7();

int main()
{
	MatOp1();
	MatOp2();
	MatOp3();
	MatOp4();
	MatOp5();
	MatOp6();
	MatOp7();

	return 0;
}

// 행렬의 생성과 초기화
void MatOp1()
{
	Mat img1; // empty matrix

	Mat img2(480, 640, CV_8UC1);	   // unsigned char, 1-channel
	Mat img3(480, 640, CV_8UC3);	   // unsigned char, 3-channels
	Mat img4(Size(640, 480), CV_8UC3); // Size(width, height)

	Mat img5(480, 640, CV_8UC1, Scalar(128));		// initial values, 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255)); // initial values, red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1); // 0's matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);  // 1's matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);   // identity matrix

	float data[] = {1, 2, 3, 4, 5, 6};
	Mat mat4(2, 3, CV_32FC1, data);

	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<uchar>({2, 3}, {1, 2, 3, 4, 5, 6});

	mat4.create(256, 256, CV_8UC3); // uchar, 3-channels
	mat5.create(4, 4, CV_32FC1);	// float, 1-channel

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
}

// 행렬의 복사
void MatOp2()
{
	Mat img1 = imread("dog.bmp");

	// 복사 생성자와 대입 연산자를 이용하여 img1의 복사본 영상 img2, img3 생성(얕은 복사)
	Mat img2 = img1;
	Mat img3;
	img3 = img1;

	// Mat::clone()과 Mat::copyTo() 함수를 이용하여 img1의 복사본 영상 img4, img5를 생성(깊은 복사)
	Mat img4 = img1.clone();
	Mat img5;
	img1.copyTo(img5);

	img1.setTo(Scalar(0, 255, 255)); // yellow

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();
}

// 부분 행렬 추출
void MatOp3()
{
	Mat img1 = imread("cat.bmp");

	if (img1.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	// img1 영상의 (220, 120)좌표부터 340X240 크기만큼의 사각혀우 부분 영상을 추출
	Mat img2 = img1(Rect(220, 120, 340, 240));		   // 얕은 복사
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone(); // 깊은복사

	// img2 영상을 반전하여 그 결과를 다시 img2에 저장한다.
	img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
}

// 행렬의 원소 값 참조
void MatOp4()
{
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	// Mat::at()를 이용한 행렬의 원소 값 참조
	// 행렬의 모든 원소 값을 1씩 증가
	for (int j = 0; j < mat1.rows; j++)
	{
		for (int i = 0; i < mat1.cols; i++)
		{
			mat1.at<uchar>(j, i)++;
		}
	}

	// Mat::ptr()를 이용한 행렬의 원소 값 참조
	// 행렬의 모든 원소 값을 1씩 증가
	for (int j = 0; j < mat1.rows; j++)
	{
		uchar *p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++)
		{
			p[i]++;
		}
	}

	// MatIterator_ 반복자를 사용하여 Mat1행렬의 모든 원소 값을 1씩 증가시킴
	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it)
	{
		(*it)++;
	}

	cout << "mat1:\n"
		 << mat1 << endl;
}

// 행렬 정보 참조하기
void MatOp5()
{
	Mat img1 = imread("lenna.bmp");

	cout << "Width: " << img1.cols << endl;
	cout << "Height: " << img1.rows << endl;
	cout << "Channels: " << img1.channels() << endl;

	// 그레이스케일(흑백) 영상인지 컬러(BGR) 영상인지 확인
	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image." << endl;

	float data[] = {2.f, 1.414f, 3.f, 1.732f};
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n"
		 << mat1 << endl;
}

// 행렬 연산
void MatOp6()
{
	float data[] = {1, 1, 2, 3};
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n"
		 << mat1 << endl;

	Mat mat2 = mat1.inv();
	cout << "mat2:\n"
		 << mat2 << endl;

	cout << "mat1.t():\n"
		 << mat1.t() << endl;
	cout << "mat1 + 3:\n"
		 << mat1 + 3 << endl;
	cout << "mat1 + mat2:\n"
		 << mat1 + mat2 << endl;
	cout << "mat1 * mat2:\n"
		 << mat1 * mat2 << endl;
}

// 크기 및 타입 변환 함수
void MatOp7()
{
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1); // 행렬의 차입 변경

	uchar data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	Mat mat1(3, 4, CV_8UC1, data1);
	// 3x4 행렬을 1x12 행렬로 재구성 (데이터는 공유됨 - 얕은 복사)
	// 따라서 mat2의 값을 변경하면 mat1도 함께 변경됨
	Mat mat2 = mat1.reshape(0, 1);

	cout << "mat1:\n"
		 << mat1 << endl;
	cout << "mat2:\n"
		 << mat2 << endl;

	mat1.resize(5, 100);
	cout << "mat1:\n"
		 << mat1 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	cout << "mat1:\n"
		 << mat1 << endl;
}
