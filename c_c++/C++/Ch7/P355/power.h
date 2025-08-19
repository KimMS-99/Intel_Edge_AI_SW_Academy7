#include <iostream>

using namespace std;

class Power;

Power &operator++(Power &op);
Power operator++(Power &op, int x);

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
    friend Power &operator++(Power &op);       // 전위 ++ 연산자 함수 프렌드 선언
    friend Power operator++(Power &op, int x); // 후위 ++ 연산자 함수 프렌드 선언
};