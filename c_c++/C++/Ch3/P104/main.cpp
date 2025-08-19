#include <iostream>

using namespace std;

class Circle
{
private:
    int radius;

public:
    // int radius;
    Circle(int val);
    double getArea();

    // double getArea()
    // {
    // return 3.14 * radius * radius;
    // }
};

Circle::Circle(int val)
{
    radius = val;
    return; // 생성자 함수는 값을 리턴해서는 안됨.
}

double Circle::getArea()
{
    return 3.14 * radius * radius;
}

// 예제 3-1 circle 클래스의 객체 생성 및 활용, 생성자
int main()
{
    /* 3-1 */
    // Circle donut;
    // cout << sizeof(donut) << endl;
    // donut.radius = 1;              // donut 객체의 반지름을 1로 설정
    // double area = donut.getArea(); // donut 객체의 면적 알아내기
    // cout << "donut 면적은 " << area << endl;

    // Circle pizza;
    // pizza.radius = 30;      // pizza 객체의 반지름을 30으로 설정
    // area = pizza.getArea(); // pizza 객체의 면적 알아내기
    // cout << "pizza 면적은 " << area << endl;

    /* 생성자 */
    Circle donut(1);
    double area = donut.getArea();
    cout << "donut 면적은 " << area << endl;
}