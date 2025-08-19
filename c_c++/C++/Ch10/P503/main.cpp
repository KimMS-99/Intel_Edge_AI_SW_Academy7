#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 예제 10-10 문자열을 저장하는 벡터 만들기 연습
int main()
{
    vector<string> sv; // 문자열 벡터 생성
    string name;       // 사전에서 가장 뒤에 나오는 이름을 저장하기 위한 변수

    cout << "이름을 5개 입력하라" << endl;
    for (int i = 0; i < 5; i++) // 한 줄에 한 개씩 5개의 이름을 입력받음.
    {
        cout << i + 1 << ">>";
        getline(cin, name);
        sv.push_back(name); // 이름을 벡터에 삽입
    }
    name = sv.at(0); // 벡터의 첫 번째 이름
    for (int i = 1; i < sv.size(); i++)
    {
        if (name < sv[i]) // sv[i]의 문자열이 name보다 사전에서 뒤에 나옴
            name = sv[i]; // name을 sv[i]의 문자열로 변경
    }
    cout << "사전에서 가장 뒤에 나오는 이름은 " << name << endl;
}