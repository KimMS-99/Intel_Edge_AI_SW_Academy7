#ifndef COLORPOINT_H
#define COLORPOINT_H
#include "point.h"
#include <string>

using namespace std;

class ColorPoint : public Point // 2차원 평면에서 컬러점을 표현하는 클래스 colorPoint. Point를 상속받으
{
    string color; // 점의 색 표현
public:
    void setColor(string color);
    void showColorPoint();
};
#endif
