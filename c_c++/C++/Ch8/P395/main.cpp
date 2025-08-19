#include <iostream>
#include <string>
using namespace std;

class TV
{
	int size; // 스크린 크기
public:
	TV()
	{
		size = 20;
		cout << "TV()" << endl;
	}
	TV(int size)
	{
		this->size = size;
		cout << "TV(int size)" << endl;
	}
	~TV() { cout << "TV" << endl; }
	int getSize() { return size; }
};

class WideTV : public TV
{ // TV를 상속받는 WideTV
	bool videoIn;

public:
	WideTV(int size, bool videoIn) : TV(size)
	{
		this->videoIn = videoIn;
		cout << "WideTV(int size, bool videoIn) : TV(size)" << endl;
	}
	~WideTV() { cout << "WideTV(int size, bool videoIn) : TV(size)" << endl; }
	bool getVideoIn() { return videoIn; }
};

class SmartTV : public WideTV
{				   // WideTV를 상속받는 SmartTV
	string ipAddr; // 인터넷 주소
public:
	SmartTV(string ipAddr, int size) : WideTV(size, true)
	{
		this->ipAddr = ipAddr;
		cout << "SmartTV(string ipAddr, int size) : WideTV(size, true)" << endl;
	}
	~SmartTV() { cout << "SmartTV(string ipAddr, int size) : WideTV(size, true)" << endl; }
	string getIpAddr() { return ipAddr; }
};

// 예제 8-3 TV, WideTV, SmartTV의 상속 관계와 생성자 매개 변수 전달
int main()
{
	// 32 인치 크기에 "192.0.0.1"의 인터넷 주소를 가지는 스마트 TV 객체 생성
	SmartTV htv("192.0.0.1", 32);
	cout << "size=" << htv.getSize() << endl;
	cout << "videoIn=" << boolalpha << htv.getVideoIn() << endl; // boolalpha : 조작자로 true를 "true" 문자열로 false를 "false"문자열로 출력
	cout << "IP=" << htv.getIpAddr() << endl;
}
