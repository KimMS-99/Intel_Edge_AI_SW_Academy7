#include <iostream>
using namespace std;

class Circle
{
private:
	static int numOfCircles; // 생성된 원의 개수 기억
	int radius;

public:
	Circle(int r = 1); // 디폴트 매개 변수를 이용한 간소화
	Circle(const Circle &c);
	~Circle();
	void setRadius(int r) { radius = r; }
	int getRadius() { return radius; }
	double getArea();
	static int getNumOfCircles() { return numOfCircles; }
};