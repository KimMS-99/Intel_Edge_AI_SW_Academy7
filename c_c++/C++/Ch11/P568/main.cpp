#include <iostream>
#include <string>
using namespace std;

class Book
{ // 책을 표현하는 클래스
	string title;
	string press;
	string author;

public:
	Book(string title = "", string press = "", string author = "")
	{
		this->title = title;
		this->press = press;
		this->author = author;
	}
	friend ostream &operator<<(ostream &stream, const Book &b); // friend 선언
};

// << 연산자 함수
ostream &operator<<(ostream &stream, const Book &b)
{
	stream << b.title << "," << b.press << "," << b.author;
	return stream;
}

// 예제 11-10 Book 클래스를 만들고 Book 객체를 스트림에 출력하는 << 연산자 작성
int main()
{
	Book book("소유냐 존재냐", "한국출판사", "에리히프롬"); // Book 객체 생성
	cout << book;											// Book 객체 book 화면 출력
}