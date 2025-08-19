#include <iostream>

using namespace std;

class Power;
Power operator+(int op1, Power op2);

class Power
{
    int kick;
    int punch;

public:
    Power(int kick = 0, int punch = 0)
    {
        this->kick = kick;
        this->punch = punch;
    }
    void show();
    friend Power operator+(int op1, Power op2); // 프렌드 함수
};