#include "power.h"

void Power::show()
{
    cout << "kick = " << kick << ", " << "punch = " << punch << endl;
}
bool Power::operator!()
{
    if (kick == 0 && punch == 0)
        return true;
    else
        return false;
}