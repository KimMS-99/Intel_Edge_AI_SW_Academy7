#include <iostream>

using namespace std;

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
    Power &operator<<(int n); // 연산 후 Power 객체의 참조 리턴
};