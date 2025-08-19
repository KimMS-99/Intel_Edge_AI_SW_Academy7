#include <iostream>
using namespace std;

void showWidth()
{
	cout.width(10); // 다음에 출력되는 "Hello"를 10 칸으로 지정
	cout << "Hello" << endl;
	cout.width(5); // 다음에 출력되는 정수 12를 5 칸으로 지정
	cout << 12 << endl;

	cout << '%';
	cout.width(10); // 다음에 출력되는 "Korea/"만 10 칸으로 지정
	cout << "Korea/" << "Seoul/" << "City" << endl;
}

// 예제 11-6 width(), fill(), precision()을 사용한 포멧 출력
int main()
{
	showWidth(); // width() 사용 사례
	cout << endl;

	cout.fill('^'); // fill()을 적용한 후 width()의 사례를 보여준다.
	showWidth();
	cout << endl;

	cout.precision(5); // precision() 사용 예
	cout << 11. / 3. << endl;
}