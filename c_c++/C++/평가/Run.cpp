#include "Animal.h"

void running(Animal &a)
{
    cout << a.name << "가 달린다" << endl;
    // cout << a.getName() << "가 달린다" << endl;
    // cout << "Test용 나이 출력 : " << a->age << endl; // 평가랑 관련 없음.
}

void run(Animal &a)
{
    running(a);
    a.crying();
}