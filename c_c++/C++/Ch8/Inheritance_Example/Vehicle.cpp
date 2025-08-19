#include "Vehicle.h"

// Vehicle 클래스의 생성자 구현
// 바퀴 수를 초기화하고, 속도를 0으로 설정합니다.
Vehicle::Vehicle(int wheels) : speed(0), numWheels(wheels) {
    std::cout << "Vehicle 객체 생성 (바퀴 " << numWheels << "개)" << std::endl;
}

// 속도를 증가시키는 멤버 함수 구현
void Vehicle::accelerate(int amount) {
    speed += amount;
}

// 속도를 감소시키는 멤버 함수 구현
void Vehicle::brake(int amount) {
    speed -= amount;
    if (speed < 0) {
        speed = 0;
    }
}

// 현재 Vehicle의 상태를 출력하는 멤버 함수 구현
void Vehicle::showStatus() const {
    std::cout << " - 속도: " << speed << " km/h" << std::endl;
    std::cout << " - 바퀴 수: " << numWheels << std::endl;
}
