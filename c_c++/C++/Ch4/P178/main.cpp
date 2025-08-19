#include <iostream>
#include "circle.h"

// 예제 4-7 Cicle 객체의 동적 생성 및 반환
int main()
{
    Circle *p, *q;
    p = new Circle;
    q = new Circle(30);
    if (!q)
    {
        cout << "메모리 부족" << endl;
        return 0;
    }

    cout << p->getArea() << endl
         << q->getArea() << endl;

    int *pArray = new int[10];
    memset(pArray, 0, sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        cout << "pArray[" << i << "] " << pArray[i] << endl;

    delete p;
    delete q; // 생성한 순서에 관계 없이 원하는 순서대로 delete 할 수 있음.
    delete[] pArray;
}