#ifndef CAR_H
#define CAR_H

#include "Vehicle.h" // Vehicle 클래스를 상속받기 위해 포함합니다.
#include <string>

// Car 클래스는 Vehicle 클래스를 public으로 상속받는 파생(Derived) 클래스입니다.
// 'public' 상속은 기반 클래스의 public/protected 멤버가 파생 클래스에서도 동일한 접근 지정자를 유지함을 의미합니다.
class Car : public Vehicle {
private:
    // Car 클래스만의 고유한 속성: 문의 개수
    int numDoors;

public:
    // 생성자: 문의 개수를 인자로 받아 Car 객체를 초기화합니다.
    // Vehicle(4)를 호출하여 기반 클래스의 생성자를 명시적으로 호출하고, 바퀴 수를 4로 설정합니다.
    Car(int doors);
    // Car 클래스만의 고유한 기능: 트렁크를 여는 함수
    void openTrunk() const;
    // 기반 클래스(Vehicle)의 showStatus() 함수를 재정의(Override)합니다.
    // 이를 통해 Car 객체에 특화된 상태 정보를 출력할 수 있습니다.
    void showStatus() const;
};

#endif
