#include <iostream>

using namespace std;

class PrivateAccessError
{
private:
    int a;
    void f();
    PrivateAccessError();

public:
    int b;
    PrivateAccessError(int x);
    void g();
};
PrivateAccessError::PrivateAccessError()
{
    a = 1;
    b = 1;
}
PrivateAccessError::PrivateAccessError(int x)
{
    a = x;
    b = x;
}
void PrivateAccessError::f()
{
    a = 5;
    b = 5;
}
void PrivateAccessError::g()
{
    a = 6;
    b = 6;
}

// 예제 3-9 다음 소스에서 컴파일 오류가 발생하는 곳은 어디인가?(실행 x)
int main()
{
    // PrivateAccessError objA; // 생성자 PrivateAccessError()는 private 이므로 main()에서 호출 불가
    PrivateAccessError objB(100);
    // objB.a = 10; // a는 PrivateAccessError 클래스의 private 멤버이므로 main()에서 접근 불가.
    objB.b = 20;
    // objB.f(); // f()는 PrivateAccessError 클래스의 private 멤버이므로 main()에서 호출 불가.
    objB.g();
}