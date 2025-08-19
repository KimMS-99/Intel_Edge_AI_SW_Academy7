#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
Power::Power(Power &p)
{
    cout << "복사 생성자 호출" << endl;
    this->kick = p.kick;
    this->punch = p.punch;
}
Power Power::operator+(const Power &op2) // 매개변수를 Power& op2로 해도 됨
{
    Power tmp;                           // 임시 객체 생성
    tmp.kick = this->kick + op2.kick;    // kick 더하기
    tmp.punch = this->punch + op2.punch; // punch 더하기
    return tmp;                          // 더한 결과 리턴
}
Power Power::operator+(const int x)
{
    Power tmp;
    tmp.kick = this->kick + x;
    tmp.punch = this->punch + x;
    return tmp;
}