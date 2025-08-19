#include <iostream>
#include "circle.h"

using namespace std;

Circle::Circle(int r)
{
	radius = r;
	// cout << "생성자 radius : " << radius << endl;
}

Circle::Circle(const Circle &c) // 복사 생성자 구현
{
	this->radius = c.radius;
	// cout << "복사 생성자 실행 radius = " << radius << endl;
}

Circle::~Circle()
{
	// cout << "소멸자 radius : " << radius << endl;
}

double Circle::getArea()
{

	return 3.14 * radius * radius;
}
