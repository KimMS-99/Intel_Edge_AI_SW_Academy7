#include "Animal.h"
#include "Cat.h"

Cat::Cat(string name, int age, string bark) : Animal(name, age) // 생성자
{
    this->bark = bark;
}

Cat::Cat(const Cat &cat) : Animal(cat) // 복사 생성자
{
    bark = cat.bark;
}

Cat::~Cat()
{
    cout << "Cat 소멸" << endl;
} // 가상소멸자

string Cat::getBark()
{
    return bark;
}

void Cat::crying()
{
    cout << this->getName() << "는" << bark << endl;
}
