#include <iostream>

int num = 5;

int main(int argc, char *argv[])
{
    int num = 1;
    double db = 3.1415;
    std::cout << "Hello" << std::endl; // endl은 조작자
    std::cout << num << std::endl;
    std::cout.precision(3); // 조작자(자릿수)
    std::cout << db << std::endl;
    std::cout << ::num << std::endl; // ::붙이면 전역범위에 변수를 지목

    return 0;
}