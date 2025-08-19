#include <iostream>

using namespace std;

// 예제 2-6 cin.getline()을 이용한 문자열 입력
int main()
{
    cout << "주소를 입력하세여>>";

    char address[100];
    // cin.getline(address, 100, '\n');
    // cin.getline(address, sizeof(address), '\n'); // 키보드로부터 주소 읽기
    cin.getline(address, sizeof(address), ';'); // ; 까지 입력받음

    cout << "주소는 " << address << "입니다 \n"; // 주소 출력

    // // 첫 번째 getline
    // cin.getline(address, sizeof(address), '\n');
    // cout << "읽은 부분: " << address << endl;

    // // failbit가 세팅됐는지 확인하고 초기화
    // if (cin.fail())
    // {
    //     cin.clear(); // 스트림 상태 복구
    // }

    // // 두 번째 getline
    // cin.getline(address, sizeof(address), '\n');
    // cout << "읽은 부분: " << address << endl;
    return 0;
}