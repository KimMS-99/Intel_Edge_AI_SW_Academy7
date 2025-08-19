#include <iostream>
#include <string>
#include "point.h"
#include "colorpoint.h"

// 예제 8-1 Point 클래스를 상속받는 ColorPoint클래스 만들기
int main()
{
    // Point p;             // 기본 클래스의 객체 생성
    ColorPoint cp;       // 파생 클래스의 객체 생성
    cp.set(3, 4);        // 기본 클래스의 멤버 호출
    cp.setColor("Red");  // 파생 클래스의 멤버 호출
    cp.showColorPoint(); // 파생 클래스의 멤버 호출
}