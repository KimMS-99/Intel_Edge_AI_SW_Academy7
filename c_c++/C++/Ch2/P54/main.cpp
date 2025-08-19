#include <iostream>

using namespace std;

int num = 5;

int main(int argc, char *argv[])
{
    int num = 1;
    double db = 3.1415;
    cout << "Hello" << endl; // endl은 조작자
    cout << num << endl;
    cout.precision(3); // 조작자(자릿수)
    cout << db << endl;
    cout << ::num << endl; // ::붙이면 전역범위에 변수를 지목

    return 0;
}