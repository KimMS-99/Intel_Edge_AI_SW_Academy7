#include <iostream>
#include <fstream>
using namespace std;

// 예제 12-8 read()를 이용하여 블록 단위로 텍스트 파일 읽기
int main()
{
	const char *file = "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/student.txt";

	ifstream fin;
	fin.open(file, ios::in | ios::binary); // 읽기 모드로 파일 열기
	if (!fin)
	{ // 열기 실패 검사
		cout << "파일 열기 오류";
		return 0;
	}

	int count = 0;
	char s[32]; // 블록 단위로 읽어 들일 버퍼
	while (!fin.eof())
	{						  // 파일 끝까지 읽는다.
		fin.read(s, 32);	  // 최대 32 바이트를 읽어 배열 s에 저장
		int n = fin.gcount(); // 실제 읽은 바이트 수 알아냄
		cout.write(s, n);	  // 버퍼에 있는 n 개의 바이트를 화면에 출력
		count += n;
	}

	cout << "읽은 바이트 수는 " << count << endl;
	fin.close(); // 입력 파일 닫기
}