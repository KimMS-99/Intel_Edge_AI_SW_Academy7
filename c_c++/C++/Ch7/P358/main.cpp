#include "power.h"

// 예제 7-14 참조를 리턴하는 << 연산자 작성
int main()
{
    Power a(1, 2);
    a << 3 << 5 << 6; // 객체 a에 3, 5, 6이 순서대로 더해진다.
    a.show();
}