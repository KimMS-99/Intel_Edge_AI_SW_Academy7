#include <iostream>
#include "circle.h"

using namespace std;

Circle::Circle(int r)
{
	radius = r;
	numOfCircles++;
	cout << "생성자 radius : " << radius << endl;
}

Circle::Circle(const Circle &c) // 복사 생성자 구현
{
	this->radius = c.radius;
	numOfCircles++;
	cout << "복사 생성자 실행 radius = " << radius << endl;
}

Circle::~Circle()
{
	numOfCircles--; // 생성된 원의 개수 감소
	cout << "소멸자 radius : " << radius << endl;
}

double Circle::getArea()
{
	return 3.14 * radius * radius;
}

int Circle::numOfCircles = 0; // 0으로 초기화
