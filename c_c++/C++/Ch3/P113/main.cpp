#include <iostream>
#include <string>

using namespace std;

class Rectangle
{
private:
    int width;
    int height;

public:
    Rectangle(int h, int w); // 타겟 생성자
    Rectangle();             // 위임 생성자
    int getArea();
    void setter(int w, int h); // setter
};
// Rectangle::Rectangle() : Rectangle(1, 1) {} // 위임생성자
Rectangle::Rectangle() : width(0), height(0) {} // 생성자로 변수를 0, 0으로 초기화
// Rectangle::Rectangle(int h, int w)
// {
//     height = h;
//     width = w;
// }
Rectangle::Rectangle(int h, int w) : width(h), height(w) {} // width를 h로 height를 w로
int Rectangle::getArea()
{
    return width * height;
}
void Rectangle::setter(int w, int h)
{
    width = w;
    height = h;
}

// 예제 3-4 생성자에서 다른 생성자 호출 연습(위임 생성자 만들기 연습), p114
int main()
{
    Rectangle rect;
    // rect.width = 3;
    // rect.height = 5;
    cout << "매개변수 없는 생성자 사각형의 면적은 " << rect.getArea() << endl;
    int h, w;
    cout << "높이와 넓이 입력 : ";
    cin >> h >> w;
    rect.setter(w, h);
    cout << "setter로 입력받은 사각형의 면적은 " << rect.getArea() << endl;

    Rectangle rect2(10, 5);
    cout << "매개변수 있는 생성자 사각형의 면적은 " << rect2.getArea() << endl;
}