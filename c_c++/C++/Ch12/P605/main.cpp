#include <iostream>
#include <fstream>
using namespace std;

// 예제 12-3 get()을 이용한 텍스트 파일 읽기
int main()
{
	const char *file = "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/student.txt"; // 읽을 파일
	ifstream fin(file);
	if (!fin)
	{
		cout << file << " 열기 오류" << endl;
		return 0;
	}
	int count = 0;
	int c;
	while ((c = fin.get()) != EOF)
	{					 // EOF를 만날때까지 읽음
		cout << (char)c; // 읽은 문자를 화면에 출력
		count++;
	}
	if (fin.eof())
	{
		cout << "읽은 바이트 수는 " << count << endl;
	}

	fin.close(); // 파일 닫기
}