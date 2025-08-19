#include <iostream>
#include <string>

using namespace std;

// Point 클래스 정의
class Point // 2차원 평면에서 한 점을 표현하는 클래스 Point 선언
{
    int x, y; // 한 점 (x, y) 좌표값
public:
    void set(int x, int y);
    void showPoint();
    virtual void testVirtual() = 0; // 순수 가상 함수
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
    void showColorPoint();
    void testVirtual() override
    {
        cout << "testVirtual()" << endl;
    }
};
// ColorPoint 클래스 구현
void ColorPoint::setColor(string color)
{
    this->color = color;
}
void ColorPoint::showColorPoint()
{
    cout << color << ":";
    showPoint(); // Point의 showPoint() 호출
}

class LinePoint : public Point
{
    string line;

public:
    void setLine(string line) { this->line = line; }
    void showLinePoint();
    void testVirtual()
    {
        cout << "testVirtual()" << endl;
    }
};
void LinePoint::showLinePoint()
{
    cout << line << ":";
    showPoint(); // Point의 showPoint 호출
}

void testShow(Point *p) // 업 캐스팅
{
    // cout << "-----testShow begin-------" << endl;
    cout << "testShow : ";
    p->set(5, 8);
    p->showPoint();

    // cout << typeid(ColorPoint).name() << endl;
    // cout << typeid(*p).name() << endl;

    if (typeid(*p) == typeid(ColorPoint))
    {
        ColorPoint *pDer = (ColorPoint *)p; // 다운캐스팅 시에는 형 변환
        pDer->showColorPoint();
    }
    else if (typeid(*p) == typeid(LinePoint))
    {
        LinePoint *pLin = (LinePoint *)p;
        pLin->showLinePoint();
    }
    // cout << "-----testShow end---------" << endl;
}

// 업 캐스팅과 다운캐스팅 실습 + 매개변수의 다형성
int main()
{
    ColorPoint cp;
    ColorPoint *pDer = &cp;
    // pDer->set(3, 4);
    pDer->setColor("Blue");
    // pDer->showColorPoint();
    testShow(pDer);

    // cout << "-----------------" << endl;

    LinePoint lp;
    LinePoint *pLin = &lp;
    // pLin->set(5, 6);
    pLin->setLine("Test");
    // pLin->showLinePoint();
    testShow(pLin);

    return 0;
}
