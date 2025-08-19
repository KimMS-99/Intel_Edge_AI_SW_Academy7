#include <iostream>
using namespace std;

class Base
{
	int a;

protected:
	void setA(int a) { this->a = a; }

public:
	void showA() { cout << a; }
};

class Derived : private Base
{
	int b;

protected:
	void setB(int b) { this->b = b; }

public:
	void showB() { cout << b; }
};

int main()
{
	Derived x;
	x.a = 5;	// ① 오류
	x.setA(10); // ② 오류
	x.showA();	// ③ 오류
	x.b = 10;	// ④ 오류
	x.setB(10); // ⑤ 오류
	x.showB();	// ⑥
}