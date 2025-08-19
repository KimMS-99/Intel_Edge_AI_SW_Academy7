#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
Power Power::operator+(int op2)
{
    Power tmp;               // 임시 객체 생성
    tmp.kick = kick + op2;   // kick에 op2 더하기
    tmp.punch = punch + op2; // punch에 op2 더하기
    return tmp;              // 임시 객체 리턴
}