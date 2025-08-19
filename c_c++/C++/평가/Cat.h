#ifndef CAT
#define CAT

#include "Animal.h"

class Cat : public Animal
{
    string bark;

public:
    Cat(string name = "Cat", int age = 5, string bark = "냥"); // 디폴트 매개변수 생성자
    Cat(const Cat &cat);                                       // 복사생성자
    virtual ~Cat();                                            // 가상소멸자

    string getBark();
    void crying();
};

#endif