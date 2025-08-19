#include <iostream>
#include <fstream>
using namespace std;

// 예제 12-2 ifstream과 >> 연산자를 이용한 텍스트 파일 읽기
int main()
{
	// 스트림 객체 생성 및 파일 열기
	// ifstream fin;
	// fin.open("/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/student.txt");
	fstream file;
	file.open("/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/student.txt",
			  ios::in | ios::out | ios::trunc | ios::binary); // trunc : 기존 파일이 존재하면 내용을 전부 지우고, 새로 쓰기를 시작.
	if (!file)
	{ // 파일 열기 실패
		cout << "파일을 열 수 없다";
		return 0;
	}

	char name[10], dept[20];
	int sid;

	file << "Test " << endl;
	file << 250708 << endl;
	file << "C++" << endl;

	file.seekg(0, ios::beg); // 파일포인터의 위치를 첫 번째 위치로 이동 후 0번째 부터

	// 파일 읽기
	file >> name; // 파일에 있는 문자열을 읽어서 name 배열에 저장
	file >> sid;  // 정수를 읽어서 sid 정수형 변수에 저장
	file >> dept; // 문자열을 읽고 dept 배열에 저장

	// 읽은 텍스트를 화면에 출력
	cout << name << endl;
	cout << sid << endl;
	cout << dept << endl;

	file.close(); // 파일 읽기를 마치고 파일을 닫는다.
}