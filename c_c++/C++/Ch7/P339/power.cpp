#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
Power &Power::operator+=(Power op2)
{
    kick = kick + op2.kick;    // kick 더하기
    punch = punch + op2.punch; // punch 더하기
    return *this;              // 합한 결과 리턴
}