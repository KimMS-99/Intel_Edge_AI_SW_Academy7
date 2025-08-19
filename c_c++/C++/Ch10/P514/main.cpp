#include <iostream>

using namespace std;

// 예제 10-15 매개 변수 x, y의 합을 출력하는 람다식 만들기
int main()
{
    [](int x, int y)
    { cout << "합은 " << x + y; }(2, 3); // 람다식 실행
}