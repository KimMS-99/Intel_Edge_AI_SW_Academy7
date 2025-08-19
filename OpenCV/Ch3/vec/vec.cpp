#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	// 기본 선언 및 간렬 방식
	Vec<int, 2> v1(5, 12);
	Vec<double, 3> v2(40, 130.7, 125.6);
	Vec2b v3(10, 10);
	Vec6f v4(40.f, 230.25f, 525.6f);
	Vec3i v5(200, 230, 250);

	// 객체 연산 및 형변환
	Vec3d v6 = v2 + (Vec3d)v5; // Vec3d 형으로 변환
	Vec2b v7 = (Vec2b)v1 + v3;
	Vec6f v8 = v4 * 20.0f; // 벡터 원소에 스칼라값 곱함.

	Point pt1 = v1 + (Vec2i)v7; // 2원소 벡터를 Point2_ 객체에 저장
	// Point3_<int> pt2 = v2; // 3원소 벡터를 Point3_ 객체에 저장
	Point3_<int> pt2((int)v2[0], (int)v2[1], (int)v2[2]); // portable across platforms

	Vec<int, 15> v15(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14);

	// 콘솔창 출력
	cout << "[v3] =  " << v3 << endl;
	cout << "[v7] =  " << v7 << endl;
	cout << "[v3 * v7] =  " << v3.mul(v7) << endl; // 행렬곱 수행
	cout << "v8[0] =  " << v8[0] << endl;
	cout << "v8[1] =  " << v8[1] << endl;
	cout << "v8[2] =  " << v8[2] << endl;
	cout << "[v2] =  " << v2 << endl; // 정수형 Point3 객체로 출력
	cout << "[pt2] =  " << pt2 << endl;
	cout << "[v15] = " << v15 << endl;
	return 0;
}