#include <iostream>
using namespace std;

class Adder
{
protected:
	int add(int a, int b) { return a + b; }
};

class Subtractor
{
protected:
	int minus(int a, int b) { return a - b; }
};

class Calculator : public Adder, public Subtractor
{ // 다중 상속
public:
	int calc(char op, int a, int b);
};

int Calculator::calc(char op, int a, int b)
{
	int res = 0;
	switch (op)
	{
	case '+':
		res = add(a, b);
		break;
	case '-':
		res = minus(a, b);
		break;
	}
	return res;
}

// 예제 8-7 Adder 와 Subtractor를 다중 상속받는 Calculator클래스 작성
int main()
{
	Calculator handCalculator;
	cout << "2 + 4 = " << handCalculator.calc('+', 2, 4) << endl;
	cout << "100 - 8 = " << handCalculator.calc('-', 100, 8) << endl;
}