#include <iostream>
#include "Adder.h"
#include "Calculator.h"

using namespace std;

// 예제 3-11 헤더 파일과 cpp 파일로 분리하기
int main()
{
    Calculator calc; // calc 객체 생성
    calc.run();      // 계산기 시작
}