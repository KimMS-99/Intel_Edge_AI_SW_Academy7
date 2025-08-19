#include <iostream>

using namespace std;

template <class T>
T bigger(T a, T b)
{
    if (a > b)
        return a;
    else
        return b;
}

// 예제 10-2 큰 값을 리턴하는 제네릭 bigger() 함수 만들기 연습
int main()
{
    int a = 20, b = 50;
    char c = 'a', d = 'z';
    cout << "bigger(20, 50)결과는 : " << bigger(a, b) << endl;
    cout << "bigger('a', 'z')결과는 : " << bigger(c, d) << endl;
}