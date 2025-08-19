#include "power.h"

// 예제 7-10 후위 ++ 연산자 작성
int main()
{
    Power a(3, 5), b;
    a.show();
    b.show();
    b = a++;  // 후위 ++ 연산자 사용
    a.show(); // a의 파워는 1 증가됨
    b.show(); // b는 a가 증가되기 이전 상태를 가짐
}