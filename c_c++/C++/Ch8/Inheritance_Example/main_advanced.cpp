#include "Advanced_Inheritance.h"

int main() {
    std::cout << "\n===== 다중 상속 테스트 ====" << std::endl;
    DerivedMulti dm;
    dm.func1(); // Base1의 함수 호출
    dm.func2(); // Base2의 함수 호출
    dm.funcMulti(); // DerivedMulti의 함수 호출

    std::cout << "\n===== 가상 상속 테스트 (다이아몬드 문제) ====" << std::endl;
    std::cout << "--- 가상 상속 없는 경우 ---" << std::endl;
    ChildWithoutVirtual cwv;
    // cwv.common_func(); // 컴파일 에러: 모호성 (ambiguity)
    cwv.call_common_explicit(); // 명시적으로 호출해야 함

    std::cout << "\n--- 가상 상속 있는 경우 ---" << std::endl;
    ChildWithVirtual cwv_virtual;
    cwv_virtual.call_common(); // 모호성 없이 직접 호출 가능

    return 0;
}
