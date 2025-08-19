#include <iostream>
using namespace std;

// 두 개의 제네릭 타입 T1, T2를 가지는 copy()의 템플릿
template <class T1, class T2>
void mcopy(T1 src[], T2 dest[], int n)
{ // src[]의 n개 원소를 dest[]에 복사하는 함수
	for (int i = 0; i < n; i++)
		dest[i] = (T2)src[i]; // T1 타입의 값을 T2 타입으로 변환한다.
}

// 예제 10-4 배열을 복사하는 제네릭 mcopy() 함수 만들기 연습
int main()
{
	int x[] = {1, 2, 3, 4, 5};
	double d[5];
	char c[5] = {'H', 'e', 'l', 'l', 'o'}, e[5];

	mcopy(x, d, 5); // int x[]의 원소 5개를 double d[]에 복사
	mcopy(c, e, 5); // char c[]의 원소 5개를 char e[]에 복사

	for (int i = 0; i < 5; i++)
		cout << d[i] << ' '; // d[] 출력
	cout << endl;
	for (int i = 0; i < 5; i++)
		cout << e[i] << ' '; // e[] 출력
	cout << endl;
}