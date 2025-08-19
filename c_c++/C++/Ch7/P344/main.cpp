#include <iostream>
#include "power.h"

// 예제 7-8 전위 ++ 연산자 작성
int main()
{
    Power a(3, 5), b;
    a.show();
    b.show();
    b = ++a;
    a.show();
    b.show();
}