#include <iostream>
#include <string>
#include <map>
using namespace std;

// 예제 10-12 map으로 영한 사전 만들기
int main()
{
	map<string, string> dic; // 맵 컨테이너 생성. 키는 영어 단어, 값은 한글 단어

	pair<int, int> p;
	// pair<int, int> p = {3, 4};
	p.first = 1;
	p.second = 2;

	cout << "first : " << p.first << ", second : " << p.second << endl;

	// 단어 3개를 map에 저장
	dic.insert(make_pair("love", "사랑"));	// ("love", "사랑") 저장
	dic.insert(make_pair("apple", "사과")); // ("apple", "사과") 저장
	dic["cherry"] = "체리";					// ("cherry", "체리") 저장

	cout << "저장된 단어 개수 " << dic.size() << endl;
	string eng;
	while (true)
	{
		cout << "찾고 싶은 단어(종료 : exit)>> ";
		getline(cin, eng); // 사용자로부터 키 입력
		if (eng == "exit")
			break; // "exit"이 입력되면 종료

		if (dic.find(eng) == dic.end()) // eng '키'를 끝까지 찾았는데 없음
			cout << "없음" << endl;
		else
			cout << dic[eng] << endl; // dic에서 eng의 값을 찾아 출력
	}
	cout << "종료합니다..." << endl;
}