#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <errno.h>

#define DEVICE "/dev/uart3_raw"
#define BUFSIZE 256

int main()
{
    int fd = open(DEVICE, O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open device");
        return 1;
    }

    char send[BUFSIZE] = "Loopback Test!\n";
    char recv[BUFSIZE] = {0};

    while (1)
    {
        fputs("Input Send Text(Exit : q, Q) : ", stdout);
        fflush(stdout); // 출력 버퍼를 강제로 비움

        if (fgets(send, sizeof(send), stdin) == NULL)
            break;

        // 줄바꿈 제거 (fgets는 개행까지 입력 받음)
        send[strcspn(send, "\n")] = '\0'; // '\n' 문자의 위치를 찾아줌
        if (!strcmp(send, "q") || !strcmp(send, "Q"))
            break;

        strcat(send, "\n"); // write

        if (write(fd, send, strlen(send)) < 0)
        {
            perror("Write failed");
            close(fd);
            return 1;
        }

        printf("Send : %s\n", send);

        fd_set readfds;
        struct timeval timeout;

        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        timeout.tv_sec = 2; // 최대 2초 대기
        timeout.tv_usec = 0;

        int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);
        // ret > 0: 이벤트가 하나 이상 발생함
        if (ret > 0 && FD_ISSET(fd, &readfds)) // select() 호출 시 readfds는 읽기 이벤트가 발생한 fd들로 업데이트됨, FD_ISSET 매크로는 특정 fd가 그 목록에 포함되어 있는지 검사함
        {
            // 개행 나올 때까지 누적 읽기
            ssize_t total = 0;
            while (1)
            {
                // 수신 데이터 있음
                ssize_t bytes_read;
                bytes_read = read(fd, recv + total, sizeof(recv) - 1 - total);
                if (bytes_read > 0)
                {
                    total += bytes_read;
                    // 버퍼 풀 방지
                    if (total >= (ssize_t)sizeof(recv) - 1)
                        break;

                    // 라인 단위 프로토콜이면 개행 만나면 종료
                    if (memchr(recv, '\n', total))
                        break;

                    // 블로킹 read라면 여기서 계속 더 들어올 수 있음.
                    // 논블록이라면 bytes_read>0인데 개행 못찾은 경우, 다음 select()로 넘어가도 됨.
                    continue;
                }

                if (bytes_read == 0)
                    // 드라이버가 현재 줄 게 없다고 0을 준 상황
                    // 일단 한 텀 종료해서 바깥 select로 다시 돌아가는 선택을 함
                    continue;
                // bytes_read < 0: 에러 처리
                if (errno == EINTR)
                    continue; // 신호: 다시 시도
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break; // 논블록: 당장 없음
                perror("read");
                break;
            }
            if (total > 0)
            {
                recv[total] = '\0';
                printf("Recv : %s", recv);
            }
        }
        else if (ret == 0)
        {
            // 타임아웃
            puts("[Timeout] No data received.");
        }
        else
        {
            perror("select() error");
            break;
        }
    }

    close(fd);
    return 0;
}