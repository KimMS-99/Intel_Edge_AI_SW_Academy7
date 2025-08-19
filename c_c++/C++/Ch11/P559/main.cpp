#include <iostream>
using namespace std;

// 예제 11-7 매개 변수 없는 조작자 사용
int main()
{
	cout << hex << showbase << 30 << endl;
	cout << dec << showpos << 100 << endl;
	cout << true << ' ' << false << endl;
	cout << boolalpha << true << ' ' << false << endl;
}