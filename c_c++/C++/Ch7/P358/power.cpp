#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
Power &Power::operator<<(int n)
{
    kick += n;
    punch += n;
    return *this; // 이 객체의 참조 리턴
}