#include <iostream>

using namespace std;

class Retangle
{
    int width;
    int height;

public:
    bool isSquare();
    Retangle();
    Retangle(int w, int h);
    Retangle(int v);
};
Retangle::Retangle() : Retangle(1, 1) {}
Retangle::Retangle(int w, int h)
{
    width = w;
    height = h;
}
Retangle::Retangle(int v)
{
    width = height = v;
}
bool Retangle::isSquare()
{
    if (width == height)
        return true;
    else
        return false;
}

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
}