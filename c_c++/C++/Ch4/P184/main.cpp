#include <iostream>
#include "circle.h"

// 예제 4-10 Circle 배열의 동적 생성 및 반환 응용
int main()
{
    cout << "생성하고자 하는 원의 개수?";
    int n, radius;
    cin >> n; // 원의 개수 입력
    if (n <= 0)
        return 0;

    Circle *pArray = new Circle[n]; // n 개의 Circle 배열 생성
    for (int i = 0; i < n; i++)
    {
        cout << "원" << i + 1 << ": "; // 프롬프트 출력
        cin >> radius;                 // 반지름 입력
        pArray[i].setRadius(radius);   // 각 Circle 객체를 반지름으로 초기화
    }

    int count = 0; // 카운트 변수
    Circle *p = pArray;
    for (int i = 0; i < n; i++)
    {
        cout << p->getArea() << ' '; // 원의 면적 출력
        if (p->getArea() >= 100 && p->getArea() <= 200)
            count++;
        p++;
    }
    cout << endl
         << "면적이 100에서 200 사이인 원의 개수는 " << count << endl;
    delete[] pArray;
}