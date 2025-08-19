CC:=g++

# 현재 디렉토리에서 확장자가 cpp인 파일 하나를 찾아서 변수 SRC에 저장
SRC := $(wildcard *.cpp)
# SRC 파일에서 확장자를 뺀 이름으로 TARGET 설정
TARGET := $(basename $(notdir $(SRC)))
# SRC에서 오브젝트 파일명 생성 (예: main.cpp -> main.o)
OBJECT := $(SRC:.cpp=.o)
# OpenCV 헤더 포함을 위한 컴파일 옵션
CPPFLAGS = $(shell pkg-config --cflags opencv4)
# OpenCV 라이브러리 링크 옵션
LDFLAGS =  $(shell pkg-config --libs opencv4)

# 오브젝트 파일을 링크해 실행 파일 생성
$(TARGET):$(OBJECT)
	$(CC) -o $@ $(OBJECT) $(LDFLAGS)
# C++ 소스를 오브젝트로 컴파일
%.o:%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
