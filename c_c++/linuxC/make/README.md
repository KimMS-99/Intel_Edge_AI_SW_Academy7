# `Makefile` 분석

`Makefile`은 `make` 유틸리티가 소스 코드를 컴파일하고 링크하는 방법을 정의하는 파일입니다. 이 `Makefile`은 다음과 같은 규칙을 포함합니다.

```makefile
CC=gcc

OBJECT = input.o output.o hi.o
TARGET = hi
$(TARGET):$(OBJECT)
	$(CC) -o $@ $(OBJECT)

$.o:$.c
	$(CC) -c -o $@ $<

clean:
	rm -f *.o $(TARGET)
```

### 변수 정의

-   `CC=gcc`: C 컴파일러로 `gcc`를 사용하도록 정의합니다.
-   `OBJECT = input.o output.o hi.o`: 최종 실행 파일을 만들기 위해 필요한 오브젝트 파일들을 정의합니다.
-   `TARGET = hi`: 최종적으로 생성될 실행 파일의 이름을 `hi`로 정의합니다.

### 규칙

1.  **`$(TARGET):$(OBJECT)` (hi: input.o output.o hi.o)**
    -   **목표 (Target)**: `hi` (실행 파일)
    -   **의존성 (Prerequisites)**: `input.o`, `output.o`, `hi.o` (오브젝트 파일들)
    -   **명령 (Command)**: `$(CC) -o $@ $(OBJECT)`
        -   `$@`는 현재 목표(`hi`)를 나타냅니다.
        -   이 규칙은 모든 오브젝트 파일이 준비되면, `gcc`를 사용하여 이들을 링크하여 `hi`라는 실행 파일을 생성합니다.

2.  **`$.o:$.c` (패턴 규칙)**
    -   **목표 (Target)**: `.o` 확장자를 가진 모든 파일 (예: `input.o`, `output.o`, `hi.o`)
    -   **의존성 (Prerequisites)**: `.c` 확장자를 가진 해당 소스 파일 (예: `input.c`, `output.c`, `hi.c`)
    -   **명령 (Command)**: `$(CC) -c -o $@ <
`
        -   `$@`는 현재 목표(예: `input.o`)를 나타냅니다.
        -   `$<`는 첫 번째 의존성(예: `input.c`)을 나타냅니다.
        -   이 규칙은 `.c` 파일을 컴파일하여 `.o` 오브젝트 파일을 생성합니다. `-c` 옵션은 링크하지 않고 컴파일만 수행하도록 지시합니다.

3.  **`clean:`
    -   **목표 (Target)**: `clean` (가상 목표, 실제 파일이 아님)
    -   **의존성 (Prerequisites)**: 없음
    -   **명령 (Command)**: `rm -f *.o $(TARGET)`
        -   이 규칙은 컴파일 과정에서 생성된 모든 오브젝트 파일(`*.o`)과 최종 실행 파일(`hi`)을 삭제합니다. 이는 프로젝트를 깨끗한 상태로 되돌릴 때 유용합니다.

## 3. 컴파일 및 실행 방법

1.  **컴파일**: `make.d` 폴더에서 다음 명령어를 실행합니다.

    ```bash
    make
    ```

    이 명령은 `Makefile`에 정의된 규칙에 따라 `input.c`, `output.c`, `hi.c`를 각각 컴파일하여 `input.o`, `output.o`, `hi.o`를 생성하고, 마지막으로 이들을 링크하여 `hi` 실행 파일을 만듭니다.

2.  **실행**: 컴파일이 완료되면 다음 명령어로 프로그램을 실행할 수 있습니다.

    ```bash
    ./hi
    ```

    프로그램은 사용자에게 숫자를 입력하라고 요청하고, 입력된 숫자만큼 "Hi"를 출력한 후 "Good Bye"를 출력하고 종료됩니다.

3.  **정리**: 생성된 오브젝트 파일과 실행 파일을 삭제하려면 다음 명령어를 실행합니다.

    ```bash
    make clean
    ```
