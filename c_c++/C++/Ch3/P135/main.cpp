#include <iostream>

using namespace std;
// C++ 구조체 선언
struct StructCircle
{
private:
    int radius;

public:
    StructCircle(int r) { radius = r; } // 구조체의 생성자
    double getArea();
};
double StructCircle::getArea()
{
    return 3.14 * radius * radius;
}

// 예제 3-10 Circle 클래스를 C++ 구조체를 이용하여 재작성
int main()
{
    StructCircle waffle(3);
    cout << "면적은 " << waffle.getArea();
}