#include "Animal.h"

Animal::Animal(string name, int age) // 생성자
{
    this->name = name;
    this->age = age;
}

Animal::Animal(const Animal &animal) // 복사 생성자
{
    this->age = animal.age;
    this->name = animal.name;
}

Animal::~Animal() { cout << "Animal 소멸" << endl; } // 가상소멸자

void Animal::setName(string name)
{
    this->name = name;
}

void Animal::setAge(int age)
{
    this->age = age;
}

string Animal::getName()
{
    return name;
}

int Animal::getAge()
{
    return age;
}