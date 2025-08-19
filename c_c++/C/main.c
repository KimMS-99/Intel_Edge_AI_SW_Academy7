#define _CRT_SECURE_NO_WARINGS

/************
// [0-0] Hello World 만들기
*************/

#if 0
#include <stdio.h>

int main(void)
{

    printf("Hello world");
    return 0;
}
#endif

/************
// [2-3] 제어문자를 사용한 출력
*************/

#if 0
#include <stdio.h>

int main(void)
{
    
    printf("Goot\bd\tchance\n"); // 맥에서 \b가 안먹힘
    printf("Cow\rW\a\n"); // \r 안되

    return 0;
}
#endif

/************
// [3-1] 변수 선언과 사용
*************/

#if 0
#include <stdio.h>

int main(void)
{


    int a; // 변수의 선언 : 메모리에 변수 공간을 만드는 작업
    // int형 변수 -> 4byte 크기로 메모리 준비
    a = 10; // 변수에 값을 할당
    //최초 할당은 초기화
    
    int b = a, c = a + 20;
    double da = 3.5;
    char ch = 'A';
    
    printf("변수 a의 값 : %d\n", a);
    printf("변수 b의 값 : %d\n", b);
    printf("변수 c의 값 : %d\n", c);
    printf("변수 da의 값 : %.1f\n", da);
    printf("변수 ch의 값 : %c\n", ch);
    
    return 0;
}
#endif


/************
// [3-2] char형 변수의 사용
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int ch1 = 'A';
    int ch2 = 65;
    
    printf("문자 %c의 아스키 코드 값 : %d\n", ch1, ch1);
    printf("아스키 코드 값이 %d인 문자 : %c\n", ch2, ch2);

    return 0;
}
#endif


/************
// [3-3] 여러가지 정수형 변수
*************/

#if 0
#include <stdio.h>

int main(void)
{

    short menu = 10000;
    int lotto = 2000000000;
    long people = 50000000;
    long long world_people = 7000000000;
    
    // overflow : 가장 큰 값에서 표현할 수 있는 범위를 넘으면 가장 작은 값이 됨
    // underflow : 가장 작은 값에서 표현할 수 있는 범위를 넘으면 가장 큰 값이 됨
    // short 2byte = 16bit = 2^16 = 65536 -> -32768 ~ 0 ~ 32767
    short sh = 32767;

    // %d : int형
    // %ld : long형
    // %lld : longlong형
    printf("%d\n", menu);
    printf("%d\n", lotto);
    printf("%ld\n", people);
    printf("%lld\n", world_people);
    printf("%d\n", sh);
    
    return 0;
}
#endif


/************
// [3-4] unsigned를 잘못 사용한 경우
*************/

#if 0
#include <stdio.h>

int main(void)
{

    unsigned int a; // 양수만 사용가능
    
    a = 4294967295;
    printf("%d\n", a); // 오버플로우
    printf("%u\n", a);
    
    a = -1; // 재할당
    printf("u", a); // 양수만 가능인데 unsigned를 사용하여 출력 안됨.

    return 0;
}
#endif


/************
// [3-5] 유효 숫자 확인
*************/

#if 0
#include <stdio.h>

int main(void)
{

    // 결론 : 실수는 double을 쓰자
    float ft = 1.2345678901234567890;
    double db = 1.2345678901234567890;
    long double ldb = 1.2345678901234567890;
    printf("%.20f\n", ft);
    printf("%.20lf\n", db);
    printf("%.20llf\n", ldb);

    return 0;
}
#endif


/************
// [3-6] 배열에 문자를 저장
*************/

#if 0
#include <stdio.h>

int main(void)
{

    // 배열 : []로 사용
    // 반드시 크기가 할당
    // 되도록 정적으로 할당하여야 함.
    // char 변수명[크기] -> 문자열(string)
    char fruit[7] = "orange\0";
    printf("%s\n", fruit);

    // 기본 자료형
    // 정수형 : short, int, long, longlong
    // 실수형 : double, float, longdouble
    // 문자형 : char
    
    return 0;
}
#endif


/************
// [3-7] char 배열에 문자열 복사
*************/

#define _CRT_SECURE

#if 0
#include <stdio.h>
#include <string.h> // 문자열 관련 기능들을 포함하고 있는 헤더파일
// strcpy() : 문자열 복사

int main(void)
{

    char fruit[20] = "banana";
    strcpy(fruit, "choco");
    printf("%s\n", fruit);

    return 0;
}
#endif


/************
// [3-8] const를 사용한 변수
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int income = 0;
    double tax;
    income = 400;
    // const -> 바꿀 수 없는 상수로
    const double tax_rate = 0.065;
    
    tax = income * tax_rate;
    printf("%.1lf\n", tax);
    
    income = 800;
    tax = income * tax_rate;
    printf("%.1lf\n", tax);

    return 0;
}
#endif


/************
// [3-확인문제] 2
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 0; // 0
    
    a = a + 1; // 1
    a = a + 2; // 3
    a = a + 3; // 6
    
    printf("a : %d\n", a); // a : 6

    return 0;
}
#endif


/************
// [3-확인문제] 3
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int kor = 70, eng = 80, mat = 90;
    int tot;
    
    tot = kor + eng + mat;
    
    printf("국어 : %d, 영어 : %d, 수학 : %d\n", kor, eng, mat);
    printf("총점 : %d\n", tot);

    return 0;
}
#endif


/************
// [3-9] scanf 함수를 사용한 키보드 입력
*************/

#if 0
#include <stdio.h>

int main(void)
{
    
    int age;

    printf("나이를 입력하세요 : ");
    scanf("%d", &age); // scan formatted
    printf("만 나이 : %d\n", age-2);
    
    return 0;
}
#endif


/************
// [3-10] scanf 함수를 사용한 연속 입력
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int age;
    double height;
    
    printf("나이와 키를 입력해주세요 : ");
    scanf("%d %lf", &age, &height);
    printf("나이 : %d, 키 : %lf\n", age, height);

    return 0;
}
#endif


/************
// [3-11] 문자와 문자열 입력
*************/

#if 0
#include <stdio.h>

int main(void)
{

    char grade;
    char fruit[20];
    
    scanf("%c", &grade);
    scanf("%s", fruit);
    
    printf("\n당신의 성적 : %c\n좋아하는 과일 : %s\n", grade, fruit);

    return 0;
}
#endif


/************
// [4-1]  더하기, 빼기, 곱하기, 음수 연산
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a, b;
    int sum, sub, mul, inv;
    
    a = 10;
    b = 20;
    
    sum = a + b;
    sub = a - b;
    mul = a * b;
    inv = -a;
    
    printf("%d + %d = %d\n", a, b, sum);
    printf("%d - %d = %d\n", a, b, sub);
    printf("%d * %d = %d\n", a, b, mul);
    printf("%d의 음수 변환 %d\n", a, inv);

    return 0;
}
#endif


/************
// [4-2] 나누기, 나머지 연산자
*************/

#if 0
#include <stdio.h>

int main(void)
{

    double apple;
    int banana, orange;
    
    apple = 5.0 / 2.0;
    // 1. 우항 먼저 실행 5.0 / 2.0
    // 2. 우항 연산 : 실수 / 실수 -> 실수
    // 3. 실수 결과를 apple에 대입
    banana = 5 / 2;
    // 1. 우항 먼저 실행 : 5 / 2
    // 2. 우항 연산 : 정수 / 정수 -> 정수 : 2
    // 3. 정수 결과를 banana에 대입
    
    printf("apple : %.2lf\n", apple);
    printf("banana : %d\n", banana);

    return 0;
}
#endif


/************
// [4-2-실습] 최소 동전 구하기 문제
*************/

#if 0
#include <stdio.h>

int main(void)
{

    // 자판기에 동전을 투입
    // 잔돈을 출력하는 프로그램
    
    int input = 770;
    int price = 100; // coke
    
    int change = input - price;
    
    int _500, _100, _50;
    
    _500 = change / 500;
    _100 = change % 500 / 100;
    _50 = change % 100 / 50;
    
    
    printf("자판기에 넣은 돈 : %d \n", input);
    printf("음료 가격 : %d \n", price);
    printf("잔돈 %d원, 500원 : %d개, 100원 : %d개, 50원 : %d개\n", change, _500, _100, _50);

    return 0;
}
#endif


/************
// [4-2-실습2] 시간 변환
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int time = 7533; // 총 초(seconds)의 수가 주어진다.
    // ===출력 결과 ===
    // 2시간 5분 33초
    
    printf("%d시간 %d분 %d초\n", time / 3600, time % 3600 / 60, time % 60);

    return 0;
}
#endif


/************
// [4-3] 증감 연산자의 연산
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 10, b = 10;
    
    // 증감 연산자 : 증가 연산자 + 감소 연산자
    ++a;
    --b;
    
    printf("%d %d\n", a, b);

    return 0;
}
#endif


/************
// [4-4] 전위 표기와 후위 표기를 사용한 증감 연산
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 5, b = 5;
    int prefix, postfix;
    
    prefix = (++a) * 3; // 전위형 증감 연산자
    postfix = (b++) * 3; // 후위형 증감 연산자
    
    printf("%d %d\n", prefix, postfix);
    printf("%d %d \n", a ,b);

    return 0;
}
#endif


/************
// [4-5] 관계 연산의 결괏값 확인
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 10, b = 20;
    printf("%d\n", a < b);
    printf("%d\n", a > b);
    printf("%d\n", a <= b);
    printf("%d\n", a >= b);
    printf("%d\n", a == b);
    printf("%d\n", a != b);

    return 0;
}
#endif


/************
// [4-6] 논리 연산의 결괏값 확인
*************/

#if 0
#include <stdio.h>

int main(void)
{
    
//    &&(AND) : 논리곱, 하나라도 거짓이면 거짓
//    Input Output
//    1 1     1
//    1 0     0
//    0 1     1
//    0 0     0
//    ||(OR) : 논리합, 하나라도 진실이면 진실
//    Input Output
//    1 1     1
//    1 0     1
//    0 1     1
//    0 0     0
//    !(NOT) : 논리 부정,
//    Input Output
//    1       0
//    0       1

    int a = 30;
    printf("(a > 30) && (a < 20) : %d\n", (a > 30) && (a < 20)); // 0
    printf("(a < 10) || (a > 20) : %d\n", (a < 10) || (a > 20)); // 1
    printf("!(a >= 30) : %d\n", !(a >= 30)); // 0
    
    return 0;
}
#endif


/************
// [4-확인문제2] 평균을 구해보자
*************/

#if 0
#include <stdio.h>

int main(void)
{

    // 사용자로부터 kor, eng, mat입력 받음
    // 예) 70, 80, 90
    // 출력 예) 총 점수 240점, 평균 점수 80점
    
    int kor, eng, mat;
    int tot, ava;
    
    scanf("%d %d %d", &kor, &eng, &mat);
    
    tot = kor + eng + mat;
    ava = tot / 3;
    
    printf("총 점수 : %d\n", tot);
    printf("평균 점수 : %d\n", ava);

    return 0;
}
#endif


/************
// [4-8] 형 변환 연산자가 필요한 경우
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 20, b = 3;
    double result = (double)a / b;
    
    printf("%lf\n", result);
    
    int answer = result;
    
    printf("%d\n", answer);
    

    return 0;
}
#endif


/************
// [4-9] sizeof 연산자의 사용 예
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 10;
    double b = 3.14;
    
    printf("int형 변수의 크기 : %lu\n", sizeof(a));
    printf("double형 변수의 크기 : %lu\n", sizeof(b));
    printf("정수형 상수의 크기 : %lu\n", sizeof(100));
    printf("수식의 결괏값 크기 : %lu\n", sizeof(1.5 + 3.4));
    printf("char형 자료형의 크기 : %lu\n", sizeof(char));

    return 0;
}
#endif


/************
// [4-10] 복합 대입 연산자
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int age = 25;
    // 내년 생일이 되어서 한 살 증가
    age += 1;
    
    int salary = 100000000;
    // 월급의 10% 인상해서 저장
    
    salary *= 1.1;
    
    return 0;
}
#endif


/************
// [4-11] 콤마 연산자
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 10, b = 20;
    int result;
    
    result = ++a, ++b;
    printf("%d %d %d\n", a, b, result);

    result = (++a, ++b);
    
    printf("%d %d %d\n",a, b, result);

    return 0;
}
#endif


/************
// [4-12] 조건 연산자
*************/

#if 0
#include <stdio.h>

int main(void)
{

    // 내일의 점심 메뉴 고르기
    int menu = 57;

    // 메뉴가 홀수 짝수일때 다른메뉴
    char *tomorrow_lunch_menu = menu % 2 == 0 ? "asd" : "asddfe";
    
    
    
    printf("%s\n", tomorrow_lunch_menu);

    return 0;
}
#endif


/************
// [4-12] 제목
*************/

#if 0
#include <stdio.h>

int main(void)
{

    // 사용자로 부터 두 정수 입력받아 더 큰 수 출력
    
    int a, b;
    
    scanf("%d %d", &a, &b);
    printf("큰 수 출력 %d\n", (a > b) ? a : b);

    return 0;
}
#endif


/************
// [4-12] 절댓값을 구해보자
*************/

#if 0
#include <stdio.h>

int main(void)
{

    //사용자가 입력한 정수의 절댓값 출력
    
    int a;
    
    scanf("%d", &a);
    
    printf("%d\n", (a < 0) ? a * -1 : a);

    return 0;
}
#endif


/************
// [4-13] 비트 연산식의 결과
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a = 10, b = 12;
    printf("a & b = %d\n", a & b);
    printf("a ^ b = %d\n", a ^ b);
    printf("a | b = %d\n", a | b);
    printf("~a = %d\n", ~a);
    printf("a << 1 = %d\n", a << 1);
    printf("a >> 2 = %d\n", a >> 2);

    return 0;
}
#endif


/************
// [4-13] 연산자 우선순위와 연산 방향
*************/

#if 0
#include <stdio.h>

int main(void)
{

    printf("10 / 5 * 2 = %d\n", 10 / 5 * 2); // 4
    printf("10 > 5 && 10 != 5 : %d\n", 10 > 5 && 10 != 5); // 1
    printf("10 %% 3 == 0 -> %d\n", 10 % 3 == 0); //0
    
    return 0;
}
#endif


/************
// [5-1] if문의 기본 형식
*************/

#if 0
#include <stdio.h>
#include <string.h>

int main(void)
{

    int age;
    
    printf("나이 입력 : ");
    scanf("%d", &age);
    
    char res[50];
    
    strcat(res, age >= 20 ? "성인" : "미자");
    
//    if (age >= 20) {
//        printf("성인입니다.\n");
//    }

    printf("%s", res);
    
    return 0;
}
#endif


/************
// [5-2] 공배수 출력하기
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int n;
    scanf("%d", &n);
    
    if (n % 3 == 0 && n % 5 == 0) {
        printf("3과 5의 배수입니다.");
    }

    return 0;
}
#endif


/************
// [5-3] 성인 및 미성년자 여부 파악
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int age;
    
    scanf("%d", &age);
    int price;
    
    if (age >= 20) {
        printf("성인입니다.\n");
        price = 50000;
    }
    else if (age < 20){
        printf("미성년자 입니다.\n");
        price = 30000;
    }
    else
        printf("dd");
    printf("%d \n", price);

    return 0;
}
#endif


/************
// [5-4] 홀짝
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int num1;
    
    scanf("%d", &num1);
    
    if (num1 % 2 == 0) {
        printf("짝");
    }
    else
        printf("홀");

    return 0;
}
#endif


/************
// [5-5] 마트 계산대
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int c, price = 10000;
    double rate = 0.1;
    
    scanf("%d", &c);
    
    if (c <= 10) {
        printf("%d원 입니다.\n", c * price);
    }
    else
        printf("%.0lf원 입니다.\n", c * price * (1 - rate));

    return 0;
}
#endif


/************
// [5-6] 학점 계산 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int score;
    scanf("%d", &score);
    
    if (score >= 90)
    {
        printf("A학점\n");
    }
    else if (score >= 80)
    {
        printf("B학점\n");
    }
    else if (score >= 70)
    {
        printf("C학점\n");
    }
    else
    {
        printf("F학점\n");
    }

    return 0;
}
#endif


/************
// [5-7] 마트 계산 프로그램 확장판
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int num, price = 10000;
    int member, res;
    double rate = 0.1, member_rate = 0.1;
    
    printf("개수 입력 : ");
    scanf("%d", &num);
    
    printf("회원 여부(회원 : 1, 비회원 : 0) : ");
    scanf("%d", &member);
    
    if (num > 10) {
        if (member == 1) {
            res = price * num * (1 - member_rate) * (1-rate);
        }
        else
            res = price * num * (1 - rate);

    }
    else
        if (member == 1) {
            res = price * num * (1-member_rate);
        }
        else
            res = price * num;
    
    printf("%d원 입니다\n", res);
    

    return 0;
}
#endif


/************
// [5-7.5] switch란?
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int month = 4;
    
    switch (month) {
            
        case 4:
            printf("봄\n");
            break;
        case 6:
            printf("여름\n");
            break;
            
        default:
            break;
    }

    return 0;
}
#endif


/************
// [5-8] 상금 지급 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int n;
    scanf("%d", &n);
    
    switch (n) {
        case 1:
            printf("300만원\n");
            break;
        case 2:
            printf("200만원\n");
            break;
        case 3:
            printf("100만원\n");
            break;
            
        default:
            printf("탈락");
            break;
    }

    return 0;
}
#endif


/************
// [5-확인] 자판기 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int money, menu;
    int don, d_1000, d_500, d_100;
    
    printf("금액을 입력 하시요 : ");
    scanf("%d", &money);
    
    printf("메뉴를 고르세요 \n [1]아침햇살(700원) [2]솔의눈(1000원) [3]데자와(500원) : ");
    scanf("%d", &menu);
    
    if (menu == 1) {
        don = money - 700 >= 0 ? money - 700 : money;
    }
    else if (menu == 2){
        don = money - 1000 >= 0 ? money - 1000 : money;
    }
    else if (menu == 3){
        don = money - 500 >= 0 ? money - 500 : money;
    }
    else {
        printf("없는 메뉴입니다\n");
        don = money;
    }

    d_1000 = don / 1000;
    d_500 = don % 1000 / 500;
    d_100 = don & 500 / 100;
    
    printf("잔돈 : %d원 \n", don);
    printf("천원 : %d개, 오백원 : %d개, 백원 : %d개\n", d_1000, d_500, d_100);

    return 0;
}
#endif


/************
// [5-실전] 계산기 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    char calc;
    int a, b;
    
    scanf("%d %c %d", &a, &calc, &b);
    
    
    switch (calc) {
        case '+':
            printf("%d + %d = %d\n", a, b, a + b);
            break;
        case '-':
            printf("%d - %d = %d\n", a, b, a - b);
            break;
        case '/':
            printf("%d / %d = %d\n", a, b, a / b);
            break;
        case '*':
            printf("%d * %d = %d\n", a, b, a * b);
            break;
        default:
            break;
    }

    return 0;
}
#endif


/************
// [6-1] 자릿수 계산 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int n, count = 0;
    
    scanf("%d", &n);
    
    while (n != 0) {
        count++;
        n /= 10;
    }
    printf("%d", count);
    

    return 0;
}
#endif


/************
// [6-2] 10보다 작은 값 입력 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int num;
    scanf("%d", &num);
    
    while (num < 10) {
        scanf("%d", &num);
    }

    return 0;
}
#endif


/************
// [6-3] 누적합 출력 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int n, sum = 0;
    printf("정수 입력 : ");
    scanf("%d", &n);
    
    while (n != -1) {
        sum += n;
        printf("누적 결과 : %d\n", sum);
        printf("정수 입력 : ");
        scanf("%d", &n);
    }

    printf("종료돠었습니다.\n");
    
   return 0;
}
#endif


/************
// [6-4] for문 연습
*************/

#if 0
#include <stdio.h>

int main(void)
{

    for (int i = 1; i <= 10; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    for (int i = 21; i <= 57; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    for (int i = 95; i >= 53; i--) {
        printf("%d ", i);
    }
    printf("\n\n");
        
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n\n");
    
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n\n");
    
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            continue;
        }            printf("%d ", i);

    }
    printf("\n\n");
    
    for (int i = 1; i <= 100; i++) {
        if (i % 3 != 0) {
            printf("%d ", i);
        }
    }
    printf("\n\n");

    return 0;
}
#endif


/************
// [6-5]   배수 출력하기
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= 10; i++) {
        printf("%d ", i * n);
    }

    return 0;
}
#endif


/************
// [6-6] 구구단
*************/

#if 0
#include <stdio.h>

int main(void)
{

    for (int i = 1; i <= 9; i++) {
        printf("%d x %d = %d\n", 2, i, 2 * i);
    }

    return 0;
}
#endif


/************
// [6-7] 약수 출력하기
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n/2; i++) { // 약수에 자기자신을 제외하고 가장 큰 수는 n/2를 넘지 않는다.
        if (n % i == 0) {
            printf("%d ", i);
        }
    }
    printf("%d\n", n);

    return 0;
}
#endif


/************
// [6-권장] 권장규칙!
*************/

#if 0
#include <stdio.h>

int main(void)
{

    // 메모장에 적어두었음

    return 0;
}
#endif


/************
// [6-유지보수] do ~ while 누적합
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int sum = 0, n;
    do {
        scanf("%d", &n);
        sum += n;
        printf("누적 합 : %d\n", sum);
    } while (n != -1);

    return 0;
}
#endif


/************
// [6-많이써요] 무한 반복문
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int num, sum = 0;
    while (1) {

        printf("정수 입력 : ");
        scanf("%d", &num);
        if (num == -1) {
            break;
        }
        sum += num;
        printf("누적 합계 %d\n", sum);
    }
    printf("종료\n");

    return 0;
}
#endif


/************
// [6-8] 다이어트 관리 프로그램
*************/

#if 0
#include <stdio.h>

int main(void)
{

    int a, b, count = 0, gam; // a: 현재 몸무게, b : 목표 몸무게
    
    printf("현재 몸무게 : ");
    scanf("%d", &a);
    
    printf("목표 몸무게 : ");
    scanf("%d", &b);
    
    while (1) {
        
        count++;
        printf("%d주차 감량 몸무게 : ", count);
        scanf("%d", &gam);
        a -= gam;
        if (a <= b) {
            
            break;
        }
    }
    printf("%dkg달성 ㅊㅊ", a);

    return 0;
}
#endif


/************
// [6-9] 로그인 프로그램
*************/

#if 0
#include <stdio.h>
#include<string.h>

int main(void)
{

    char id[50], pw[50];
    
    while (1) {
        printf("id : ");
        scanf("%s", id);
        printf("pw : ");
        scanf("%s", pw);
        
        if (!(strcmp(id, "ididid")) && !(strcmp(pw, "pwpwpw")))
        {
            printf("로그인 성공\n");
            break;
        }
        else
        {
            printf("로그인 실패\n");
        }
    }

    return 0;
}
#endif


/************
// [6-11] 별 기초
*************/

#if 0
#include <stdio.h>

int main(void)
{

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("*");
        }
        printf("\n");
    }
    

    return 0;
}
#endif


/************
// [6-13] 별 응용
*************/

#if 0
#include <stdio.h>

int main(void)
{

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            printf("*");
        }printf("\n");
    }

    return 0;
}
#endif


/************
// [6-11] 구구단 전부 출력
*************/

#if 0
#include <stdio.h>

int main(void)
{

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            printf("%d x %d = %d\n", i, j, i * j);
        }
        
    }

    return 0;
}
#endif


/************
// [7-1] 두 정수의 합을 반환하는 함수
*************/

#if 0
#include <stdio.h>

int f_sum(int a, int b);

int main(void)
{

    int n1, n2, sum;
    
    scanf("%d %d", &n1, &n2);
    
    sum = f_sum(n1, n2);
    
    printf("%d + %d = %d\n", n1, n2, sum);

    return 0;
}

int f_sum(int a, int b)
{
    return a + b;
}
#endif


/************
// [7-확인] 두 실수의 평균을 반환하는 함수
*************/

#if 0
#include <stdio.h>

double average(double n1, double n2);

int main(void)
{

    printf("%.2lf\n", average(1.5, 3.4));

    return 0;
}

double average(double n1, double n2)
{
    return (n1 + n2) / 2;
}
#endif


/************
// [7-2] 매개변수가 없는 함수
*************/

#if 0
#include <stdio.h>

int num(void);

int main(void)
{

    printf("%d\n", num());

    return 0;
}

int num(void){
    
    int input;
    printf("양수 입력 ㅣ ");
    scanf("%d", &input);
    
    return input;
}
#endif


/************
// [7-3] 반환값이 없는 함수
*************/

#if 0

#include <stdio.h>

void output(int n, char c);

int main(void)
{

    int nm;
    char cm;
    
    scanf("%d %c", &nm, &cm);
    for (int i = 1; i <= nm; i++) {
        output(i, cm);
    }

    return 0;
}

// 문자와 개수를 전달하면 가로로 출력하는 함수
void output(int n, char c)
{
    for (int i = 0; i < n; i++) {
        printf("%c ", c);
    }
    printf("\n");
}

#endif


/************
// [7-4] 매개변수와 반환값이 모두 없는 함수
*************/

#if 0
#include <stdio.h>

void print_line(void);

int main(void)
{

    print_line();
    printf("이름  학번  전공  mbti\n");
    print_line();


    return 0;
}

void print_line(void)
{
    
    for (int i = 0; i < 30; i++) {
        printf("-");
    }
    printf("\n");
}

#endif


/************
// [7-5] 재귀 함수
*************/

#if 0
#include <stdio.h>

int fibonacci(int num);

int main(void)
{

    printf("%d\n", fibonacci(20));

    return 0;
}

int fibonacci(int num){
    
    if (num <= 2) {
        return 1;
    }
    
    return fibonacci(num-2) + fibonacci(num - 1);
}

#endif


/************
// [7-6] 함수 연습 1
 절댓값 반환
*************/

#if 0

int abs(int n);

#include <stdio.h>

int main(void)
{

    printf("%d\n", abs(-20));

    return 0;
}

int abs(int n)
{
    if (n < 0) {
        return -n;
    }
    else{
        return n;
    }
}

#endif


/************
// [7-7] 완전수 구허기
*************/

#if 0

#include <stdio.h>

int is_divisor(int num1, int num2);
void print_divisor(int num);
int get_sum_of_divisors(int num);
int is_perfect_number(int num);

int main(void)
{

    printf("%d\n", is_divisor(10, 2));
    print_divisor(10);
    printf("%d\n", get_sum_of_divisors(28));
    for (int i = 2; i < 10000; i++) {
        if (is_perfect_number(i) == 1) {
            printf("완전수 : %d\n", i);
        }
    }

    return 0;
}

// step1. n2가 n1에 약수라면 1 아니라면 0
int is_divisor(int num1, int num2)
{
    return num1 % num2 == 0 ? 1 : 0;
}

// step2. 약수들을 출력
void print_divisor(int num)
{
    int s = num / 2;
    
    printf("%d의 약수 : ", num);
    
    for (int i = 1; i <= s; i++) {
        if (num % i == 0) {
            printf("%d ", i);
        }
    }
    printf("%d\n", num);
}

// step3. get_sum_of_divisors(num)
int get_sum_of_divisors(int num)
{
    int s = num / 2, sum = 0;
    
    printf("%d의 약수 : ", num);
    
    for (int i = 1; i <= s; i++) {
        if (is_divisor(num, i)) {
            sum += i;
        }
    }
    return sum + num;
}

// step4. is_perfect_number(num)
int is_perfect_number(int num)
{
    int s = num / 2, sum = 0;
        
    for (int i = 1; i <= s; i++) {
        if (is_divisor(num, i)) {
            sum += i;
        }
    }
    return sum == num ? 1 : 0;
}

#endif


/************
// [6-9?] Up-Down 프로그램
*************/

#if 0

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{

    int n, r, count = 0;
    srand(time(NULL));
    r = rand() % 100 + 1;
    
    while (1) {
        printf("입력 : ");
        scanf("%d", &n);
        
        count++;
        
        if (n == r) {
            printf("*%d번 만에 정답*\n", count);
            break;
        }
        else if (n > r)
        {
            printf("더 작음\n");
        }
        else
        {
            printf("더 큼\n");
        }
        
        
    }

    return 0;
}

#endif


/************
// [8-1] 배열의 선언과 사용
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int num;
    num = 10;
    num = 20;
    
    printf("%d\n", num);
    
    int array[5] = {1, 2, 3, 4, 5};
    array[0] = 10;
    array[1] = 20;
    array[2] = 50;
    array[3] = 70;
    array[4] = 100;
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    
   // printf("%d %d\n", array[0], array[1]);
//    printf("%d %d %d\n", array[2], array[3], array[4]);
//    printf("%d\n", array[5]);

    return 0;
}

#endif


/************
// [8-2] 배열의 선언과 사용
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int array[5] = {8, 4, 99, 6, 7};
    
    printf("array배열의 홀수는 : ");
    
    for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
        if (array[i] % 2 == 1) {
            printf("%d ", array[i]);
        }
    }
    printf("이다.\n");

    return 0;
}

#endif


/************
// [8-3] sizeof 연산자를 이용한 배열
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int scores[5], length = sizeof(scores) / sizeof(int), total = 0;
    
    for (int i = 0; i < length; i++) {
        printf("%d과목 성적을 입력 : ", i+1);
        scanf("%d", &scores[i]);
        total += scores[i];
    }
    printf("총점 : %d, 평점 : %d\n", total, total/length);

    return 0;
}

#endif


/************
// [8-4] char형 배열의 선언과 초기화
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char fruit[6] = {'a', 'p', 'p', 'l', 'e'};
    char fruit_2[6] = "apple";
    
    printf("%s\n", fruit);
    printf("%s\n", fruit_2);
    
    char my_name[10];
    my_name[0] = 'k';
    my_name[1] = 'm';
    my_name[2] = 's';
    my_name[3] = '\0';
    
    printf("%s\n", my_name);

    return 0;
}

#endif


/************
// [8-5] 문자열을 대입하는 strcpy 함수
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char cat_name[100] = "이름을 지어주세요.";
    char name[100];
    
    printf("%s : ", cat_name);
    scanf("%s", name);
    
    strcpy(cat_name, name);
    
    printf("고양이 : %s\n", cat_name);

    return 0;
}

#endif


/************
// [8-6] 띄어쓰기까지 입력 받자!
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char inputs[100];
    
    printf("내일의 점심 메뉴 입력 : ");
    gets(inputs);
    puts(inputs);

    return 0;
}

#endif


/************
// [8-도전] 대소문자 변환 프로그램
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char s[100] = "HELLo worlD!!";
    int count = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] <= 97 && s[i] >= 65) {
            s[i] = s[i]+32;
            count++;
        }
    }
    printf("바뀐 문자 수 : %d\n바뀐 문장 : %s\n", count, s);
    

    return 0;
}

#endif


/************
// [8-5] 기본 정렬
*************/

#if 0

#include <stdio.h>

// 버블정렬(bubble sort)
int main(void)
{

    int a[6] = {1, 13, 21, 7, 31, 28}, temp;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5-i; j++) {
            if (a[j] > a[j+1]) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}



#endif


/************
// [9-1] 변수 메모리 주소 확인
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a; // 4byte 정수형 메모리
    double b; // 8byte 실수형 메모리
    char c; // 1byte 문자형 메모리
    
    printf("a의 주소  : %u\n", &a);
    printf("b의 주소  : %u\n", &b);
    printf("c의 주소  : %u\n", &c);

    return 0;
}

#endif


/************
// [9-2] 포인터 선언과 사용
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a = 10; // 변수의 선언
    int *pa; // 포인터 선언
    
    pa = &a; // a의 주소값을 포인터 pa에 담겠다.
    *pa = a;
    
    printf("p에 들어있는 값 : %d\n", pa);
    printf("a에 들어 있는 값 : %d\n", *pa);
    

    return 0;
}

#endif


/************
// [9-3] 포인터를 사용한 두 정수의 합과 평균 계산
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a = 10, b = 15, total;
    int *pa, *pb, *pt;
    
    double avg;
    double *pg;
    
    // 1. pa, pb, pt, pg 를 각각 초기화
    // 2. 간접 참조 연산자 *를 활용하여
    // total에 a + b를 대입
    // 3. 간접 참조 연산자 *를 활용하여
    // avg에 a와 b의 평균을 대입
    
    pa = &a;
    pb = &b;
    pt = &total;
    
    *pt = *pa + *pb;
    pg = &avg;
    
    *pg = *pt / 2.0;
    
    printf("두 정수의 값 : %d %d\n", a, b);
    printf("두 정수의 총합 : %d\n", total);
    printf("두 정수의 : 평균 %.1lf\n", avg);

    return 0;
}

#endif


/************
// [9-4] 포인터에 const 사용
*************/

#if 0

#include <stdio.h>

int main(void)
{

    const int num = 10;
    int a = 10, b = 20;
    const int *pt = &a;
    
    printf("a의 값 : %d\n", *pt);
    
    pt = &b;
    printf("b의 값 : %d\n", *pt);
    
    pt = &a;
    a = 7;
    printf("a의 값 : %d\n", *pt);
    
//    *pt = 77; // const로 선언해서 재할당 불가

    return 0;
}

#endif


/************
// [9-5] 주소와 포인터의 크기
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a;
    char c;
    double b;
    
    int *pa = &a;
    char *pc = &c;
    double *pb = &b;
    
    // 주소의 크기

    printf("a주소 : %d b주소 :  %d c주소 :  %d\n", sizeof(&a), sizeof(&b), sizeof(&c));
    printf("a포인터 : %d b포인터 :  %d c포인터 :  %d\n", sizeof(pa), sizeof(pb), sizeof(pc));
    printf("a값 : %d, b값 : %d, c깂 : %d\n", sizeof(*pa), sizeof(*pb), sizeof(*pc));

    return 0;
}

#endif


/************
// [9-6] 허용되지 않은 포인터의 대입
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a = 5;
    int *pa = &a;
    double *pd;
    
    pd = (double *)pa;
    
    printf("%lf\n", *pd);
    
    int *pb;
    pb = pa;
    
    printf("%d\n", *pb);

    return 0;
}

#endif


/************
// [9-7] 포인터를 사용한 두 변수의 값 교환
*************/

#if 0

#include <stdio.h>

void swap(int *pa, int *pb);

int main(void)
{

    int a = 10, b = 20, temp;
    swap(&a, &b);
//    temp = a;
//    a = b;
//    b = temp;
    printf("%d, %d\n", a, b);

    return 0;
}

void swap(int *pa, int *pb)
{
    int temp;
    
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

#endif


/************
// [9-8, 9] 다른 함수의 변수 사용하기
*************/

#if 0

void swap(int a, int b);

#include <stdio.h>

int main(void)
{

    int a = 10, b = 20;
//    swap(a, b);
    printf("a : %d, b : %d\n", a, b);

    return 0;
}

//void swap(int a, int b)
//{
//    int t;
//    
//    t = a;
//    a = b;
//    b = t;
//}

void swap()
{
    int t;
    
    t = a;
    a = b;
    b = t;
}

#endif


/************
// [9-도전] 미니 정렬 프로그램
*************/

#if 0

#include <stdio.h>

void swap(int *pa, int *pb);
void descending(int *max, int *mid, int *min);

int main(void)
{

    int a, b, c;
    
    printf("정수 입력 : ");
    scanf("%d %d %d", &a, &b, &c);
    descending(&a, &b, &c);
    printf("정렬 결과 : %d %d %d\n", a, b, c);

    return 0;
}

void swap(int *pa, int *pb)
{
    
    int temp;
    
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void descending(int *max, int *mid, int *min)
{
    
    while (1) {
        
        if (*min > *mid) {
            
            swap(mid, min);
        }
        if (*mid > *max) {
            
            swap(max, mid);
        }
        if (*max > *mid && *mid > *min) {
            break;
        }
    }
}

#endif


/************
// [10-1] 배열명에 정수 연산을 수행해 배열 요소 사용
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int ary[3]; // 3칸짜리 int형 배열 선언(총 12byte)
    
    printf("ary : %d\n", ary);
    printf("&ary[0] : %d\n", &ary[0]);
    printf("ary + 1 : %d\n", ary+1);
    
    ary[0] = 10;
    *(ary + 1) = 20;
    
    for (int i = 0; i < 3; i++) {
        printf("%d번째 요소 : %d\n", i+1, *(ary+i));
    }
    
    

    return 0;
}

#endif


/************
// [10-2] 배열명처럼 사용되는 포인터
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int ary[3];
    int *pa = ary;
    
    *pa = 10;
    *(pa + 1) = 20;
    
    for (int i = 0; i < 3; i++) {
        printf("%d번째 요소 : %d\n", i + 1, ary[i]);
    }
    
    printf("배열 전체의 길이 : %d\n", sizeof(ary));
    printf("포인터 하나의 길이 : %d\n", sizeof(pa));

    return 0;
}

#endif


/************
// [10-3] 포인터를 이용한 배열의 값 출력
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int ary[3] = {10, 20, 30};
    int *pa = ary;
    
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", *pa++);
    }

    return 0;
}

#endif


/************
// [10-4] 포인터의 뺄셈과 관계 연산
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int ary[5] = {10, 20, 30, 40, 50};
    int *pa = ary;
    int *pb = ary + 3;
    
    if (pa < pb) {
        printf("%d\n", *pa);
    }
    else
    {
        printf("%d\n", *pb);
    }

    return 0;
}

#endif


/************
// [10-확인] 제목
*************/

#if 0

#include <stdio.h>

int main(void)
{

    
    double ary[5] = {1.2, 3.5, 7.4, 0.5, 10.0};
    double *pa = ary;
    double *pb = ary+2;
    
    // ary배열에 첫번째 주소는 100
    // 1. 100
    // 2. 3.5
    // 3. 116
    // 4. 0.5
    // 5. 7.4
    // 6. 2

    return 0;
}

#endif


/************
// [10-5] 배열을 처리하는 함수
*************/

#if 0

#include <stdio.h>

void print_ary(int *pa);

int main(void)
{

    int ary[5] = {10, 20, 30, 40, 50};
    print_ary(ary);

    return 0;
}

void print_ary(int *pa)
{
    for (int i = 0; i < 5; i++) {
        printf("%d ", pa[i]);
    }
}

#endif


/************
// [10-6] 크기가 다른 배열을 출력하는 함수
*************/

#if 0

#include <stdio.h>

void print_ary(int *pa, int n);

int main(void)
{

    int ary1[5] = {10, 20, 30, 40, 50};
    int ary2[7] = {10, 20, 30, 40, 50, 60, 70};
    
    print_ary(ary1, 5);
    print_ary(ary2, 7);

    return 0;
}

void print_ary(int *pa, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", pa[i]);
    }
    printf("\n");
}

#endif


/************
// [10-7] 배열에 값을 입력하는 함수
*************/

#if 0

#include <stdio.h>

void input_ary(int *pa, int size);
void find_max(int *pa, int size);


int main(void)
{

    // 1. 배열에 값을 입렷하는 input_ary()
    int ary[5];
    input_ary(ary, 5);
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
    
    find_max(ary, 5);

    return 0;
}

void input_ary(int *pa, int size)
{
    
    for (int i = 0; i < size; i++) {
        scanf("%d", pa+i);
    }
}

void find_max(int *pa, int size)
{
    
    int max = *pa;
    for (int i = 1; i < size; i++) {
        if (pa[i] > max) {
            max = pa[i];
        }
    }
    printf("최대 : %d\n", max);
}

#endif


/************
// [10-도전] 로또 번호 생성 프로그램
*************/

#if 0

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void lotto_input(int *ps, int size);
void lotto_output(int *ps, int size);
void rand_lotto(int *ps, int size);
void bubble_sort(int *ps, int size);

int main(void)
{

    // 도전문제 : 6개의 정수를 입력 (1~45)
    // 해당 값이 이미 존재하면 다시 입력
    // 랜덤 6개추출
    int s[6];
    
    //lotto_input(s, 6);
    rand_lotto(s, 6);
    bubble_sort(s, 6);
    lotto_output(s, 6);

    return 0;
}

void lotto_input(int *ps, int size)
{

    
    for (int i = 0; i < size; i++) {
        
        printf("로또 번호 입력 : ");
        scanf("%d", &ps[i]);
        
        if (ps[i] <= 0 || ps[i] > 45) {
            i--;
            printf("다시 ");
            continue;;
        }
        
        for (int j = 0; j < i; j++) {
            if (ps[i] == ps[j]) {
                i--;
                printf("다시 ");
                break;
            }
        }
    }
}

void lotto_output(int *ps, int size)
{
    
    printf("로또 번호 : ");
    
    for (int i = 0; i < size; i++) {
        
        printf("%d ", ps[i]);
    }
    printf("\n");
}

void rand_lotto(int *ps, int size)
{
    int r;
    srand(time(NULL));
    
    for (int i = 0; i < size; i++) {
        
        r = rand() % 45 + 1;
        ps[i] = r;
        for (int j = 0; j < i; j++) {
            
            if (ps[i] == ps[j]) {
                
                i--;
                break;
            }
        }
    }
}

void bubble_sort(int *ps, int size)
{
 
    int temp;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            
            if (ps[j] > ps[j+1]) {
                
                temp = ps[j];
                ps[j] = ps[j+1];
                ps[j+1] = temp;
            }
        }
    }
}

#endif


/************
// [10-도전] 정렬 알고리즘
*************/

#if 0

#include <stdio.h>

void swap(int *pa, int *pb);
void bubble_sort(int *pa, int size);
void print_array(int *pa, int size);
void selection_sort(int *pa, int size);
void binary_search(int *pa, int size, int search);
void recursion_binary_search(int *pa, int high, int low, int search);

int main(void)
{

    int array[10] = {1, 32, 19, 27, 23, 15, 20, 96, 25, 37};
    int size = sizeof(array) / sizeof(int);
    
    printf("정렬 전 : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    selection_sort(array, size);
//    bubble_sort(array, size);
    print_array(array, size);
//    binary_search(array, size, 96);
//    recursion_binary_search(array, size, 0, 23);
    
    return 0;
}

void swap(int *pa, int *pb)
{
    
    int temp;
    
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void bubble_sort(int *pa, int size)
{
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (pa[j] > pa[j+1]) {
                swap(pa+j, pa+j+1);
            }
        }
    }
}

void selection_sort(int *pa, int size)
{
    
    int index;
    
    for (int i = 0; i < size - 1; i++) {
        
        index = 0;
        
        for (int j = 0; j < size - i; j++) {
            if (pa[j] > pa[index]) {
                index = j;
            }
        }
        printf("index : %d, pa[index] : %d, pa[size-(i+1)] : %d\n", index, pa[index], pa[size-(i+1)]);
        swap(&pa[index], &pa[size-(i+1)]);
        print_array(pa, size);
        printf("\n");
    }
}

void print_array(int *pa, int size)
{
    printf("정렬 후 : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", pa[i]);
    }
    printf("\n");
}

void binary_search(int *pa, int size, int search)
{
    
    int low = 0, high = size - 1, mid = (high + low)/2;
    
    while (1) {
        
        if (pa[mid] > search) {
            high = mid - 1;
            mid = (high + low) / 2;
        }
        else if (pa[mid] < search)
        {
            low = mid + 1;
            mid = (high + low) / 2;
        }
        else{
            printf("찾는 %d는 index %d번에 있습니다. \n", search, mid);
            break;
        }
    }
    
}

void recursion_binary_search(int *pa, int high, int low, int search)
{
    
    int mid = (high + low) / 2;
    
    if (mid >= 1) {
        
        if (pa[mid] > search)
            recursion_binary_search(pa, mid - 1, low, search);
        
        else if (pa[mid] < search)
            recursion_binary_search(pa, high, low + 1, search);
        
        else printf("%d는 index %d에 있다.\n", search, mid);
    }
    else
        printf("없음 \n");
}

#endif


/************
// [11-1] 대문자를 소문자로 변경하는 함수
*************/

#if 0

#include <stdio.h>

char lowercase(char alphabet);

int main(void)
{

    printf("%c\n", lowercase('H'));

    return 0;
}

char lowercase(char alphabet)
{
    
    return alphabet + 32;
}

#endif


/************
// [11-2] 공백이나 제어 문자의 입력
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char ch1, ch2;
    
    while (1)
    {
        
        scanf("%c", &ch1);
        
        if (ch1 == 10) break;
        
        printf("%c", ch1);
    }
    
//    scanf("%c%c", &ch1, &ch2);
//    printf("[%d, %d]\n", ch1, ch2);
    
    return 0;
}

#endif


/************
// [11-3] getchar, putchar
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int ch;
    
    while (1)
    
    {
        ch = getchar();
        
        if (ch == EOF) break;
        
        putchar(ch);
    }

    return 0;
}

#endif


/************
// [11-3-1] scanf에 공백??
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char c;
    
    for (int i = 0; i < 5; i++) {
        scanf(" %c", &c); // %앞에 공백 삽입 시 -> 화이트 스페이스를 무시한다.
        printf("%c", c);
    }

    return 0;
}

#endif


/************
// [11-4] 버퍼를 사용하는 문자 입력
*************/

#if 0

#include <stdio.h>

int main(void)
{

//    char c;
//    
//    for (int i = 0; i < 3; i++)
//    {
        
//        scanf("%c", &c);
//        printf("%c", c);
//    }
    
    char ch;
    
    while (1)
    {
        
        scanf("%c\n", &ch);
    
        if (ch == EOF) break;
        
        printf("%c", ch);
    }
    
    return 0;
}

#endif


/************
// [11-5] 입력 문자의 아스키 코드 값을 출력하는 프로그램
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int result;
    char c;
    
    while (1)
    {
        
        result = scanf("%c", &c);
        if (result == -1) break;
        printf("%d", c);
    }

    return 0;
}

#endif


/************
// [11-6] getchar 함수를 사용한 문자열 입력
*************/

#if 0

#include <stdio.h>

void my_getchar(char *str, int size);

int main(void)
{

    char str[7];
    
    my_getchar(str, 7);
    printf("입력한 문자열 : %s\n", str);

    return 0;
}

void my_getchar(char *str, int size)
{
    
    for (int i = 0; i < size; i++)
    {
        
        str[i] = getchar();
    }
}

#endif


/************
// [11-7] 버퍼의 내용을 지워야 하는 경우
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int num;
    printf("학번 입력 : ");
    scanf("%d", &num);
    
    int grade;
    printf("학점 입력 : ");
    grade = getchar(); // 버퍼에 엔터(\n)이 남아있음
    
    // 입력 버퍼 사용 시 주의사항
    // 잘 모르겠으면 버퍼를 초기화
    // getchar();을 넣으면 화이트 스페이스를 넣어서 버퍼 초기화 가능
    
    printf("학번 : %d, 학점 : %c\n", num, grade);

    return 0;
}

#endif


/************
// [11-도전] 길이가 가장 긴 단어 찾기
*************/

#if 0

#include <stdio.h>

int main(void)
{
    
    int c, max = 0, len = 0;
    
    while (1)
    {
        
        c = getchar();
        len++;
        
        if (c == EOF)
            break;
        
        else if (c == 10)
            len = 0;
        
        else if (max < len)
            max = len;
        
    }
    printf("%d\n", max);
    
    return 0;
}

#endif


/************
// [12-1] 문자열 상수가 주소인 이유
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int array[5] = {10, 20, 30, 40, 50};
    int *pa = array;
    
    printf("%p %p\n", array, pa);
    
    char fruit[6] = {'a', 'p', 'p', 'l', 'e', '\0'};
    char fruit2[6] = "apple";
    
    char *pf = fruit, *pf2 = fruit2;
    
    printf("%p %p\n", pf, pf2);

    return 0;
}

#endif


/************
// [12-2] 포인터로 문자열 사용
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char drink[80] = "coke";
    char *pd = drink;
    
    while (*pd) // *pd의 값이 \0(널)이 아닐 때 참(1), \0(널)이면 거짓(0)
        printf("%c", *(pd++));
    
    printf("\n");
    
    return 0;
}

#endif


/************
// [12-잠깐] 같은 문자열 상수??
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char fruit[6] = { 'a', 'p', 'p', 'l', 'e', '\0'};
    char *fruit2 = "apple";
    char *fruit3 = "apple";
    
    printf("%p\n", fruit);
    printf("%p\n", fruit2);
    printf("%p\n", fruit3);
    
    printf("\n");

    char *pf = fruit;
    char *pf2 = fruit2;
    char *pf3 = fruit3;
    
    printf("%p\n", pf);
    printf("%p\n", pf2);
    printf("%p\n", pf3);

    return 0;
}

#endif


/************
// [12-3] scanf함수를 사용한 문자열 입력
*************/

#if 0

#include <stdio.h>
// 입력 버퍼관련
int main(void)
{
    
    char str[100];

    printf("문자열 입력 : ");
    scanf("%s", str);
    printf("%s\n", str);
    
    scanf("%s", str);
    printf("두번째 단어 : %s\n", str);

    return 0;
}

#endif


/************
// [12-4] gets 함수로 한 줄의 문자열 입력
*************/

#if 0

#include <stdio.h>
// xcode에서 gets를 지원하지 않음.
int main(void)
{

    char str[100];
    
    printf("문자열 입력 : ");
    gets(str);
    printf("내용 : %s", str);

    return 0;
}

#endif


/************
// [12-5] gets의 안정성 보장을 위한 fgets
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[100];
    
    printf("입력 : ");
    fgets(str, sizeof(str), stdin);
    printf("출력 : %s", str);
    printf("문자열 길이 : %d\n", strlen(str) - 1);
    printf("문자열 길이 2 : %d\n", sizeof(str));

    return 0;
}

#endif


/************
// [12-6] 개행 문자로 인해 get 함수가 입력 안되는 경우
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int age;
    char name[50];
    
    printf("나이 입력 : ");
    scanf("%d", &age);
    
    
    printf("이름 입력 : ");
    fgetc(stdin);
    
    printf("나이 : %d, 이름 : %s\n", age, name);

    return 0;
}

#endif


/************
// [12-7] 문자열을 출력하는 puts와 fputs함수
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char str[100] = "apple juice";
    char *ps = "banana";
    
    puts(str);
    fputs(ps, stdout);
    puts(" milk");

    return 0;
}

#endif


/************
// [12-직접] gets 함수 구현해보기
*************/

#if 0

#include <stdio.h>

void my_gets(char *ps);

int main(void)
{

    char str[50];
    my_gets(str);
    
    printf("%s", str);

    return 0;
}

void my_gets(char *ps)
{
    int i = 0;
    while (1)
    {
        
        scanf("%c", &ps[i]);
        
        if (ps[i] == '\n')
        {
         
            ps[i] = '\0';
            break;
        }
        else i++;
    }
}

#endif


/************
// [12-8] strcpy 함수의 사용법
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[80] = "strawberry";
    
    strcpy(str, "banana");
    
    printf("%s\n", str);
    printf("%c\n", str[8]);

    return 0;
}

#endif


/************
// [12-9] strncpy
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[90] = "strawberry";
    
    strncpy(str, "mango", 5);
    
    printf("%s", str);

    return 0;
}

#endif


/************
// [12-8-직접구현] strcpy
*************/

#if 0

#include <stdio.h>

void my_strcpy(char *pd, char *ps);

int main(void)
{

    char str[50] = "strawberry";
    
    printf("바꾸기 전 : %s\n", str);
    
    my_strcpy(str, "banana");
    
    printf("바꾼 후 : %s\n", str);
    

    return 0;
}

void my_strcpy(char *pd, char *ps)
{
    
    int *po;
    po = pd;
    
    while (*po) *po++ = *ps++;
    
    *po = '\0';
}

#endif


/************
// [12-9] 문자열을 연결하는 strcat()
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[80] = "straw";
    strcat(str, " berry");
    printf("%s\n", str);
    
    char *pi = " ice-cream";
    strcat(str, pi);
    printf("%s\n", str);
    
    char str2[80] = "cake dessert yogurt";
    strncat(str, str2, 4);
    printf("%s\n", str);

    return 0;
}

#endif


/************
// [12-10-직접구현] 나만의 my_strcat() 만들기
*************/

#if 0

#include <stdio.h>

char *my_strcat(char *pd, char *ps);

int main(void)
{
    
    char str[100] = "straw";
    
    printf("strcat 전 : %s\n", str);
    
    str = my_strcat(str, " berry");
    
    printf("strcat 후 : %s\n", str);
    
    printf("\n");

    return 0;
}

char *my_strcat(char *pd, char *ps)
{
    
    char *po = pd;
    
    while (*po) po++;
    while (*ps) *po++ = *ps++;
    
    *po = '\0';
    
    return po;
}

#endif


/************
// [12-11] 문자열 길이 strlen()
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    char str1[80], str2[80];
    
    printf("두 과일 입력(과일1 과일2) : ");
    scanf("%s %s", str1, str2);
    
    if (strlen(str1) > strlen(str2)) {
        printf("첫 번째 과일이 더 김\n");
    }
    else{
        printf("두 번째 과일이 더 김\n");
    }
    
    printf("첫 번째 과일 : %s\n", str1);
    printf("두 번째 과일 : %s\n", str2);

    return 0;
}

#endif


/************
// [12-11-직접] my_strlen()
*************/

#if 0

#include <stdio.h>

int my_strlen(char *pd);

int main(void)
{

    char str1[80], str2[80];
    
    printf("두 과일 입력(과일1 과일2) : ");
    scanf("%s %s", str1, str2);
    
    if (my_strlen(str1) > my_strlen(str2)) {
        printf("첫 번째 과일이 더 김\n");
    }
    else{
        printf("두 번째 과일이 더 김\n");
    }
    
    printf("첫 번째 과일 : %s\n", str1);
    printf("두 번째 과일 : %s\n", str2);

    return 0;
}

int my_strlen(char *pd)
{
 
    int i = 0;
    while (*pd) {
        pd++;
        i++;
    }
    return i - 1;
}



#endif


/************
// [12-12] strcmp 함수를 사용한 문자열 비교
*************/

#if 0

#include <stdio.h>
#include <string.h>

int main(void)
{

    printf("%d", strcmp("aaa", "bbb"));

    return 0;
}

#endif


/************
// [12-12-직접] my_strcmp
*************/

#if 0

#include <stdio.h>

int my_strcmp(char *pd, char *ps);

int main(void)
{

    printf("%d\n", my_strcmp("banana", "kiwi"));
    printf("%d\n", my_strcmp("kiwi", "banana"));
    printf("%d\n", my_strcmp("kkk", "kkk"));
    printf("%d\n", my_strcmp("aaa", "bbb"));

    return 0;
}

int my_strcmp(char *pd, char *ps)
{
    
    char *po = pd;
    
    while (*po++ && *ps++);
    
    
    if (*po > *pd) return 1;
    else if (*po < *pd) return -1;
    else return 0;

}

#endif


/************
// [12-추가] 문자 개수 찾기
*************/

#if 0

#include <stdio.h>

int find_char(char *ps, char c);

int main(void)
{

    printf("%d\n", find_char("Helloasd", 'c'));

    return 0;
}

int find_char(char *ps, char c)
{
    
    int count = 0;
    for (int i = 0; ps[i] != '\0'; i++) {
        if (ps[i] == c) {
            count++;
        }
    }
    return count;
}

#endif


/************
// [12-도전] 단어 정렬 프로그램
*************/

#if 0

#include <stdio.h>
#include <string.h>

void sort_char(char *p1, char *p2, char *p3);

int main(void)
{

    sort_char("c", "a", "b");
    sort_char("kiwi", "zanana", "grape");
   
    return 0;
}

void sort_char(char *p1, char *p2, char *p3)
{
    
    if (strcmp(p1, p2) <= 0 && strcmp(p1, p3) <= 0)
        strcmp(p2, p3) <= 0 ? printf("%s %s %s\n", p1, p2, p3) : printf("%s %s %s\n", p1, p3, p2);
        
    else if (strcmp(p2, p1) <= 0 && strcmp(p2, p3))
        strcmp(p1, p3) <= 0 ? printf("%s %s %s\n", p2, p1, p3) : printf("%s %s %s\n", p2, p3, p1);
    
    else
        strcmp(p1, p2) <= 0 ? printf("%s %s %s\n", p3, p1, p2) : printf("%s %s %s\n", p3, p2, p1);
        
}


#endif


/************
// [13-1] 두 함수에서 같은 이름의 지역 변수를 사용한 경우
*************/

#if 0

#include <stdio.h>

void assign(void);

int main(void)
{

    auto int a = 10; // auto : 지역 변수 선언 시 사용, 생략 시 컴파일러가 자동 추가

    printf("a의 값 : %d\n", a);
    assign();
    
    return 0;
}

void assign(void)
{
    
    int a = 20;
    
    printf("a의 값 : %d\n", a);
}

#endif


/************
// [13-2] 블록 안에서 사용하는 지역 변수
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a = 10;
    printf("a값 : %d\n", a);
    {
        int a = 20;
        printf("a값 : %d\n", a);
        {
            
            int a = 30;
            printf("a값 : %d\n", a);
        }
    }
    
    

    return 0;
}

#endif


/************
// [13-3] 전역변수 사용
*************/

#if 0

#include <stdio.h>

void assign10(void);
void assign20(void);

int a = 1;

int main(void)
{

    printf("함수 호출 전 전역 변수 a의 값 : %d\n", a);
    
    assign10();
    printf("assign10호출 후 a의 값 : %d\n", a);
    
    assign20();
    printf("assign20호출 후 a의 값 : %d\n", a);

    return 0;
}

void assign10(void)
{
    
    a = 10;
}

void assign20(void)
{
    
    a = 20;
}

#endif


/************
// [13-4] 정적 지역 변수
*************/

#if 0

#include <stdio.h>

void print_star(void);

int main(void)
{

    print_star();
    print_star();

    return 0;
}

void print_star(void)
{
    static int a = 1;
    for (int i = 0; i < a; i++) {
        printf("*");
    }
    printf("\n");
    a++;
    
}

#endif


/************
// [13-5] 레지스터 변수
*************/

#if 0

#include <stdio.h>
#include <time.h> // clock()

int main(void)
{

     int i;
    long long num = 2000000000;
    long long sum = 0;
    long start = clock();
    
    for (i = 1; i < num; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    
    printf("%lld의 약수의 합 : %lld\n", num, sum);
    long end = clock();
    printf("끝 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}

#endif


/************
// [13-6] 값을 복사해서 전달
*************/

#if 0

#include <stdio.h>

int add_ten(int n);

int main(void)
{

    int a = 10;
    
    a = add_ten(&a);
    printf("%d\n", a);

    return 0;
}

int add_ten(int n)
{
    
    return n += 10;
}

#endif


/************
// [13-7] 함수를 전달
*************/

#if 0

#include <stdio.h>

void add_ten(int *pn);

int main(void)
{
    
    int a = 10;
    add_ten(&a);
    printf("%d\n", a);

    return 0;
}

void add_ten(int *pn)
{
    
    *pn += 10;
}

#endif


/************
// [13-8] 주소를 반환하는 함수
*************/

#if 0

#include <stdio.h>

int *sum(int a, int b);

int main(void)
{

    int a = 10, b = 20;
    int *ps = sum(a, b);
    
    printf("%d\n", *ps);

    return 0;
}

int *sum(int a, int b)
{
    // 주소값을 반환 사 static 키워드를 사용하자
    static int r;
    r = a + b;
    
    return &r;
}


#endif


/************
// [13-도전] 전역 변수 교환 프로그램
*************/

#if 0

#include <stdio.h>

void swap(void);

int a, b;

int main(void)
{

    a = 10;
    b = 20;
    printf("교환 전 a : %d, b : %d\n", a, b);
    
    swap();
    printf("교환 후 a : %d, b : %d\n", a, b);

    return 0;
}

void swap(void)
{
    
    int temp;
    
    temp = a;
    a = b;
    b = temp;
}

#endif


/************
// [14-0] 2차원 배열 사용 이유
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int score1[4] = { 10, 20, 30, 40 };
    int score2[4] = { 20, 30, 40, 50 };
    int score3[4] = { 30, 40, 50, 60 };
    
    int total_kor = score1[0] + score2[0] + score3[0];
    
    int scores[3][4] = {score1, score2, score3};
    
    
    
    return 0;
}

#endif


/************
// [14-1] 4 과목의 총점과 평균
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int scores[3][4] = {
       {72, 80, 95, 60},
       {68, 98, 83, 90},
       {75, 72, 84, 90}
    };

    int sum;
    double avg;
    
    for (int i = 0; i < 3; i++) {
        sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += scores[i][j];
        }
        avg = sum / 4.0;
        printf("%d번 사람의 총점 : %d, 평균 : %.1lf\n", i+1, sum, avg);
    }

    return 0;
}

#endif


/************
// [14-2] 4 과목의 총점과 평균을 입력
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int scores[3][4];

    for (int i = 0; i < 3; i++)
    {
        printf("%d번째 학생 입력 : \n", i+1);
        for (int j = 0; j < 4; j++)
        {
            scanf("%d", &scores[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        printf("%d번째 학생 입력 점수 : ", i+1);
        for (int j = 0; j < 4; j++)
        {
            printf("%2d ", scores[i][j]);
        }
        printf("\n");
    }

    return 0;
}

#endif


/************
// [14-연습] 2차원 배열 부수기
*************/

#if 0

#include <stdio.h>

void print_2d_array(int *pa);
void print_2d_array1(int *pa);
void input_2d_array(int *pa);
void input_2d_array1(int *pa);
void print_2d_array2(int pa[5][5]);
void print_2d_array3(int pa[5][5]);

int main(void)
{

    int array[5][5];
    int index = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j] = index++;
        }
        
    }

    print_2d_array3(array);

    return 0;
}

void print_2d_array(int *pa)
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%5d", *((pa+i * 5)+j));
        }
        printf("\n");
    }
}
void print_2d_array1(int *pa)
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%5d", *((pa+j)+i));
        }
        printf("\n");
    }
}
void input_2d_array(int *pa)
{

    int index = 1;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            *((pa+i)+j) = index++;
        }
    }
}
void input_2d_array1(int *pa)
{

    int index = 21;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            *((pa+i)+j) = index++;
        }
    }
}
void print_2d_array2(int pa[5][5])
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 4; j >= 0; j--)
        {
            printf("%5d", pa[i][j]);
        }
        printf("\n");
    }
}
void print_2d_array3(int pa[5][5])
{

    for (int i = 0; i < 5; i++)
    {
        //if (i % 2 == 0)
            for (int j = 0; j < 5; j++)
            printf("%3d", pa[i][(1 - i % 2) * j + (i % 2) * (4 - j)]);                 
        // else
        //     for (int j = 4; j >= 0; j--)
        //         printf("%5d", pa[i][j]);
            
        printf("\n");
    }
}
#endif


/************
// [14-3] 여러 마리의 동물을 입출력
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char animal[5][20];
    int row = sizeof(animal) / sizeof(animal[0]);

    for (int i = 0; i < row; i++)
    {
        scanf("%s", animal[i]);
    }
    
    for (int i = 0; i < row; i++)
    {
        printf("%s d", animal[i]);
    }

    return 0;
}

#endif


/************
// [14-4] 포인터 배열로 여러개의 문자열 출력
*************/

#if 0

#include <stdio.h>

int main(void)
{

    char *pa = "dog", *pb = "Cat", *pc = "elephant", *pd = "rabbit", *pe = "hippo";
    char *pary[5] = {pa, pb, pc, pd, pe};

    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", pary[i]);
    }

    return 0;
}

#endif


/************
// [14-5] 포인터 배열을 통해 int 2차원도 1차원처럼 써보자
*************/

#if 0

#include <stdio.h>

int main(void)
{

   int ary1[4] = { 10, 20, 30, 40 };
   int ary2[4] = { 11, 21, 31, 41 };
   int ary3[4] = { 12, 22, 32, 42 };

   int *pary[3] = {ary1, ary2, ary3};


   for (int i = 0; i < 3; i++)
   {
    for (int j = 0; j < 4; j++)
    {
        printf("%3d ", (*(pary+i))[j]);    
    }
    printf("\n");
   }
   

    return 0;
}

#endif


/************
// [14-도전] 가로 세로의 합 구하기
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int ary[5][6] = {0,}, index = 1, sum_x = 0, sum_y = 0, total = 0;
    int j;

    for (int i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            ary[i][j] = index++;
            sum_y += ary[i][j];
            if (j == 4)
            {
                ary[i][j+1] = sum_y;
                total += sum_y;
                sum_y = 0;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        sum_x = 0;
        for (j = 0; j < 4; j++)
        {
            sum_x += ary[j][i];
            total += sum_x;
        }
        ary[4][i] = sum_x;
    }
    
    ary[4][5] = total;

    for (int i = 0; i < 5; i++)
    {
        for (j = 0; j < 6; j++)
        {
            printf("%5d", ary[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}

#endif


/************
// [15-1] 이중 포인터
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a = 10;
    int *pa = &a;
    int **ppa = &pa;

    printf("%d %d %d\n", &a, &pa, ppa);

    return 0;
}

#endif


/************
// [15-2] 이중 포인터를 활용한 문자열 교환
*************/

#if 0

#include <stdio.h>

void swap_poninter(char **pa, char **pb);
void swap_int(int *pa, int *pb);

int main(void)
{

    char *pa = "success";
    char *pb = "failure";

    printf("pa -> %s, pb -> %s\n", pa, pb);
    swap_poninter(&pa, &pb);
    printf("pa -> %s, pb -> %s\n", pa, pb);

    int a = 10, b = 20;
    printf("%d %d\n", a, b);
    swap_int(&a, &b);
    printf("%d %d\n", a, b);

    return 0;
}

void swap_poninter(char **pa, char **pb)
{

    char *pt;

    pt = *pa;
    *pa = *pb;
    *pb = pt;
}

void swap_int(int *pa, int *pb)
{

    int *pt;

    *pt = *pa;
    *pa = *pb;
    *pb = *pt;
}

#endif


/************
// [15-3] 포인터 배열
*************/

#if 0

#include <stdio.h>

void print_str(char **ppa, int size);

int main(void)
{

    char *animal = "dog";

    char *animals[4] = {"dog", "cat", "rabbit", "hippo"};

    print_str(animals, 4);
    
    printf("*주소 : %d %d", animal, animals[0]);

    return 0;
}

void print_str(char **ppa, int size)
{

    // printf("%c\n", *(*ppa + 0)); // d
    // printf("%c\n", *(*ppa + 1)); // o

    // printf("%c\n", **(ppa + 1)); // c
    // printf("%c\n", *(*(ppa + 1) + 1)); // a
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", ppa[i]);
    }
    
    printf("%c\n", ppa[1][2]); // t
}

#endif


/************
// [15-4] 배열의 주소
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int array[5];

    printf("%d\n", array); // array의 주소(0번 인덱스 주소)
    printf("%d\n", &array); // array의 주소 값
    printf("%d\n", array + 1); // 1번 인덱스의 주소
    printf("%d\n", &array + 1); // (array의 주소) + 1

    return 0;
}

#endif


/************
// [15-5] 배열 포인터로 5x5 출력
*************/

#if 0

#include <stdio.h>

void print_array(int **ppa);

int main(void)
{

    int array[5][5];
    int count = 1;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            array[i][j] = count++;

    print_array(array);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%5d", *(*(array+i)+j));
        }
        printf("\n");
    }
    
    

    return 0;
}

void print_array(int **ppa)
{

    int (*array)[5] = ppa;

    printf("print_Array :\n");

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%5d", array[i][j]);
        }
        printf("\n");
        
    }
    
}

#endif


/************
// [15-7] 함수 포인터를 사용한 함수 호출
*************/

#if 0

#include <stdio.h>

int sum(int a, int b);

int main(void)
{

    int result;
    result = sum(10, 20);

    printf("%d\n", result);

    int (*fp)(int, int); // 함수 포인터
    fp = sum;
    int result2 = fp(20, 30);

    printf("%d\n", result2);

    int result3 = (*sum)(30, 40);
    printf("%d\n", result3);
    

    return 0;
}

int sum(int a, int b){ return a + b; }

#endif


/************
// [15-8] 깔끔한 계산 프로그램 만들기
*************/

#if 0

#include <stdio.h>

void func(int (*fp)(int, int));
int sum(int a, int b);
int max(int a, int b);
int mul(int a, int b);
int abs(int a, int b);

int main(void)
{

    printf("1 두 정수의 합\n");
    printf("2 두 정수의 곱\n");
    printf("3 두 정수 중에서 큰 값 계산\n");
    printf("4 두 정수의 차\n");

    printf("원하는 연산을 선택하세여 : ");
    int menu;
    scanf("%d", &menu);

    int result;

    switch (menu)
    {

    case 1: func(sum); break;
    case 2: func(mul); break;
    case 3: func(max); break;
    case 4: func(abs); break;
    default: return -1;
    }

    return 0;
}

void func(int (*fp)(int, int))
{

    int a, b, result;
    printf("두 정수의 값을 입력하세요 : ");
    scanf("%d %d", &a, &b);
    
    result = (*fp)(a, b);

    printf("결괏값은 : %d\n", result);
}
int sum(int a, int b){return a + b;}
int mul(int a, int b){return a * b;}
int max(int a, int b){return a > b ? a : b;}
int abs(int a, int b){return a - b < 0 ? b - a : a - b;}

#endif


/************
// [15-9] void 포인터
*************/

#if 0

#include <stdio.h>

int main(void)
{

    int a = 10;
    double b = 3.14;

    void *vp;
    vp = &b;
    printf("%lf\n", *((double *)vp));

    return 0;
}

#endif


/************
// [16-1] 동적 할당한 저장 공간을 사용하는 프로그램
*************/

#if 0

#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int N, count = 1;
    printf("배열의 크기를 입력하세여 : ");
    scanf("%d", &N);

    int *pi = (int *)malloc(sizeof(int) * N);

    if (pi == NULL)
    {
        printf("메모리 부족\n");
        exit(1);
    }
    

    for (int i = 0; i < N; i++) pi[i] = count++;

    for (int i = 0; i < N; i++) printf("%d ", pi[i]);

    free(pi);

    return 0;
}

#endif


/************
// [16-2] 연속 할당과 재할당
*************/

#if 0

#include <stdio.h>
#include<stdlib.h>

int main(void)
{

    printf("배열 크기 입력 : ");
    int N;
    scanf("%d", &N);
    // calloc -> 초기화 : 0
    int *parray = (int *)calloc(N, sizeof(int));

    if (parray == NULL)
    {
        printf("memory...\n");
        exit(1);
    }

    int count = 1;

    for (int i = 0; i < N; i++) parray[i] = count++;
    for (int i = 0; i < N; i++) printf("%1d", parray[i]);  
    printf("\n");

    int M;
    printf("재조정할 배열의 크기 : ");
    scanf("%d", &M);

    int *pparray = (int *)realloc(parray, sizeof(int) * M);

    

    for (int i = N; i < M; i++) parray[i] = count++;
    for (int i = 0; i < M; i++) printf("%1d", pparray[i]);  
    for (int i = 0; i < N; i++) printf("%1d", parray[i]);  

    free(parray);

    return 0;
}

#endif


/************
// [16-4] 3개의 문자열을 저장하기 위한 동적 할당
*************/

#if 0

#include <stdio.h>
#include <string.h>
#include<stdlib.h>

int main(void)
{

    char *str[3];
    char temp[80] = {0,};
    for (int i = 0; i < 3; i++)
    {
        gets(temp);
        str[i] = (char *)malloc(strlen(temp) + 1);
        if (str[i] == NULL)
        {
            exit(1);
        }
        
        strcpy(str[i], temp);
    }
    
    for (int i = 0; i < 3; i++)
    {
        printf("%s\n", str[i]);
    }
    
    for (int i = 0; i < 3; i++)
    {
        free(str[i]);
    }
    


    return 0;
}

#endif


/************
// [16-5] 몇 개???를 받아 문자열 출력
*************/

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(char **ppa);

int main(void)
{

    char *str[21] = {0, };
    char temp[46];

    for (int i = 0; i < 20; i++)
    {

        printf("문자열을 입력하세요 : ");
        scanf("%s", temp);

        if (strcmp(temp, "end") == 0) break;

        str[i] = (char *)malloc(strlen(temp) + 1);
        strcpy(str[i], temp);

        if (str[i] == NULL) 
            exit(1);
        
    }

    print_array(str);
    
    for (int i = 0; *str[i] != '\0'; i++)
    {
        free(str[i]);
    }
    
    

    return 0;
}

void print_array(char **ps)
{

    while (*ps) printf("%s\n", *ps++);
}

#endif


/************
// [16-6] 명령 프롬프트 인자를 출력하는 프로그램
*************/

#if 0

#include <stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{

    int size = atoi(argv[1]);

    printf("Hello World\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
        
    }
    
    // for (int i = 0; i < argc; i++)
    // {
    //     printf("%s\n", argv[i]);
    // }
    

    return 0;
}

#endif


/************
// [17-1] 구조체 선언 및 사용
*************/

#if 0

#include <stdio.h>

struct contact
{
    // 멤버 변수
    char *name;
    int age;
    char *mbti;
};

struct student
{
    char ch1;
    short num;
    char ch2;
    int score;
    char ch3;
    double grade;
};

struct exam
{
   char c1;
   int num;
};


int main(void)
{

    struct contact p1;
    struct contact p2;

    struct student s1;

    struct exam e1;

    printf("e1의 크기 : %d\n", sizeof(e1));
    

    printf("s1의 크기 : %d\n", sizeof(s1));
    

    p1.name = "김민수";
    p1.age = 27;
    p1.mbti = "ESFJ";

    p2.name = "김민우";
    p2.age = 28;
    p2.mbti = "I~~~";

    printf("이름 : %s, 나이 : %d세, MBTI : %s\n", p1.name, p1.age, p1.mbti);
    printf("이름 : %s, 나이 : %d세, MBTI : %s\n", p2.name, p2.age, p2.mbti);

    return 0;
}

#endif


/************
// [17-2] 멤버의 자료형
*************/

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int id;
    double grade;
};


struct profile
{

    char name[20];
    int age;
    double height;
    char *info;

    struct student st;
 
};


int main(void)
{

    struct profile p1 = {"김민수", 20, 168.8};
    
    printf("자기소개 : ");
    char temp[100];
    scanf("%[^\n]s", temp);
    p1.info = (char *)malloc(strlen(temp) + 1);
    strcpy(p1.info, temp);

    p1.st.id = 201831006;
    p1.st.grade = 3.39;

    printf("이름 : %s, 나이 : %d, 키 : %lf\n소개 : %s\n", p1.name, p1.age, p1.height, p1.info);
    printf("학번 : %d, 학점 : %lf\n", p1.st.id, p1.st.grade);

    return 0;
}

#endif


/************
// [17-3] 최고 학점의 학생 데이터 출력
*************/

#if 0

#include <stdio.h>

struct student
{
    int id;
    char name[20];
    double grade;

};


int main(void)
{

    struct student s1 = {315, "홍길동", 2.9},
                    s2 = {316, "임꺽정", 3.7},
                    s3 = {317, "tlacjddl", 4.5};


    // s1.grade > s2.grade ? s1.grade > s3.grade ? printf("학번 : %d, 이름 : %s, 학점 : %.1lf", s1.id, s1.name, s1.grade) : printf("학번 : %d, 이름 : %s, 학점 : %.1lf", s3.id, s3.name, s3.grade) : 
    // s2.grade > s3.grade ?
    // printf("학번 : %d, 이름 : %s, 학점 : %.1lf", s2.id, s2.name, s2.grade) : printf("학번 : %d, 이름 : %s, 학점 : %.1lf", s3.id, s3.name, s3.grade);
    
    
    struct student max = s1;

    if (s2.grade > max.grade) max = s2;
    if (s3.grade > max.grade) max = s3;

    printf("학번 : %d, 이름 : %s, 학점 : %.1lf\n", max.id, max.name, max.grade);
    
    
    

    return 0;
}

#endif


/************
// [17-6] 구조체 포인터와 간접 멤버 접근 연산자
*************/

#if 0

#include <stdio.h>

struct score
{
    
    int kor;
    int eng;
    int math;
};

int main(void)
{

    struct score s1 = {70, 80, 90};
    struct score *ps;

    ps = &s1;

    printf("%d %d %d\n", s1.kor, (*ps).eng, ps->math);
    

    return 0;
}

#endif


/************
// [17-7] 구조체 배열
*************/

#if 0

#include <stdio.h>

struct student
{
   int id;         // 학번
   char name[20]; // 이름
   double grade;  // 학점
};

void print_struct(struct student *s);

int main(void)
{

    struct student students[3] = {
        {315, "홍길동", 2.4},
        {316, "임꺽정", 3.7},
        {317, "심청이", 4.5}
    };

    
    print_struct(students);
    

    return 0;
}

void print_struct(struct student *s)
{

    for (int i = 0; i < 3; i++)
        printf("id : %d, name : %s, grade : %.1lf \n", s[i].id, (*(s + i)).name, s[i].grade);
}

#endif


/***********************************************************/
// [17-8] 구조체 선언
/***********************************************************/
#if 0
#include <stdio.h>
struct student
{
	int num;
	double grade;
} s1;

int main(void)
{
	s1.num = 315;
	s1.grade = 3.4;

	return 0;
}
#endif
/***********************************************************/
// [17-9] 자기 참조 구조체
/***********************************************************/

#if 0
#include <stdio.h>
struct list
{
	int num;
	struct list *next;
};
int main(void)
{
	// list : Linked List (연결 리스트)
	struct list a = { 10, }, b = { 20, }, c = { 30, };
	// 처음 값인 a를 가리키기 위한 주소
	// head의 값은 절대 변경하지 않는다
	const struct list *head = &a;
	a.next = &b;
	b.next = &c;

	printf("a : %d, a가 가리키는 주소 : %d\n", a.num, a.next);
	printf("b : %d, b가 가리키는 주소 : %d\n", a.next->num, a.next->next);
	printf("c : %d, c가 가리키는 주소 : %d\n", a.next->next->num, a.next->next->next);

	printf("list all : ");
	struct list *current = head;

	while (current != NULL)
	{
		printf("%d ", current->num);
		current = current->next;
	}
	return 0;
}
#endif


/***********************************************************/
// [17-10] 공용체 union
/***********************************************************/
#if 0
#include <stdio.h>
union data
{
	int i;
	double d;
} weather_data;
int main(void)
{
	// 패킷을 통해 타 디바이스에서 
	// data를 전송하고자 한다
	// 2개 data가 오는데
	// 1. 정수형 습도 84%
	// 2. 실수형 기온 17.1도

	// 84,17.1,85,17.2,86,17.3
	//char *str = "84";
	//int count = 1;
	//if (count % 2 == 1)
	//{
	//	weather_data.i = 84;
	//	count++;

	//}
	//else
	//{
	//	weather_data.d = 17.1;
	//	count++;
	//}
	weather_data.i = 84;
	printf("%d\n", weather_data.i);

	weather_data.d = 17.1;
	printf("%.1lf\n", weather_data.d);
	printf("%d\n", weather_data.i);

	return 0;
}
#endif
/***********************************************************/
// [17-11] 열거형
/***********************************************************/

#if 0
#include <stdio.h>
enum discount {NORMAL, EARLY = 4000, TELECOM = 2000};

int main(void)
{
	// 영화 예매 프로그램
	int menu;
	printf("[1]없음 [2]조조 [3]통신사 할인\n");
	printf("할인 권종을 선택하세요 : ");
	scanf("%d", &menu);
	int ticket_price = 14000;

	switch (menu)
	{
	case 1: ticket_price -= NORMAL; break;
	case 2: ticket_price -= EARLY; break;
	case 3: ticket_price -= TELECOM; break;
	default: break;
	}
	printf("결제 금액 : %d원", ticket_price);

	return 0;
}
#endif


/***********************************************************/
// [17-12] typedef을 사용한 자료형 재정의
/***********************************************************/
#if 0
#include <stdio.h>
#include <time.h>

typedef signed int 정수;
struct student
{
	int num;
	double grade;
};
typedef struct student Student;

typedef struct
{
	char name[20];
	int age;
} Profile;

int main(void)
{
	//#include <time.h>
	clock_t t = clock();

	// 구조체를 재정의하면
	// 대문자로 시작하자!!
	Student s1 = { 315, 3.7 };

	int a = 10;
	정수 b = 20;
	printf("%d, %d\n", a, b);

	return 0;
}
#endif


/***********************************************************/
// [18-1] 파일 열고 닫기
/***********************************************************/
#if 0
#include <stdio.h>
#define PATH "C:\Users\Intel Master\Desktop\workspace_c"
int main(void)
{
	FILE *fp;
	const char *path = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\a.txt";
	// 상대 경로로 경로 정할 때,
	// 우리가 지금 바라봤을 때 -> Ctrl + F5
	// 컴파일 배포 -> exe -> 
	const char *path2 = "..\\a.txt";

	fp = fopen(path, "r");
	if (fp == NULL)return 1;
	printf("파일이 열렸습니다.\n");

	// file get char
	int ch;
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF) break;
		putchar(ch);
	}
	fclose(fp); // 열었으면 닫자!! 열었으면 닫자!!
	return 0;
}
#endif


/***********************************************************/
// [18-3] 파일에 문자열 쓰기!!
/***********************************************************/
#if 0
#include <stdio.h>
int main(void)
{
	FILE* fp;
	// 끝에 a.txt -> b.txt로 바꿔주세요!!
	const char* path = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\b.txt";
	fp = fopen(path, "w");
	if (fp == NULL) return 1;

	char* words = "C CLEAR!!";
	while (*words != NULL) fputc(*words++, fp);
	fputc('\n', fp);

	fclose(fp); // 열었으면 닫자, 열었으면 닫자
	return 0;
}
#endif
/***********************************************************/
// [18-3-연습] 파일 입출력!!
/***********************************************************/
#if 0
#include <stdio.h>
#include <string.h>
int main(void)
{
	FILE *fpa, *fpb, *fpc;
	const char *origin_path = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\";
	char path_a[256] = { 0, };
	char path_b[256] = { 0, };
	char path_c[256] = { 0, };
	strcpy(path_a, origin_path);
	strcpy(path_b, origin_path);
	strcpy(path_c, origin_path);
	strcat(path_a, "a.txt");
	strcat(path_b, "b.txt");
	strcat(path_c, "c.txt");

	fpa = fopen(path_a, "r");
	if (fpa == NULL) return 1;

	fpb = fopen(path_b, "r");
	if (fpb == NULL) return 2;

	fpc = fopen(path_c, "w");
	if (fpc == NULL) return 3;

	char temp[256] = { 0, };
	// 1. a.txt 읽어서 temp에 담기!! // Hello World!!
	// 2. b.txt 읽어서 temp에 추가!! // Hello World!! C CLEAR!!
	// 3. temp를 c.txt에 그대로 쓰기
	char* pt = temp;
	int ch;
	while (1)
	{
		ch = fgetc(fpa);
		*pt++ = ch;
		if (ch == EOF) break;
	}
	pt--;

	while (1)
	{
		ch = fgetc(fpb);
		*pt++ = ch;
		if (ch == EOF) break;
	}
	pt--;
	*pt = '\0';

	pt = temp; // 쓰기 위해 포인터 맨 왼쪽으로 이동!!
	while (1)
	{
		fputc(*pt, fpc);
		pt++;
		if (*pt == NULL) break;
	}
	fputc('\n', fpc);

	printf("%s\n", temp);

	fclose(fpa);
	fclose(fpb);
	fclose(fpc);

	return 0;
}
#endif
/***********************************************************/
// [18-4,5] 표준 입출력, stdin, stdout
/***********************************************************/
#if 0
#include <stdio.h>
int main(void)
{
	int ch;
	while (1)
	{
		ch = getchar();
		if (ch == EOF) break;
		putchar(ch);
	}

	while (1)
	{
		ch = fgetc(stdin); // 현재OS와 연결된 키보드!!
		if (ch == EOF) break;
		fputc(ch, stdout);
	}

	return 0;
}
#endif
/***********************************************************/
// [18-6] 파일 형태와 개방 모드가 다른 경우
/***********************************************************/
#if 0
#include <stdio.h>
int main(void)
{
	FILE* fp;
	char* path = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\d.txt";

	fp = fopen(path, "wb");
	if (fp == NULL) return 1;

	int array[10] = { 13, 10, 13, 13, 10, 26, 13, 10, 13, 10 };
	for (int i = 0; i < 10; i++)
	{
		fputc(array[i], fp);
	}
	fclose(fp);

	// txt 형식으로 읽어보자
	fp = fopen(path, "rt");
	int ch;
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF) break;
		printf("%3d", ch);
	}
	fclose(fp);
	return 0;
}
#endif
/***********************************************************/
// [18-7] a+ 모드로 파일 내용 확인하며 출력
/***********************************************************/
#if 0
#include <stdio.h>
#include <string.h> // strcmp()
int main(void)
{
	FILE* fp;
	// 경로 끝에 music.txt
	char* path = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\music.txt";
	// 추가될 데이터(문자열) 임시 저장되는 공간
	char str[20];

	fp = fopen(path, "a+");
	if (fp == NULL) return 1;

	// logic

	while (1) {
		printf("노래 제목 : "); // amond
		scanf("%s", str);
		if (strcmp(str, "end") == 0) break; // end <- 프로그램 종료
		else if (strcmp(str, "list") == 0) // list <- 현재까지 저장된 모든 노래 출력!!
		{
			// 모든 정보 출력하기 전
			// fp를 맨 첫 줄 
			// 맨 앞으로 이동시키자
			fseek(fp, 0, SEEK_SET);
			while (1)
			{
				// 개행(\n)가져오기 위해 +1
				fgets(str, strlen(str) + 1, fp);
				// 행 끝에 도달하면
				// feof() -> 
				if (feof(fp) != 0) break;
				printf("%s", str);
			}
		}
		// while(1) fputc(), -> 문장 전체를 입력, fputs() fprintf
		else fprintf(fp, "%s\n", str);
		// str에 들어 있는 노래 정보를
		// 맨 끝에 d.txt에 쓰자!! 
	}

	fclose(fp); // 열었으면 닫자, 열었으면 닫자!!
	return 0;
}
#endif
/***********************************************************/
// [18-8] 여러 줄의 문장을 입력해 한 줄로 내보내기
/***********************************************************/
#if 0
#include <stdio.h>
#include <string.h> // strlen
int main(void)
{
	// a : Hello World!!
	// b : C CLEAR!!
	// 2개를 e에 내보내기
	char *path_a = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\a.txt";
	char *path_b = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\b.txt";
	char *path_e = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\e.txt";

	FILE *fpa, *fpb, *fpe;
	fpa = fopen(path_a, "r");
	if (fpa == NULL) return 1;

	fpb = fopen(path_b, "r");
	if (fpb == NULL) return 2;

	fpe = fopen(path_e, "w");
	if (fpe == NULL) return 3;

	char str[80];
	char *result;

	while (1)
	{
		result = fgets(str, strlen(str) + 1, fpa);
		if (result == NULL)
		{
		
			/*while (1)
			{
				result = fgets(str, strlen(str) + 1, fpb);
				if (result == NULL) break;
			}*/
			break;
		}
		fputs(result, fpe);
	}
	fclose(fpa);
	fclose(fpb);
	fclose(fpe);

	return 0;
}
#endif
/***********************************************************/
// [18-9] fprintf() 다양한 형식으로 내보내기
/***********************************************************/
#if 0
#include <stdio.h>
int main(void)
{
	// girlfriend.txt
	//소원 95 99 96
	//유주 80 85 94
	//신비 92 76 93

	FILE *fp;
	char *path = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\girlfriend.txt";
	fp = fopen(path, "r");
	if (fp == NULL) return 1;

	FILE *fs;
	char *path_score = "C:\\Users\\Intel Master\\Desktop\\workspace_c\\score.txt";
	fs = fopen(path_score, "w");
	if (fs == NULL) return 2;

	// 이름 국 영 수
	char name[20];
	int kor, eng, math;
	int total;
	double avg;

	int result;
	while (1)
	{
		result = fscanf(fp, "%s %d %d %d", name, &kor, &eng, &math);
		if (result == EOF) break;
		total = kor + eng + math;
		avg = total / 3.0;

		fprintf(fs, "%3s %4d %.1lf\n", name, total, avg);
	}

	fclose(fp);
	fclose(fs);

	return 0;
}
#endif
