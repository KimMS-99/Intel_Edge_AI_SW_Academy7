#include "Advanced_Inheritance.h"

// Base1 구현
void Base1::func1() {
    std::cout << "Base1::func1() called" << std::endl;
}

// Base2 구현
void Base2::func2() {
    std::cout << "Base2::func2() called" << std::endl;
}

// DerivedMulti 구현
void DerivedMulti::funcMulti() {
    std::cout << "DerivedMulti::funcMulti() called" << std::endl;
}

// Grandparent 구현
Grandparent::Grandparent() { std::cout << "Grandparent constructor" << std::endl; }
void Grandparent::common_func() { std::cout << "Grandparent::common_func()" << std::endl; }

// Parent1 구현
Parent1::Parent1() { std::cout << "Parent1 constructor" << std::endl; }

// Parent2 구현
Parent2::Parent2() { std::cout << "Parent2 constructor" << std::endl; }

// ChildWithoutVirtual 구현
ChildWithoutVirtual::ChildWithoutVirtual() { std::cout << "ChildWithoutVirtual constructor" << std::endl; }
void ChildWithoutVirtual::call_common_explicit() {
    Parent1::common_func();
    Parent2::common_func();
}

// Parent1Virtual 구현
Parent1Virtual::Parent1Virtual() { std::cout << "Parent1Virtual constructor" << std::endl; }

// Parent2Virtual 구현
Parent2Virtual::Parent2Virtual() { std::cout << "Parent2Virtual constructor" << std::endl; }

// ChildWithVirtual 구현
ChildWithVirtual::ChildWithVirtual() { std::cout << "ChildWithVirtual constructor" << std::endl; }
void ChildWithVirtual::call_common() {
    common_func();
}