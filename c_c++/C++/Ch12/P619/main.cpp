#include <iostream>
#include <fstream>
using namespace std;

// 예제 12-10 int 배열과 double 변수를 바이너리 파일에 저장하고 다시 읽기
int main()
{
	const char *file = "/Users/gasap/Desktop/Coding_study/c_c++/C++/Ch12/data.dat";

	ofstream fout;
	fout.open(file, ios::out | ios::binary); // 읽기 모드로 파일 열기
	if (!fout)
	{ // 열기 실패 검사
		cout << "파일 열기 오류";
		return 0;
	}

	int n[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	double d = 3.15;
	fout.write((char *)n, sizeof(n));	 // int 배열 n을 한 번에 파일에 쓴다.
	fout.write((char *)(&d), sizeof(d)); // double 값 하나를 파일에 쓴다.
	fout.close();

	// 배열 n과 d 값을 임의의 값으로 변경시킨다.
	for (int i = 0; i < 10; i++)
		n[i] = 99;
	d = 8.15;

	// 배열 n과 d 값을 파일에서 읽어 온다.
	ifstream fin(file, ios::in);
	if (!fin)
	{ // 열기 실패 검사
		cout << "파일 열기 오류";
		return 0;
	}

	fin.read((char *)n, sizeof(n));	   // int 배열을 한 번에 읽오 온다.
	fin.read((char *)(&d), sizeof(d)); // double 값을 읽어 온다.

	for (int i = 0; i < 10; i++) // 읽은 배열 n을 확인한다.
		cout << n[i] << ' ';
	cout << endl
		 << d << endl; // 읽은 double 값을 확인한다.
	fin.close();
}