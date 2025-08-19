#include "power.h"

// 예제 7-13 ++연산자를 프렌드로 작성한 예
int main()
{
    Power a(3, 5), b;
    b = ++a; // 전위 ++ 연산자
    a.show();
    b.show();

    b = a++; // 후위 ++ 연산자
    a.show();
    b.show();
}