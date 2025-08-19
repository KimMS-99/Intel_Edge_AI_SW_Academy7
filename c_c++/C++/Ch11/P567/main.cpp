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
	Point(Point &p)
	{
		this->x = p.x;
		y = p.y;
		cout << " 복사 생성자 호출 " << endl;
	}
	friend ostream &operator<<(ostream &stream, Point &a); // 참조로 하면 복사생성자 생성 x
};

// << 연산자 함수
ostream &operator<<(ostream &stream, Point &a) // 참조로 안하면 복사생성자 생성
{
	stream << "(" << a.x << "," << a.y << ")";
	return stream;
}

// 예제 11-9 Point 객체를 스트림에 출력하는 << 연산자 작서
int main()
{
	Point p(3, 4);	   // Point 객체 생성
	cout << p << endl; // Point 객체 화면 출력

	Point q(1, 100), r(2, 200); // Point 객체 생성
	cout << q << r << endl;		// Point 객체들 화면 출력
}
