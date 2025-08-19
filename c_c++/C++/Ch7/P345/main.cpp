#include <iostream>
#include "power.h"

// 예제 7-9 Power 클래스에 !연산자 작성
int main()
{
    Power a(0, 0), b(5, 5);
    if (!a)
        cout << "a의 파워가 0이다." << endl;
    else
        cout << "의 파워가 0이 아니다" << endl;
    if (!b)
        cout << "b의 파워가 0이다." << endl;
    else
        cout << "b의 파워가 0이 아니다" << endl;
}