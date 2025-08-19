#include <iostream>

using namespace std;

void fillLine(int n = 25, char c = '*') // n개의 c 문자를 한 라인에 출력
{
    for (int i = 0; i < n; i++)
        cout << c;
    cout << endl;
}

// 예제 6-5 디폴트 매개 변수를 이용하여 중복 함수 간소화 연습
int main()
{
    fillLine();
    fillLine(10, '%');
}