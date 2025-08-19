#include <iostream>
using namespace std;

// 예제 11-1 ostream의 멤버 함수를 이용한 문자 출력
int main()
{
	// "Hi!"를 출력하고 다음 줄로 넘어간다.
	cout.put('H');
	cout.put('i');
	cout.put(33);
	cout.put('\n');

	// "C++ "을 출력한다.
	cout.put('C').put('+').put('+').put(' ');

	char str[] = "I love programming";
	cout.write(str, 6); // str 배열의 6 개의 문자 "I love"를 스트림에 출력
}