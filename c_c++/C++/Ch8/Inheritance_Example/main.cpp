#include "Car.h" // Car 클래스를 사용하기 위해 Car.h를 포함합니다. Car.h는 Vehicle.h를 이미 포함하고 있습니다.

int main()
{
    // 1. 기반 클래스(Vehicle) 객체 생성 및 사용
    std::cout << "--- 오토바이 객체 테스트 ---" << std::endl;
    // Vehicle 객체는 Vehicle 클래스에 정의된 속성과 기능만 가집니다.
    Vehicle motorcycle(2); // 바퀴 2개짜리 탈것
    motorcycle.accelerate(80);
    motorcycle.showStatus();
    std::cout << std::endl;

    // 2. 파생 클래스(Car) 객체 생성 및 사용
    std::cout << "--- 자동차 객체 테스트 ---" << std::endl;
    // Car 객체는 Vehicle의 속성과 기능을 상속받고, Car 고유의 속성과 기능도 가집니다.
    Car myCar(4); // 문 4개짜리 자동차

    // Car 객체는 Vehicle의 기능을 물려받았으므로 사용할 수 있습니다.
    // 이는 상속을 통한 코드 재사용의 예시입니다.
    myCar.accelerate(100);
    myCar.brake(30);

    // Car 객체는 자신만의 고유 기능도 사용할 수 있습니다.
    // 이는 상속을 통한 기능 확장의 예시입니다.
    myCar.openTrunk();

    // Car 객체는 재정의된 showStatus() 함수를 호출합니다.
    // 이는 다형성(Polymorphism)의 한 형태인 함수 오버라이딩(Overriding)의 예시입니다.
    myCar.showStatus();
    std::cout << std::endl;

    // 3. 업캐스팅 (Upcasting) 예제
    std::cout << "--- 업캐스팅 테스트 ---" << std::endl;
    // 파생 클래스(Car)의 객체를 기반 클래스(Vehicle)의 포인터나 참조로 다루는 것을 업캐스팅이라고 합니다.
    // 이는 항상 안전하며, 명시적인 형 변환이 필요 없습니다.
    // 업캐스팅된 포인터/참조는 기반 클래스의 멤버에만 접근할 수 있습니다.
    Vehicle *vehiclePtr = &myCar; // Car 객체를 Vehicle 포인터로 가리킴
    vehiclePtr->accelerate(20);   // Vehicle의 멤버 함수 호출 가능
    vehiclePtr->showStatus();     // Vehicle의 showStatus() (Car에서 재정의된 버전) 호출
    // vehiclePtr->openTrunk(); // 에러: Vehicle 포인터로는 Car의 고유 멤버에 접근할 수 없습니다.
    std::cout << std::endl;

    // 4. 다운캐스팅 (Downcasting) 예제
    std::cout << "--- 다운캐스팅 테스트 ---" << std::endl;
    // 기반 클래스(Vehicle)의 포인터나 참조를 파생 클래스(Car)의 포인터나 참조로 다루는 것을 다운캐스팅이라고 합니다.
    // 이는 위험할 수 있으며, 명시적인 형 변환(dynamic_cast 또는 static_cast)이 필요합니다.
    // 잘못된 객체를 다운캐스팅하면 런타임 오류가 발생할 수 있습니다.

    // static_cast를 이용한 다운캐스팅 (컴파일 시점에 타입 체크, 안전하지 않을 수 있음)
    Car *carPtrStatic = static_cast<Car *>(vehiclePtr); // vehiclePtr이 실제 Car 객체를 가리키므로 안전함
    carPtrStatic->openTrunk();                          // Car의 고유 멤버 함수 호출 가능
    carPtrStatic->showStatus();

    // dynamic_cast를 이용한 다운캐스팅 (런타임 시점에 타입 체크, 더 안전함)
    // dynamic_cast는 다형성을 위해 가상 함수가 하나 이상 필요합니다.
    // 현재 Vehicle 클래스에 가상 함수가 없으므로 dynamic_cast는 컴파일 에러를 발생시킬 수 있습니다.
    // 이 예제에서는 static_cast를 사용합니다.
    // 만약 Vehicle 클래스에 virtual 함수가 있다면, 아래와 같이 사용할 수 있습니다.
    // Car* carPtrDynamic = dynamic_cast<Car*>(vehiclePtr);
    // if (carPtrDynamic) {
    //     carPtrDynamic->openTrunk();
    // }

    // 잘못된 다운캐스팅의 예 (런타임 오류 발생 가능성)
    // Vehicle anotherVehicle(4); // 실제로는 Car 객체가 아님
    // Car* badCarPtr = static_cast<Car*>(&anotherVehicle); // 컴파일은 되지만, badCarPtr->openTrunk() 호출 시 런타임 오류 발생 가능성 높음
    // badCarPtr->openTrunk(); // 위험!

    return 0;
}
