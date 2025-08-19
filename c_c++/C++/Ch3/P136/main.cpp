#include <iostream>
#include "circle.h"

using namespace std;

// 예제 3-8 지역 객체와 전역 객체의 생성 및 소멸 순서
int main()
{
    Circle mainDonut;
    f(); // 함수 실행되고 함수 종료될때 각각 생성자 소멸자
    Circle mainPizza(30);
}
