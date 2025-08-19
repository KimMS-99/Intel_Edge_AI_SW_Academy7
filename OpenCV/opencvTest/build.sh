g++ -o $1 $1.cpp $(pkg-config opencv4 --libs --cflags)

# g++ : GNU C++ 컴파일러
# -o $1 : 출력 파일 이름을 $1로 지정 (예: ./build.sh test → test라는 실행 파일 생성)
# $1.cpp : 입력 소스 파일 (예: test.cpp)
# $(pkg-config opencv4 --libs --cflags) : OpenCV4의 컴파일 및 링크에 필요한 플래그들을 자동으로 추가
