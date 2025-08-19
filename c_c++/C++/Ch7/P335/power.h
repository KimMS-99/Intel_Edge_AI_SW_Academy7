#pragma once

#include <iostream>

using namespace std;

class Power
{
    int kick;
    int punch;

public:
    Power(int kick = 0, int punch = 0)
    {
        // cout << "생성자 호출" << endl;
        this->kick = kick;
        this->punch = punch;
    }
    Power(Power &p);
    void show();
    Power operator+(const Power &op2); // + 연산자 함수 선언, 매개변수를 Power& op2로 해도 됨
    Power operator+(const int x);
};