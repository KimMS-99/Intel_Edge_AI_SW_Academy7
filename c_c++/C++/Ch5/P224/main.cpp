#include <iostream>
#include "circle.h"

/* call by value */
void increase(Circle c)
{
    int r = c.getRadius();
    c.setRadius(r + 1);
}

/* call by address */
void increase(Circle *p)
{
    int r = p->getRadius();
    p->setRadius(r + 1);
}

// 예제 5-1 '값에 의한 호출'시 매개 변수의 생성자 실행되지 않음
int main()
{
    Circle waffle(30);
    // increase(waffle);
    increase(&waffle);
    cout << waffle.getRadius() << endl;
}