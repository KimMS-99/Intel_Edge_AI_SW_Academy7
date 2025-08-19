#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>   // open()
#include <termios.h> // termios, tcgetattr(), tcsetattr()
#include <unistd.h>  // read(), write(), close()
#include <errno.h>

#define SERIAL_PORT "/dev/ttyAMA3" // uart3
#define BAUDRATE B9600

int main()
{
    int fd;

    // 포트 열기
    fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        perror("Failed to open serial port");
        return 1;
    }

    // UART 설정
    struct termios options;
    // 현재 포트 설정 가져오기
    tcgetattr(fd, &options);

    // 보드레이트 설정
    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);

    // 포맷 설정: 8N1 (8비트 데이터, 패리티 없음, 1 스톱 비트)
    options.c_cflag &= ~PARENB; // 패리티 없음
    options.c_cflag &= ~CSTOPB; // 1 스톱 비트
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8; // 8 데이터 비트

    // 기타 설정
    options.c_cflag |= (CLOCAL | CREAD);                // 로컬 연결, 수신 허용
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw 입력 모드
    options.c_iflag &= ~(IXON | IXOFF | IXANY);         // 소프트웨어 흐름제어 비활성화
    options.c_oflag &= ~OPOST;                          // Raw 출력 모드

    // 설정 적용
    tcsetattr(fd, TCSANOW, &options);

    printf("[UART3 loopback test start]\n");

    unsigned char send_byte = 'A';
    unsigned char recv_byte;

    while (1)
    {
        printf("Sending: %c (%d)\n", send_byte, send_byte);

        // 데이터 보내기
        int n_written = write(fd, &send_byte, 1);
        if (n_written < 0)
        {
            perror("Write failed");
        }

        // 데이터 받기 (반복 대기)
        int attempts = 0;
        while (attempts++ < 100)
        { // 100번까지만 시도
            int n_read = read(fd, &recv_byte, 1);
            if (n_read > 0)
            {
                printf("Received: %c (%d)\n", recv_byte, recv_byte);
                break;
            }
            usleep(10000); // 10ms 기다림
        }

        // 다음 문자로
        send_byte++;
        if (send_byte > 'Z')
            send_byte = 'A';

        sleep(1);
    }

    // 포트 닫기
    close(fd);
    return 0;
}
