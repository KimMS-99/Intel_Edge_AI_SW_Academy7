#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Matx<ushort, 5, 4> pts;	   // 5행, 4열 ushort 행렬 선언, 2쌍의 좌표 5개 생성 위해
	Mat_<int> sizes, sort_idx; // 사각형 크기 벡터와 정렬 인덱스 벡터
	vector<Rect> rects;
	randn(pts, Scalar(200), Scalar(100)); // 랜덤값 생성 - 임의 사각형 생성 위해
	cout << "\npts" << pts << endl;

	cout << "\n-------------------------------------" << endl;
	cout << "	랜덤 사격형 정보	" << endl;
	cout << "-------------------------------------" << endl;

	for (int i = 0; i < pts.rows; i++)
	{
		Point pt1(pts(i, 0), pts(i, 1));  // 사각형 시작 좌표
		Point pt2(pts(i, 2), pts(i, 3));  // 사각형 종료 좌표
		rects.push_back(Rect(pt1, pt2));  // 2개 좌표로 사각형 지정
		sizes.push_back(rects[i].area()); // 사각형 크기 저장
		cout << format("rects[%d] = ", i) << rects[i] << endl;
	}

	// 정렬 후, 정렬 원소의 원본 인덱스 반환
	sortIdx(sizes, sort_idx, SORT_EVERY_COLUMN); // 열단위 오름차순 정렬 후 원본 좌표 반환

	cout << "\n-------------------------------------" << endl;
	cout << " 크기 순 정렬 사각형 정보 \t크기" << endl;
	cout << "-------------------------------------" << endl;
	for (int i = 0; i < rects.size(); i++)
	{
		int idx = sort_idx(i);
		cout << rects[idx] << "\t" << sizes(idx) << endl;
	}
	cout << "-------------------------------------" << endl;

	return 0;
}