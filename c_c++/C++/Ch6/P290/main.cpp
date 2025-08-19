#include <iostream>

using namespace std;

class MyVector
{
    int *p;
    int size;

public:
    MyVector(int n = 100)
    {
        p = new int[n];
        size = n;
    }
    ~MyVector() { delete[] p; }
};

// 예제 6-6 중복된 생성자들을 디폴트 매개 변수을 이용한 간소화 연습
int main()
{
    MyVector *v1, *v2;
    v1 = new MyVector();     // 디플트로 정수 배열 100 동적할당
    v2 = new MyVector(1024); // 정수 배열 1024 동적할당

    delete v1;
    delete v2;
}