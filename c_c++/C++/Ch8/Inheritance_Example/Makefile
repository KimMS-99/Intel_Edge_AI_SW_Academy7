# 컴파일러
CXX = g++
CXXFLAGS = -g -Wall -std=c++17

# 기본 상속 예제
BASIC_SRCS = Vehicle.cpp Car.cpp main.cpp
BASIC_OBJS = $(BASIC_SRCS:.cpp=.o)
BASIC_TARGET = inheritance_example_basic

# 고급 상속 예제 (다중 상속, 가상 상속)
ADVANCED_SRCS = Advanced_Inheritance.cpp main_advanced.cpp
ADVANCED_OBJS = $(ADVANCED_SRCS:.cpp=.o)
ADVANCED_TARGET = inheritance_example_advanced

# 모든 빌드 타겟
all: $(BASIC_TARGET) $(ADVANCED_TARGET)

# 기본 상속 예제 빌드 규칙
$(BASIC_TARGET): $(BASIC_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✅ 빌드 성공: $(BASIC_TARGET) 실행파일이 생성되었습니다."

# 고급 상속 예제 빌드 규칙
$(ADVANCED_TARGET): $(ADVANCED_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✅ 빌드 성공: $(ADVANCED_TARGET) 실행파일이 생성되었습니다."

# 오브젝트 파일 빌드 규칙
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 클린(빌드 결과 삭제)
clean:
	rm -f *.o $(BASIC_TARGET) $(ADVANCED_TARGET)
	@echo "🧹 clean 완료: 모든 빌드 파일이 삭제되었습니다."

# 실행 (기본 상속 예제)
run_basic: $(BASIC_TARGET)
	./$(BASIC_TARGET)

# 실행 (고급 상속 예제)
run_advanced: $(ADVANCED_TARGET)
	./$(ADVANCED_TARGET)