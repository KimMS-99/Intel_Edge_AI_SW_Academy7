#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
bool Power::operator==(const Power &op2)
{
    if (kick == op2.kick && punch == op2.punch)
        return true;
    else
        return false;
}