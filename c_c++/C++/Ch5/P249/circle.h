#include <iostream>
using namespace std;

class Circle
{
	int radius;

public:
	Circle(int r = 1); // 디폴트 매개 변수를 이용한 간소화
	~Circle();
	Circle(const Circle &c);
	void setRadius(int r) { radius = r; }
	int getRadius() { return radius; }
	double getArea();
};