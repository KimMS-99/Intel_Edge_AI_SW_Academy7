#include <iostream>
#include <cstring>
using namespace std;

// 예제 11-3 get(char*, int)을 이용한 문자열 입력
int main()
{
	char cmd[80];
	cout << "cin.get(char*, int)로 문자열을 읽습니다." << endl;
	while (true)
	{
		cout << "\n종료하려면 exit을 입력하세요 >> ";
		cin.get(cmd, 80); // 79개까지의 문자 읽음
		cout.write(cmd, cin.gcount());
		if (strcmp(cmd, "exit") == 0)
		{
			cout << "프로그램을 종료합니다....";
			return 0;
		}
		else			   // else 블록을 제거하면 무한루프에 빠짐
			cin.ignore(1); // 버퍼에 남아 있는 <Enter> 키 ('\n') 제거
	}
}