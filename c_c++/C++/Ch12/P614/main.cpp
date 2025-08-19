#include <iostream>
#include <fstream>
using namespace std;

// 예제 12-7 get()과 put()을 이용한 이미지 파일 복사
int main()
{
	// 소스 파일과 목적 파일의 이름
	const char *srcFile = "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/desert.jpg";
	const char *destFile = "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/copydesert.jpg";

	// 소스 파일 열기
	ifstream fsrc(srcFile, ios::in | ios::binary);
	if (!fsrc)
	{ // 열기 실패 검사
		cout << srcFile << " 열기 오류" << endl;
		return 0;
	}

	// 목적 파일 열기
	ofstream fdest(destFile, ios::out | ios::binary);
	if (!fdest)
	{ // 열기 실패 검사
		cout << destFile << " 열기 오류" << endl;
		return 0;
	}

	// 소스 파일에서 목적 파일로 복사하기
	int c;
	while ((c = fsrc.get()) != EOF)
	{				  // 소스 파일을 끝까지 한 바이트씩 읽는다.
		fdest.put(c); // 읽은 바이트를 파일에 출력한다.
	}
	cout << srcFile << "을 " << destFile << "로 복사 완료" << endl;
	fsrc.close();
	fdest.close();
}