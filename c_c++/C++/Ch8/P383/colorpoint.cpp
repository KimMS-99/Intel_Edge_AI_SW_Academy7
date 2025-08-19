#include "point.h"
#include "colorpoint.h"
#include <iostream>

using namespace std;

void ColorPoint::setColor(string color)
{
    this->color = color;
}
void ColorPoint::showColorPoint()
{
    cout << color << ":";
    showPoint(); // Point의 showPoint() 호출
}