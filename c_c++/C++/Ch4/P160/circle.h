#include <iostream>
using namespace std;

class Circle {
	int radius; 
public:
	Circle() {	radius = 1; }
	Circle(int r)  { radius = r; }
	void setRadius(int r)  { radius = r; } 
	double getArea(); 
}; 