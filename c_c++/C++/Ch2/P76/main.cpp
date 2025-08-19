#include <iostream>
#include <string>

using namespace std;

// 예제 2-7 string 클래스를 이용한 문자열 입력 및 다루기
int main()
{
    string song("Falling in love with you"); // 문자열 song
    string elvis("Elvis Presley");           // 문자열 elvis
    string singer;                           // 문자열 singer

    cout << song + "를 부른 가수는";                  // + 로 문자열 연결
    cout << "(힌트 : 첫 글자는 " << elvis[0] << ")?"; // []연산자 사용

    getline(cin, singer);                                     // 문자열 입력
    cout << "입력된 문자열 수는 " << singer.length() << endl; // 문자열을 세는 함수
    if (singer == elvis)                                      // 문자열 비교
        cout << "맞았습니다.";
    else
        cout << "틀렸습니다. " + elvis + "입니다." << endl; // +로 문자열 연결
}
