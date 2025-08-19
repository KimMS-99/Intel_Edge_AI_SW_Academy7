#include <opencv2/opencv.hpp>
#include <time.h>
using namespace cv;
using namespace std;
int main()
{
	vector<double> v1, v2;
	v1.reserve(10000); // 벡터 메모리 할당

	cout << " v1.capacity() : " << v1.capacity() << endl;
	cout << " v2.capacity() : " << v2.capacity() << endl;

	double start_time = clock();
	for (int i = 0; i < v1.capacity(); i++)
	{
		v1.push_back(i); // v1 벡터 원소 삽입
	}
	printf("reserve() 사용 %5.2f ms\n", (clock() - start_time));

	start_time = clock(); // 벡터 원소 삽입 시간 체크
	for (int i = 0; i < v1.capacity(); i++)
	{
		v2.push_back(i); // v2 벡터 원소 삽입
	}
	printf("reserve() 미사용 %5.2f ms\n", (clock() - start_time));
	return 0;
}