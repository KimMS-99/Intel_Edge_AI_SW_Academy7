#include <iostream>
#include "Animal.h"
#include "Dog.h"
#include "Cat.h"

using namespace std;

void run(Animal &a);

// 평가
int main()
{
    // Dog testDog; // 디폴트 생성자 확인용
    // Cat testCat; // 디폴트 생성자 확인용
    cout << "--추상클래스와 파생 클래스 구현--\n";
    Dog *dog = new Dog("강아지", 4, "멍멍");
    Cat *cat = new Cat("고양이", 2, "야옹");

    cout << "--매개 변수의 다형성 구현--\n";
    run(*dog);
    run(*cat);

    cout << "\n--복사생성자 직접 구현--\n";
    Dog copyDog(*dog);
    cout << copyDog.getName() << endl;
    cout << copyDog.getAge() << endl;
    cout << copyDog.getBark() << endl;

    cout << "\n--소멸자실행--\n";
    delete dog;
    delete cat;

    return 0;
}