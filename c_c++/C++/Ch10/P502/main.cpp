#include <iostream>
#include <vector>

using namespace std;

// 예제 10-9 vector 컨테이너 활용
int main()
{
    vector<int> v; // 정수만 삽입 가능한 벡터 생성

    cout << "v size : " << v.size() << endl;
    cout << "v capacity : " << v.capacity() << endl;

    v.push_back(1); // 벡터에 정수 1 삽입
    v.push_back(2); // 벡터에 정수 2 삽입
    v.push_back(3); // 벡터에 정수 3 삽입

    cout << "v size : " << v.size() << endl;
    cout << "v capacity : " << v.capacity() << endl;

    for (int i = 0; i < v.size(); i++) // 벡터의 모든 원소 출력
        cout << v[i] << " ";           // v[i]는 벡터의 i번째 원소
    cout << endl;

    v[0] = 10;    // 벡터의 첫 번째 원소를 10으로 변경
    int m = v[2]; // m에 3 저장
    v.at(2) = 5;  // 벡터의 3번째 원소를 5로 변경

    for (int i = 0; i < v.size(); i++) // 벡터의 모든 원소 출력
        cout << v[i] << " ";
    cout << endl;

    cout << "m : " << m << endl;
}