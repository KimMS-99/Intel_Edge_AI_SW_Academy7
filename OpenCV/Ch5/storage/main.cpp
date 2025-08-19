#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void writeData();
void readData();

// String filename = "mydata.xml";
// String filename = "mydata.yml";
String filename = "mydata.json";

int main(void)
{
	writeData();
	readData();

	return 0;
}

void writeData()
{
	// 파일에 저장할 데이터 변수들
	String name = "Jane";
	int age = 10;
	Point pt1(100, 200);
	vector<int> scores = {80, 90, 50};
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	// FileStorage 객체를 쓰기 모드로 생성
	FileStorage fs;
	fs.open(filename, FileStorage::WRITE);

	if (!fs.isOpened())
	{
		cerr << "File open failed!" << endl;
		return;
	}

	// << 연산자로 준비한 데이터를 파일에 저장
	fs << "name" << name;
	fs << "age" << age;
	fs << "point" << pt1;
	fs << "scores" << scores;
	fs << "data" << mat1;

	fs.release();
}

void readData()
{
	// 파일에서 읽어 올 데이터를 저장할 변수들
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs(filename, FileStorage::READ); // FileStorage객체를 읽기 모드로 생성.

	if (!fs.isOpened())
	{
		cerr << "File open failed!" << endl;
		return;
	}

	// [] 연산자와 >> 연산자를 이용하여 파일에서 데이터를 읽어옴
	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();

	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "point: " << pt1 << endl;
	cout << "scores: " << Mat(scores).t() << endl;
	cout << "data:\n"
		 << mat1 << endl;
}
