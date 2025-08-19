#ifndef ANIMAL
#define ANIMAL

#include <iostream>
using namespace std;

class Animal
{
    string name;
    int age;

public:
    Animal(string name = "KMS", int age = 27); // 디폴트 매개변수 생성자
    Animal(const Animal &animal);              // 복사 생성자
    virtual ~Animal();                         // 가상소멸자

    void setName(string name);
    void setAge(int age);
    string getName();
    int getAge();

    virtual void crying() = 0;

    friend void running(Animal &a);
};

#endif