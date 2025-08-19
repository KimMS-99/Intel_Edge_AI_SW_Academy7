#include "Car.h"

// Car 클래스의 생성자 구현
// Car 객체 생성 시, 기반 클래스인 Vehicle의 생성자를 먼저 호출하여 바퀴 수를 4로 설정합니다.
// 그 후 Car 고유의 멤버인 numDoors를 초기화합니다.
Car::Car(int doors) : Vehicle(4), numDoors(doors) {
    std::cout << "-> Car 객체 생성 (문 " << numDoors << "개)" << std::endl;
}

// Car 클래스만의 고유 기능인 openTrunk() 함수 구현
void Car::openTrunk() const {
    std::cout << "트렁크를 엽니다." << std::endl;
}

// Vehicle 클래스에서 상속받은 showStatus() 함수를 재정의(Override)합니다.
// 이를 통해 Car 객체에 특화된 정보를 추가로 출력할 수 있습니다.
void Car::showStatus() const {
    std::cout << "[자동차 상태 정보]" << std::endl;
    // 기반 클래스(Vehicle)의 showStatus()를 호출하여 공통적인 상태 정보를 재사용합니다.
    Vehicle::showStatus();
    std::cout << " - 문의 수: " << numDoors << std::endl;
}
