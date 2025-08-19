#include <iostream>
#include <fstream>
using namespace std;

void showStreamState(ios &stream)
{
	cout << "eof() " << stream.eof() << endl;
	cout << "fail() " << stream.fail() << endl;
	cout << "bad() " << stream.bad() << endl;
	cout << "good() " << stream.good() << endl;
}

// 예제 12-11 스트링 상태 검사
int main()
{
	const char *noExistFile = "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/noexist.txt"; // 존재하지 않는 파일명
	const char *existFile = "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/student.txt";	  // 존재하는 파일명

	ifstream fin(noExistFile); // 존재하지 않는 파일 열기
	if (!fin)
	{ // 열기 실패 검사
		cout << noExistFile << " 열기 오류" << endl;
		showStreamState(fin); // 스트림 상태 출력

		cout << existFile << " 파일 열기" << endl;
		fin.open(existFile);
		showStreamState(fin); // 스트림 상태 출력
	}

	// 스트림을 끝까지 읽고 화면에 출력
	int c;
	while ((c = fin.get()) != EOF)
		cout.put((char)c);

	cout << endl;
	showStreamState(fin); // 스트림 출력

	fin.close();
}