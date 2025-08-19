#include <iostream>
using namespace std;

class Rect;					 // forward decalaration. 이 라인이 없으면, 다음 라인에서 Rect를 참조하는 전방 참조(forward reference) 문제 발생
bool equals(Rect r, Rect s); // equals() 함수 선언

class Rect
{ // Rect 클래스 선언
	int width, height;

public:
	Rect(int width, int height)
	{
		this->width = width;
		this->height = height;
	}
	friend bool equals(Rect r, Rect s); // 프렌드 함수 선언
	bool equals(Rect r);				// 멤버 함수 선언
};

bool equals(Rect r, Rect s)
{ // 외부 함수
	if (r.width == s.width && r.height == s.height)
		return true;
	else
		return false;
}

bool Rect::equals(Rect s)
{ // 멤버 함수
	if (this->width == s.width && this->height == s.height)
		return true;
	else
		return false;
}

// 예제 7-1 프렌드 함수 만들기
int main()
{
	Rect a(3, 4), b(4, 5);
	if (a.equals(b)) // 멤버 함수 사용
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;
	if (equals(a, b)) // 외부 함수 friend 사용
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;
}