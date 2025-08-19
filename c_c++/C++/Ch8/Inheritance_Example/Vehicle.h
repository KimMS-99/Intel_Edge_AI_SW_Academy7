#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>

// Vehicle 클래스는 모든 '탈것'의 공통적인 속성과 기능을 정의하는 기반(Base) 클래스입니다.
// 이 클래스의 멤버들은 파생 클래스(예: Car)에 의해 상속됩니다.
class Vehicle {
protected:
    // protected 멤버는 파생 클래스에서 직접 접근할 수 있도록 허용합니다.
    // 이는 외부에서는 접근할 수 없지만, 상속 관계에 있는 자식 클래스에서는 접근이 필요한 경우에 유용합니다.
    int speed;
    int numWheels;

public:
    // 생성자: Vehicle 객체 초기화 시 바퀴 수를 설정합니다.
    Vehicle(int wheels);
    // 속도를 증가시키는 함수
    void accelerate(int amount);
    // 속도를 감소시키는 함수
    void brake(int amount);
    // 현재 Vehicle의 상태를 출력하는 함수. 파생 클래스에서 재정의될 수 있습니다.
    void showStatus() const;
};

#endif

