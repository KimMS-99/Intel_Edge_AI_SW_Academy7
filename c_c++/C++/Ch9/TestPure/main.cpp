#include <iostream>
#include <string>

using namespace std;

// Point 클래스 정의
class Point // 2차원 평면에서 한 점을 표현하는 클래스 Point 선언
{
    int x, y; // 한 점 (x, y) 좌표값
public:
    void set(int x, int y);
    void get(int &x, int &y)
    {
        x = this->x;
        y = this->y;
    }
    virtual void derivedShow() = 0;
    void showPoint();
};
// Point 클래스 구현
void Point::set(int x, int y)
{
    this->x = x;
    this->y = y;
}
void Point::showPoint()
{
    cout << "(" << x << ", " << y << ")" << endl;
}

// ColorPoint 클래스 정의
class ColorPoint : public Point // 2차원 평면에서 컬러점을 표현하는 클래스 colorPoint. Point를 상속받으
{
    string color; // 점의 색 표현
public:
    void setColor(string color);
    void derivedShow();
};
// ColorPoint 클래스 구현
void ColorPoint::setColor(string color)
{
    this->color = color;
}
void ColorPoint::derivedShow()
{
    cout << color << ":";
    showPoint(); // Point의 showPoint() 호출
}

class LinePoint : public Point
{
    string line;

public:
    void setLine(string line) { this->line = line; }
    void derivedShow();
};
void LinePoint::derivedShow()
{
    cout << line << ":";
    showPoint(); // Point의 showPoint() 호출
}

void testShow(Point *p) // 업 캐스팅
{
    // cout << "-----testShow begin-------" << endl;
    cout << "testShow() : ";
    // p->set(5, 8);
    p->derivedShow();

    // cout << "-----testShow end---------" << endl;
}

// 순수 가상함수와 추상 클래스
int main()
{
    int getX, getY;
    ColorPoint cp;
    ColorPoint *pDer = &cp;
    pDer->set(2, 3);
    pDer->setColor("Purple");
    // pDer->showColorPoint();
    testShow(pDer);
    pDer->get(getX, getY);
    cout << "x : " << getX << ", y : " << getY << endl;

    // cout << "-----------------" << endl;

    LinePoint lp;
    LinePoint *pLin = &lp;
    pLin->set(5, 8);
    pLin->setLine("Text");
    // pLin->showLinePoint();
    testShow(pLin);
    pLin->get(getX, getY);
    cout << "x : " << getX << ", y : " << getY << endl;

    Point *pp = new ColorPoint();
    pp->set(4, 7);
    // pp->showPoint();
    pp->derivedShow();

    pp->get(getX, getY);
    cout << "x : " << getX << ", y : " << getY << endl;

    return 0;
}
