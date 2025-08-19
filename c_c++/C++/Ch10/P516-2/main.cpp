#include <iostream>
using namespace std;

// 예제 10-18 캡쳐 리스트에 참조 활용. 합을 외부에 저장하는 람다식 만들기
int main()
{
	int sum = 0; // 지역 변수

	[&sum](int x, int y)
	{ sum = x + y; }(2, 3); // 합 5를 지역변수 sum에 저장

	cout << "합은 " << sum;
}