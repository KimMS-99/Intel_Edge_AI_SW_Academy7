#include "power.h"

// 예제 7-12 a + b를 위한 + 연산자 함수를 프렌드로 작성
int main()
{
    Power a(3, 5), b(4, 6), c;
    c = a + b; // 파워 객체 더하기 연산
    a.show();
    b.show();
    c.show();
}