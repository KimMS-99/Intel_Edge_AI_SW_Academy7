#ifndef DOG
#define DOG

#include "Animal.h"

class Dog : public Animal
{
    string bark;

public:
    Dog(string nam = "Dog", int age = 3, string bark = "멍"); // 디폴트 매개변수 생성자
    Dog(const Dog &dog);                                      // 복사생성자
    virtual ~Dog();                                           // 가상소멸자

    string getBark();
    void crying();
};

#endif