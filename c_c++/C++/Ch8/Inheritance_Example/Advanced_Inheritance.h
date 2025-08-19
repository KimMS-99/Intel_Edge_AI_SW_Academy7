#ifndef ADVANCED_INHERITANCE_H
#define ADVANCED_INHERITANCE_H

#include <iostream>
#include <string>

// ===== 다중 상속 예제 =====
// Base1: 첫 번째 기반 클래스
class Base1 {
public:
    void func1();
};

// Base2: 두 번째 기반 클래스
class Base2 {
public:
    void func2();
};

// DerivedMulti: Base1과 Base2를 모두 상속받는 다중 상속 클래스
// 다중 상속은 여러 기반 클래스의 기능을 하나의 파생 클래스에 통합할 때 사용됩니다.
// 하지만 이름 충돌(Diamond Problem) 등의 문제가 발생할 수 있어 주의해야 합니다.
class DerivedMulti : public Base1, public Base2 {
public:
    void funcMulti();
};

// ===== 가상 상속 예제 =====
// Problem: 다이아몬드 상속 문제 (Diamond Problem)
// Grandparent: 최상위 기반 클래스
class Grandparent {
public:
    Grandparent();
    void common_func();
};

// Parent1: Grandparent를 상속
class Parent1 : public Grandparent {
public:
    Parent1();
};

// Parent2: Grandparent를 상속
class Parent2 : public Grandparent {
public:
    Parent2();
};

// ChildWithoutVirtual: Parent1과 Parent2를 상속 (가상 상속 없음)
// 이 경우 ChildWithoutVirtual 객체는 Grandparent의 두 개의 서브오브젝트를 가지게 되어
// common_func() 호출 시 모호성(ambiguity) 문제가 발생합니다.
class ChildWithoutVirtual : public Parent1, public Parent2 {
public:
    ChildWithoutVirtual();
    // common_func()를 직접 호출하면 모호성 에러 발생
    // void call_common() { common_func(); } // 에러 발생
    void call_common_explicit();
};

// Parent1Virtual: Grandparent를 가상 상속
class Parent1Virtual : virtual public Grandparent {
public:
    Parent1Virtual();
};

// Parent2Virtual: Grandparent를 가상 상속
class Parent2Virtual : virtual public Grandparent {
public:
    Parent2Virtual();
};

// ChildWithVirtual: Parent1Virtual과 Parent2Virtual을 상속 (가상 상속 사용)
// 가상 상속을 사용하면 Grandparent의 서브오브젝트가 하나만 생성되어
// 다이아몬드 상속 문제를 해결하고 모호성을 제거합니다.
class ChildWithVirtual : public Parent1Virtual, public Parent2Virtual {
public:
    ChildWithVirtual();
    void call_common();
};

#endif // ADVANCED_INHERITANCE_H
