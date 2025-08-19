#include <iostream>
#include "circle.h"

using namespace std;

Circle::Circle()
{
	radius = 1;
	cout << "생성자 radius : " << radius << endl;
}

Circle::Circle(int r)
{
	radius = r;
	cout << "생성자 radius : " << radius << endl;
}

Circle::~Circle()
{
	cout << "소멸자 radius : " << radius << endl;
}

double Circle::getArea()
{

	return 3.14 * radius * radius;
}
