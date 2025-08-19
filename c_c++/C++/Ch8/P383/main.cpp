#include <iostream>
#include <string>
#include "point.h"
#include "colorpoint.h"

// 업 캐스팅과 다운캐스팅 실습
int main()
{
    ColorPoint cp;
    ColorPoint *pDer = &cp;
    pDer->set(3, 4);
    pDer->setColor("Blue");
    pDer->showColorPoint();

    Point p;
    Point *pPoint = &p;
    pPoint->set(2, 3);
    pPoint->showPoint();

    pDer = (ColorPoint *)pPoint;
    pDer->setColor("Red");  // 안되는게 맞음
    pDer->showColorPoint(); // 안되는게 맞음

    // int num = 3;
    // double db = num;

    Point *pBase = pDer; // 업 캐스팅
    // pBase.setColor("Red"); // 불가능
    // pBase.showColorPoint(); // 불가능

    pDer = (ColorPoint *)pBase; // 다운 캐스팅
    pDer->setColor("Purple");
    pDer->set(7, 8);
    pDer->showColorPoint();
    pBase->showPoint();
}