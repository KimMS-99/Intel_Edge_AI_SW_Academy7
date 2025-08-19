#include <iostream>
using namespace std;

class Rect;

class RectManager
{ // RectManager 클래스 선언
public:
	bool equals(Rect r, Rect s);
	void copy(Rect &dest, Rect &src);
};

class Rect
{ // Rect 클래스 선언
	int width, height;

public:
	Rect(int width, int height)
	{
		this->width = width;
		this->height = height;
	}
	friend RectManager; // RectManager 클래스의 모든 함수를 프렌드 함수로 선언

	// friend bool equals(Rect r, Rect s); // 전역함수로 하는 방법
	// friend void copy(Rect &dest, Rect &src);
};

bool RectManager::equals(Rect r, Rect s)
{ // r과 s가 같으면 true 리턴
	if (r.width == s.width && r.height == s.height)
		return true;
	else
		return false;
}

void RectManager::copy(Rect &dest, Rect &src)
{ // src를 dest에 복사
	dest.width = src.width;
	dest.height = src.height;
}

// bool equals(Rect r, Rect s)
// { // 외부 함수
// 	if (r.width == s.width && r.height == s.height)
// 		return true;
// 	else
// 		return false;
// }

// void copy(Rect &dest, Rect &src)
// { // src를 dest에 복사
// 	dest.width = src.width;
// 	dest.height = src.height;
// }

// 예제 7-3 다른 클래스 전체를 프렌드로 선언
int main()
{
	Rect a(3, 4), b(5, 6);
	RectManager man;

	man.copy(b, a); // a를 b에 복사한다.
	if (man.equals(a, b))
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;
}