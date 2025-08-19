#include <iostream>
#include <fstream>
using namespace std;

// 그림 12-8
int main()
{
	ofstream fout;		   // 파일 출력 스트림 객체 생성
	fout.open("song.txt"); // song.txt 파일 열기
	if (!fout)
	{ // 열기가 실패한 경우
		cout << "song.txt 파일을 열 수 없다.";
		return 0;
	}
	int age = 21;
	char singer[] = "Kim";
	char song[] = "Yesterday";

	fout << age << '\n';	// 파일에 age와 '\n'을 기록한다.
	fout << singer << endl; // 파일에 singer의 문자열과 '\n'을 덧붙여 기록한다.
	fout << song << endl;	// 파일에 song 문자열과 '\n'을 덧붙여 기록한다.
	fout.close();
}