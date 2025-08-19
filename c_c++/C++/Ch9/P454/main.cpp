#include <iostream>
using namespace std;

class Calculator
{
public:
	virtual ~Calculator() {}
	virtual int add(int a, int b) = 0;			   // 두 정수의 합 리턴
	virtual int subtract(int a, int b) = 0;		   // 두 정수의 차 리턴
	virtual double average(int a[], int size) = 0; // 배열 a의 평균 리턴. size는 배열의 크기
};

class GoodCalc : public Calculator
{
public:
	~GoodCalc() {}
	int add(int a, int b) { return a + b; }
	int subtract(int a, int b) { return a - b; }
	double average(int a[], int size)
	{
		double sum = 0;
		for (int i = 0; i < size; i++)
			sum += a[i];
		return sum / size;
	}
};

// 예제 9-6 추상 클래스 구현 연습
int main()
{
	int a[] = {1, 2, 3, 4, 5};
	Calculator *p = new GoodCalc();
	// Calculator c; // 추상 클래스 이므로 객체 생성이 안됨.
	cout << p->add(2, 3) << endl;
	cout << p->subtract(2, 3) << endl;
	cout << p->average(a, 5) << endl;
	delete p;
}