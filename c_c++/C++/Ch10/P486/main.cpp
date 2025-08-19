#include <iostream>
using namespace std;

template <class T>
void print(T array[], int n)
{
	for (int i = 0; i < n; i++)
		cout << array[i] << '\t';
	cout << endl;
}

void print(char array[], int n)
{ // 템플릿 함수와 동일한 이름의 함수 중복
	for (int i = 0; i < n; i++)
		cout << (int)array[i] << '\t'; // array[i]를 int 타입으로 변환하여 정수 출력
	cout << endl;
}

// 예제 10-5 제네릭 함수와 이름이 같은 중복 함수 작성
int main()
{
	int x[] = {1, 2, 3, 4, 5};
	double d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	print(x, 5); // 템플릿으로부터 구체화한 함수 호출
	print(d, 5); // 템플릿으로부터 구체화한 함수 호출

	char c[5] = {1, 2, 3, 4, 5};
	print(c, 5); // char 배열을 숫자로 출력하는 중복 함수 호출
}