#include <iostream>
#include <string>

using namespace std;

// 예제 4-11 string 클래스를 이용한 문자열 생성 및 출력
int main()
{
    // 스트링 생성
    string str;                                                   // 빈 문자열을 가진 스트링 객체 생성
    string address("서울시성북구삼선동389");                      // 한글은 UTF-8에서 보통 3바이트씩 차지
    string copyAddress(address);                                  // address의 문자열을 복사한 스트링 객체 생성
    char text[] = {'L', 'o', 'v', 'e', ' ', 'C', '+', '+', '\0'}; // C-스트링
    string title(text);                                           // "Love C++" 문자열을 가진 스트링 객체 생성
    // 스트링 출력
    cout << str << endl; // 빈 스트링. 아무 값도 출력되지 않음
    cout << address << endl;
    cout << copyAddress << endl;
    cout << title << endl;

    /* 문자열 치환 */
    // string a = "java", b = "C++";
    // a = b; // a = "C++"이 된다. a는 b를 복사한 문자열을 가진다.
    // cout << "a : " << a << ", b : " << b << endl;

    /* 문자열 비교 */
    // string name = "Kitae";
    // string alias = "kito";
    // int res = name.compare(alias); // name과 alias를 비교한다.
    // if(res == 0)
    //     cout << "두 문자열이 같다." << endl;                // name과 alias가 동일
    // else if(res < 0)
    //     cout << name << " < " << alias << endl; // name이 앞에 옴.
    // else
    //     cout << alias << " < " << name << endl; // name이 뒤에 옴

    /* 문자열 연결 */
    // string a("i");
    // a.append(" love "); // a = "I love "
    // string b(".");
    // string c;
    // c = a + b; // a, b 문자열에는 변화가 없고, c = "I love."로 변경됨
    // c += b; // b 문자열에는 변화가 없고, c = "I love.."로 변경됨
    // cout << "a : " << a << ", b : " << b << ", c : " << c << endl;

    /* 문자열 삽입 */
    // string a("I love C++");
    // a.insert(2, "really ");    // a = "I really love C++""
    // a.replace(2, 11, "study"); // a = "I study C++"
    // cout << "a : " << a << endl;

    /* 문자열 길이 */
    // string a("I study C++");
    // int length = a.length();     // 문자 개수는 11
    // int size = a.size();         // length()와 동일하게 작동
    // int capacity = a.capacity(); // 스트링 a의 현재 용량. 변할 수 있음,
    // cout << "length : " << length << ", size : " << size << ", capcity : " << capacity << endl;

    /* 문자열 삭제 */
    // string a("I study C++");
    // a.erase(0, 7); // a의 처음부터 7개의 문자 삭제. a = "C++" 로 변경
    // a.clear();     // a = "";
    // cout << "a : " << a << endl;

    /* 서브스트링 */
    // string b = "I love C++";
    // string c = b.substr(2, 4); // b의 인덱스 2에서 4개의 문자 리턴. c = "love"
    // string d = b.substr(2);    // bdml 인덱스 2에서 끝까지 문자열 리턴. d = "love C++"
    // cout << "c : " << c << ", d : " << d << endl;

    /* 문자열 검색 */
    // string e = "I love love C++";
    // int index = e.find("love"); // e에서 "love" 검색. 인덱스 2 리턴
    // index = e.find("love", index + 1); // e의 인덱스 3부터 "love" 검섹/ 인덱스 7리턴
    // index = e.find("C#"); // e에서 "C#"을 발견할 수 없음. -1 리턴
    // index = e.find('v', 7); // e의 인덱스 7부터 'v' 문자 검색. 인덱스 9 리턴

    /* 문자열의 각 문자 다루기 */
    // string f("I love C++");
    // char ch1 = f.at(7);              // 문자열 f의 인덱스 7에 있는 문자 리턴. ch1 = 'C'
    // char ch2 = f[7];                 // f.at(7)과 동일한 표현. ch2 = 'C'
    // f[7] = 'D';                      // f는 "I love D++"
    // char ch3 = f.at(f.length() - 1); // ch3은 '+'

    /* 문자열의 숫자 변환, stoi() */
    // string year = "2014";
    // int n = stoi(year); // n은 정수 2014 값을 가짐
    // cout << "n : " << n << endl;

    /* 문자 다루기 */
    // string a = "hello";
    // for (int i = 0; i < a.length(); i++)
    //     a[i] = toupper(a[i]); // a가 "HELLO"로 변경
    // cout << a;
    // if (isdigit(a[0]))
    //     cout << "숫자";
    // else if (isalpha(a.at(0)))
    //     cout << "문자";
}