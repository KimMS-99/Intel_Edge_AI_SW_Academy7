#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(void)
{
	Mat train = Mat_<float>({8, 2}, {150, 200, 200, 250, 100, 250, 150, 300,
									 350, 100, 400, 200, 400, 300, 350, 400});
	Mat label = Mat_<int>({8, 1}, {0, 0, 0, 0, 1, 1, 1, 1});

	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	// svm->setKernel(SVM::LINEAR); // 선형 커널
	svm->setKernel(SVM::RBF); // 방사 기저 함수 커널
	// 다양한 파라미터 값을 이용하여 여러번 학습과 검증을 반복한 후, 최적의 파라미터를 이용하여 학습을 완료한다.
	svm->trainAuto(train, ROW_SAMPLE, label);

	cout << "svm->getGamma() : " << svm->getGamma() << "\n";
	cout << "svm -> getC() : " << svm->getC() << endl;

	Mat img = Mat::zeros(Size(500, 500), CV_8UC3);

	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{
			Mat test = Mat_<float>({1, 2}, {(float)i, (float)j});
			int res = cvRound(svm->predict(test));

			if (res == 0)
				img.at<Vec3b>(j, i) = Vec3b(128, 128, 255); // R
			else
				img.at<Vec3b>(j, i) = Vec3b(128, 255, 128); // G
		}
	}

	for (int i = 0; i < train.rows; i++)
	{
		int x = cvRound(train.at<float>(i, 0));
		int y = cvRound(train.at<float>(i, 1));
		int l = label.at<int>(i, 0);

		if (l == 0)
			circle(img, Point(x, y), 5, Scalar(0, 0, 128), -1, LINE_AA); // R
		else
			circle(img, Point(x, y), 5, Scalar(0, 128, 0), -1, LINE_AA); // G
	}

	imshow("svm", img);

	waitKey();
	return 0;
}
