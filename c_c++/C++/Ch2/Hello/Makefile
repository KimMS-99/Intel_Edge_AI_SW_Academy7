# 컴파일러
CXX = g++
CXXFLAGS = -g -Wall -std=c++17

# 소스 파일들 (자동으로 *.cpp 모두 포함)
SRCS = $(wildcard *.cpp)
# 오브젝트 파일들
OBJS = $(SRCS:.cpp=.o)

# 실행파일 이름
TARGET = hello

# 기본 빌드 타겟
all: $(TARGET)

# 실행파일 빌드 규칙
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✅ 빌드 성공: $(TARGET) 실행파일이 생성되었습니다."

# 오브젝트 파일 빌드 규칙
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 클린(빌드 결과 삭제)
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "🧹 clean 완료: $(TARGET) 빌드 파일이 모두 삭제되었습니다."

# 실행 (빌드 후 실행)
run: $(TARGET)
	./$(TARGET)
