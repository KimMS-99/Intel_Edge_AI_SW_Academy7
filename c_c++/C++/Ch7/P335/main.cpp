#include "power.h"

// 예제 7-4 두 개의 Power 객체를 더하는 + 연산자 작성
int main()
{
    Power a(3, 5), b(4, 6), c;
    c = a + b; // 파워 객체 + 연산
    a.show();
    b.show();
    c.show();
}
