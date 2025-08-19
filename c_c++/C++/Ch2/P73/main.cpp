#include <iostream>
#include <cstring> // strcmp() 함수를 사용하기 위한 헤더 파일

using namespace std;

// 예제 2-5 c-스트링을 이용하여 암호가 입력되면 프로그램을 종료하는 예
int main()
{
    char password[11];
    cout << "프로그램을 종료하려면 암호를 입력하세요." << endl;
    while (true)
    {
        cout << "암호>>";
        cin >> password;
        if (strcmp(password, "C++") == 0)
        {
            cout << "프로그램을 정상 종료합니다." << endl;
            break;
        }
        else
            cout << "암호가 틀립니다~~" << endl;
    }
}