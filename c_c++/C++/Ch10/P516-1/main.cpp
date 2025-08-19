#include <iostream>
using namespace std;

// 예제 10-17 반지름이 r인 원의 면적을 리턴하는 람다식 만들기
int main()
{
	int num = 10;
	double pi = 3.14; // 지역 변수

	// auto calc = [pi](int r) -> double
	// { return pi * r * r; }; // 반지름이 r인 원 면적을 리턴하는 람다 함수 작성

	// auto calc = [=](int r) -> double
	// { return pi * r * r * num; };

	auto calc = [&pi](int r) -> double
	{
		pi = 4.5;
		return pi * r * r;
	};

	cout << "면적은 " << calc(3) << ", pi : " << pi; // 람다식 호출. 28.26출력
}