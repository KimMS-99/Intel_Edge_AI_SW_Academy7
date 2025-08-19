#include <iostream>
#include <string>

using namespace std;

class Rectangle
{
private:
    int width;
    int height;

public:
    Rectangle(int h, int w);
    Rectangle();
    int getArea();
    void setter(int w, int h); // setter
};
Rectangle::Rectangle()
{
    height = 5;
    width = 3;
}
Rectangle::Rectangle(int h, int w)
{
    height = h;
    width = w;
}
int Rectangle::getArea()
{
    return width * height;
}
void Rectangle::setter(int w, int h)
{
    width = w;
    height = h;
}

// 예제 3-2 Rectangle 클래스 만들기, setter
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

    h = 10, w = 5;
    Rectangle rect2(h, w);
    cout << "매개변수 있는 생성자 사각형의 면적은 " << rect2.getArea() << endl;
}