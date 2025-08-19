#include <iostream>

using namespace std;

class Retangle
{
    int width;
    int height;

public:
    static int destructor_count; // 객체마다 따로 있는 변수가 아니라 공통된 변수 1개가 필요하기 때문에 static로 선언
    static int constructor_count;
    bool isSquare();
    Retangle();
    Retangle(int w, int h);
    Retangle(int v);
    ~Retangle();
};
// Retangle::Retangle() : Retangle(1, 1) // 생성자 위임으로 객체는 1개만 생성되지만 생성자는 두번 실행
// {
//     cout << ++constructor_count << "번째 매개변수 0 " << "width : " << width << ", height : " << height << " 생성" << endl;
//     destructor_count++;
// }
Retangle::Retangle() : Retangle(1, 1) {}
Retangle::Retangle(int w, int h)
{
    width = w;
    height = h;
    cout << ++constructor_count << "번째 생성자 매개변수 2 " << "width : " << width << ", height : " << height << " 생성" << endl;
    destructor_count++;
}
Retangle::Retangle(int v)
{
    width = height = v;
    cout << ++constructor_count << "번째 생성자 매개변수 1 " << "width : " << width << ", height : " << height << " 생성" << endl;
    destructor_count++;
}
Retangle::~Retangle()
{
    cout << destructor_count-- << "번째 소멸자 " << "width : " << width << ", height : " << height << " 소멸" << endl;
}
int Retangle::destructor_count = 0;
int Retangle::constructor_count = 0;
bool Retangle::isSquare()
{
    if (width == height)
        return true;
    else
        return false;
}
// 예제 3-7 Circle클래스에 소멸자 작성 및 실행
int main()
{
    Retangle rect1;
    Retangle rect2(3, 5);
    Retangle rect3(3);

    if (rect1.isSquare())
        cout << "rect1은 정사각형이다." << endl;
    if (rect2.isSquare())
        cout << "rect2은 정사각형이다." << endl;
    if (rect3.isSquare())
        cout << "rect3은 정사각형이다." << endl;

    return 0; // 프로그램이 종료되며 소멸자 실행(생성된 반대 순서대로 - 스택)
}