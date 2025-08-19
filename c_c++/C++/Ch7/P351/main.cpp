#include "power.h"

// 예제 7-11 2+a를 위한 + 연산자 함수를 프렌드로 작성
int main()
{
    Power a(3, 5), b;
    a.show();
    b.show();
    b = 2 + a; // 파워 객체 더하기 연산
    a.show();
    b.show();
}