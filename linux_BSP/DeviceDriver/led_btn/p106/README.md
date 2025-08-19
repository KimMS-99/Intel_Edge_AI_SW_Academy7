## 실행 방법

```bash
ubuntu@ubuntu04:~/pi_bsp/drivers/p106$ make
# 모듈 파일을 실행하기 위한 커널 적재
pi@pi03:/mnt/nfs_ubuntu $ sudo insmod hello.ko
# 실행된 메시지 보기
pi@pi03:/mnt/nfs_ubuntu $ dmesg
# 모듈 제거
pi@pi03:/mnt/nfs_ubuntu $ rmmod hello
```

## 커널 모듈 동작 흐름

1. 모듈 로드 (insmod hello.ko)
    - hello_init() 함수 자동 실행
    - 커널 로그에 "Hello, World" 출력

2. 모듈 동작 중
    - 별도 동작 없음 (대기 상태)

3. 모듈 제거 (rmmod hello)
    - hello_exit() 함수 자동 실행
    - 커널 로그에 "Goodbye, World" 출력

