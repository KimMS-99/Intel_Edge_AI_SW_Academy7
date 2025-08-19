#include <iostream>
#include <vector>
using namespace std;

int square(int x) { return x * x; }

// 예제 10-14 auto를 이용한 변수 선언
int main()
{
	// 기본 타입 선언에 auto 활용
	auto c = 'a';	// c는 char 타입으로 결정
	auto pi = 3.14; // pi은 double 타입으로 결정
	auto ten = 10;	// ten은 int 타입으로 결정
	auto *p = &ten; // 변수 p는 int* 타입으로 결정
	cout << c << " " << pi << " " << ten << " " << *p << endl;

	// 함수의 리턴 타입으로 추론
	auto ret = square(3); // square() 함수의 리턴 타입이 int 이므로 ret는 int로 결정
	cout << *p << " " << ret << endl;

	vector<int> v = {1, 2, 3, 4, 5}; // 벡터 v에 5개의 원소, 1,2,3,4,5 삽입
	// vector<int>::iterator it;
	// for (it = v.begin(); it != v.end(); it++)
	// 	cout << *it << " "; // 1 2 3 4 5 출력
	// cout << endl;

	// 템플릿에 auto를 사용하여 복잡한 선언의 간소화
	for (auto it = v.begin(); it != v.end(); it++)
		cout << *it << " "; // 1 2 3 4 5 출력
}