#include <iostream>
using namespace std;

class Point
{			  // 한 점을 표현하는 클래스
	int x, y; // private 멤버
public:
	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	friend istream &operator>>(istream &ins, Point &a);			 // friend 선언
	friend ostream &operator<<(ostream &stream, const Point &a); // friend 선언
};

istream &operator>>(istream &ins, Point &a) // 값을 저장해야 하므로 const를 붙이면 안된다.
{											// >> 연산자 함수
	cout << "x 좌표>>";
	ins >> a.x;
	cout << "y 좌표>>";
	ins >> a.y;
	return ins;
}

ostream &operator<<(ostream &stream, const Point &a)
{ // << 연산자 함수
	stream << "(" << a.x << "," << a.y << ")";
	return stream;
}

// 예제 11-11 Point객체를 스트림에서 입력받는 >> 연산자 작성
int main()
{
	Point p;   // Point 객체 생성
	cin >> p;  // >> 연산자를 호출하여 x 좌표와 y 좌표를 키보드로 읽어 객체 p 완성
	cout << p; // << 연산자를 호출하여 객체 p 출력
}
