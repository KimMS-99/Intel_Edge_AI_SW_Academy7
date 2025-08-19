#include <iostream>
#include "Adder.h"
#include "Calculator.h"
using namespace std;

Adder::Adder(int a, int b)
{
    op1 = a;
    op2 = b;
}

int Adder::process()
{
    return op1 + op2;
}

void Calculator::run()
{
    cout << "두 개의 수를 입력하세요>>";
    int a, b;
    cin >> a >> b;                   // 정수 두 개 입력
    Adder adder(a, b);               // 덧셈기 생성
    cout << adder.process() << endl; // 덧셈 계산
}