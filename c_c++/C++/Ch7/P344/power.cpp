#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
Power &Power::operator++() // 전위 ++ 연산자
{
    kick++;
    punch++;
    return *this;
}