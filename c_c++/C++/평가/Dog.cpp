#include "Animal.h"
#include "Dog.h"

Dog::Dog(string name, int age, string bark) : Animal(name, age) // 생성자
{
    this->bark = bark;
}

Dog::Dog(const Dog &dog) : Animal(dog) // 복사 생성자
{
    bark = dog.bark;
}

Dog::~Dog() // 가상 소멸자
{
    cout << "Dog 소멸" << endl;
}

string Dog::getBark()
{
    return bark;
}

void Dog::crying()
{
    cout << this->getName() << "는" << bark << endl;
}
