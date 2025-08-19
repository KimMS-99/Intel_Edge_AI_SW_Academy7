#include <iostream>

using namespace std;
ostream &fivestar(ostream &outs)
{
	return outs << "*****";
}
ostream &rightarrow(ostream &outs)
{
	return outs << "---->";
}
ostream &beep(ostream &outs)
{
	return outs << '\a';
}

// 예제 11-12 출력 스트림에 사용되는 조작자 만들기
int main()
{
	cout << "벨이 울립니다." << beep << endl;
	cout << "C" << rightarrow << "C++" << rightarrow << "Java" << endl;
	cout << "Visual" << fivestar << "C++" << endl;
}