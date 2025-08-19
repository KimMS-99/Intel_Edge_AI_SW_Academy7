#include <iostream>
#include <fstream>
using namespace std;

// 예제 12-5 istream의 getline()을 이용하여 텍스트 파일을 읽고 화면 출력
int main()
{
	ifstream fin("/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/student.txt");
	if (!fin)
	{
		cout << "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/student.txt 열기 실패" << endl;
		return 0;
	}

	char buf[81]; // 한 라인이 최대 80개의 문자로 구성된다고 가정
	while (fin.getline(buf, 81))
	{						 // 한 라인이 최대 80개의 문자로 구성
		cout << buf << endl; // 라인 출력
	}

	fin.close();
}