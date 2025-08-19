#include <iostream>
using namespace std;

class Circle
{
	int radius;

public:
	Circle();
	Circle(int r);
	~Circle();
	void setRadius(int r) { radius = r; }
	double getArea();
};