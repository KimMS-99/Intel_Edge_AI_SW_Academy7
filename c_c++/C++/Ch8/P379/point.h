#ifndef POINT_H
#define POINT_H
class Point // 2차원 평면에서 한 점을 표현하는 클래스 Point tjsdjs
{
    int x, y; // 한 점 (x, y) 좌표값
public:
    void set(int x, int y);
    void showPoint();
};
#endif