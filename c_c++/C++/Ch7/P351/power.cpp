#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
Power operator+(int op1, Power op2) // 외부 함수로 구현된 연산자 함수
{
    Power tmp;
    tmp.kick = op1 + op2.kick;
    tmp.punch = op1 + op2.punch;
    return tmp; // 임시 객체 리턴
}