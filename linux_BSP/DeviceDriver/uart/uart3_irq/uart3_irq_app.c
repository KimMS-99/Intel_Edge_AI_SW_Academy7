#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <poll.h>

#define DEVICE "/dev/uart3_raw"
#define BUFSIZE 256
#define TIMEOUT_MS 2000 // 전체 대기 시간
#define SLICE_MS 50     // 재-poll 간격

// 논블로킹 안전 쓰기: 부분 전송/ EAGAIN/ EINTR 모두 처리
static int write_all_nonblock(int fd, const char *buf, size_t len, int timeout_ms)
{
    size_t off = 0;
    while (off < len)
    {
        ssize_t n = write(fd, buf + off, len - off);
        if (n > 0)
        {
            off += (size_t)n;
            continue;
        }
        if (n < 0)
        {
            if (errno == EINTR)
                continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                struct pollfd wp = {.fd = fd, .events = POLLOUT};
                int pr = poll(&wp, 1, timeout_ms);
                if (pr == 0)
                    return -ETIMEDOUT;
                if (pr < 0)
                    return -errno;
                if (wp.revents & (POLLERR | POLLHUP | POLLNVAL))
                    return -EIO;
                continue; // POLLOUT 준비됨 → 다시 write()
            }
            return -errno;
        }
    }
    return 0;
}

// 개행 나올 때까지 논블로킹 누적 읽기(+짧은 재-poll)
static ssize_t read_line_nonblock(int fd, char *out, size_t outsz, int timeout_ms)
{
    ssize_t total = 0;
    if (outsz == 0)
        return -EINVAL;
    out[0] = '\0';

    while (total < (ssize_t)outsz - 1)
    {
        // 우선 지금 당장 읽어보기
        ssize_t n = read(fd, out + total, outsz - 1 - total);
        if (n > 0)
        {
            total += n;
            if (memchr(out, '\n', (size_t)total))
                break; // 한 줄 완성
            continue;  // 더 들어올 수 있으니 즉시 재시도
        }
        if (n == 0)
            break; // peer closed or no data

        // n < 0
        if (errno == EINTR)
            continue;
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            // 잠깐 더 기다려서 같은 줄의 나머지를 모음
            int wait = (timeout_ms > SLICE_MS) ? SLICE_MS : timeout_ms;
            if (wait <= 0)
                break;

            struct pollfd p = {.fd = fd, .events = POLLIN};
            int pr = poll(&p, 1, wait);
            if (pr < 0)
            {
                if (errno == EINTR)
                    continue;
                return -errno;
            }
            if (pr == 0)
            {
                timeout_ms -= wait;
                continue;
            } // 타임슬라이스 소진 → 재시도/종료 판단
            if (p.revents & (POLLERR | POLLHUP | POLLNVAL))
                break;
            // POLLIN이면 루프 상단에서 read 재시도
            continue;
        }
        // 그 외 에러
        return -errno;
    }

    out[total] = '\0';
    return total; // 0이면 타임아웃/상대 종료로 간주
}

int main(void)
{
    // 논블로킹으로 연다
    int fd = open(DEVICE, O_RDWR | O_NONBLOCK);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    char send[BUFSIZE];
    char recv[BUFSIZE];

    while (1)
    {
        fputs("Input Send Text(Exit : q, Q) : ", stdout);
        fflush(stdout);

        if (!fgets(send, sizeof(send), stdin))
            break;
        send[strcspn(send, "\n")] = '\0';
        if (!strcmp(send, "q") || !strcmp(send, "Q"))
            break;

        // 라인 전송(개행 추가)
        size_t slen = strlen(send);
        if (slen + 1 < sizeof(send))
        {
            send[slen] = '\n';
            send[slen + 1] = '\0';
            slen += 1;
        }

        int wr = write_all_nonblock(fd, send, slen, TIMEOUT_MS);
        if (wr < 0)
        {
            if (wr == -ETIMEDOUT)
                fprintf(stderr, "[Timeout] write POLLOUT\n");
            else
                fprintf(stderr, "write error: %s\n", strerror(-wr));
            break;
        }
        printf("Sent : %s", send); // send 끝에 '\n' 포함

        // 같은 줄의 에코가 모일 때까지 수신
        ssize_t r = read_line_nonblock(fd, recv, sizeof(recv), TIMEOUT_MS);
        if (r < 0)
        {
            fprintf(stderr, "read error: %s\n", strerror((int)-r));
            break;
        }
        else if (r == 0)
        {
            puts("[Timeout] No data received.");
        }
        else
        {
            printf("Recv : %s", recv); // recv가 '\n' 포함이면 자연스레 개행
        }
    }

    close(fd);
    return 0;
}
