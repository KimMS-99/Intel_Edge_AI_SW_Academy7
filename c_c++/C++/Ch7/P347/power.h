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
    Power operator++(int x); // 후위 ++ 연산자 함수 선언
};