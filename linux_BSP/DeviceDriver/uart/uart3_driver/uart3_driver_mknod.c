#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEVICE_NAME "uart3_raw"
#define UART3_BASE_PHYS 0xFE201600
#define UART3_REG_SIZE 0x90

static void __iomem *uart3_base; // 커널에서 쓸 수 있는 가상주소

#define UART_DR 0x00
#define UART_FR 0x18
#define UART_IBRD 0x24
#define UART_FBRD 0x28
#define UART_LCRH 0x2C
#define UART_CR 0x30
#define UART_ICR 0x44

#define UART_FR_TXFF (1 << 5)
#define UART_FR_RXFE (1 << 4)
static int uart3_open(struct inode *inode, struct file *file)
{
    // HW RX FIFO 드레인: 비어 있을 때까지 읽어서 버리기
    while (!(readl(uart3_base + UART_FR) & UART_FR_RXFE))
        (void)readl(uart3_base + UART_DR);

    writel(0x0, uart3_base + UART_CR);    // UART Disable
    writel(0x7FF, uart3_base + UART_ICR); // Clear interrupts
    writel(26, uart3_base + UART_IBRD);   // 115200 baud @ 48MHz
    writel(3, uart3_base + UART_FBRD);
    writel((1 << 4) | (3 << 5), uart3_base + UART_LCRH);          // FIFO + 8bit
    writel((1 << 0) | (1 << 8) | (1 << 9), uart3_base + UART_CR); // UARTEN, TXE, RXE

    printk(KERN_INFO "UART3 opened\n");
    return 0;
}

static ssize_t uart3_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    size_t i;
    char ch;

    for (i = 0; i < count; i++)
    {
        if (copy_from_user(&ch, buf + i, 1))
            return -EFAULT;

        while (readl(uart3_base + UART_FR) & UART_FR_TXFF) // FIFO(버퍼)가 꽉 차 있으면
            ;                                              // 자리 날 때까지 대기
        writel(ch, uart3_base + UART_DR);                  // 한 바이트를 송신 FIFO에 넣음
    }

    return count;
}

static ssize_t uart3_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    char kbuf[100];
    size_t i;

    for (i = 0; i < count && i < sizeof(kbuf); i++)
    {
        if (readl(uart3_base + UART_FR) & UART_FR_RXFE) // 수신 FIFO가 비었으면
            break;                                      // 반복 종료

        // FIFO에서 한 바이트 꺼냄
        kbuf[i] = readl(uart3_base + UART_DR) & 0xFF; // 32비트를 읽어서 하위 8비트만 추출
    }

    if (i == 0)
        return 0;

    if (copy_to_user(buf, kbuf, i))
        return -EFAULT;

    return i;
}

static struct cdev uart3_cdev;
static dev_t devno;               // 메이저+마이너
static struct class *uart3_class; // /sys/class/ 하위 클래스

/*  선택: 권한 0666으로 만들고 싶다면 class->devnode 콜백 사용
    커널 버전에 따라 devnode 시그니처가 다를 수 있으니, 현재 커널 헤더 선언과 동일하게 작성해야 함. */
// static char *uart3_devnode(struct device *dev, umode_t *mode)
static char *uart3_devnode(const struct device *dev, umode_t *mode)
{
    if (mode)
        *mode = 0666;
    return NULL;
}

/* fops는 기존 그대로 */
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = uart3_open,
    .read = uart3_read,
    .write = uart3_write,
};

static int __init uart3_init(void)
{
    int ret;

    /*  1) 메이저/마이너 번호 자동 할당
        첫 번째 인자 &devno에 major+minor 묶인 dev_t가 반환됨
        여기서 minor=0 하나만 씀*/
    ret = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME);
    if (ret)
    {
        pr_err("alloc_chrdev_region failed: %d\n", ret);
        return ret;
    }
    /* 메이저 고정 번호로 하는 방법 */
    // dev_t devno = MKDEV(237, 0);
    // int ret = register_chrdev_region(devno, 1, "uart3_raw");
    // if (ret)
    // { /* 이미 점유 중이면 실패 */
    // }

    /*  2) cdev 등록
        file_operations 구조체(fops)를 cdev에 연결 후 커널에 등록
        open/read/write 구현은 기존 함수 재사용 가능*/
    cdev_init(&uart3_cdev, &fops);
    uart3_cdev.owner = THIS_MODULE;

    ret = cdev_add(&uart3_cdev, devno, 1);
    if (ret)
    {
        pr_err("cdev_add failed: %d\n", ret);
        unregister_chrdev_region(devno, 1);
        return ret;
    }

    /*  3) 클래스 생성(+ 퍼미션 콜백)
        예전 커널: class_create(THIS_MODULE, name)
        최신 커널: class_create(name)
        /sys/class/DEVICE_NAME 디렉토리가 생성됨*/
    // uart3_class = class_create(THIS_MODULE, DEVICE_NAME); // 예전 커널 버전
    uart3_class = class_create(DEVICE_NAME);
    if (IS_ERR(uart3_class))
    {
        pr_err("class_create failed\n");
        cdev_del(&uart3_cdev);
        unregister_chrdev_region(devno, 1);
        return PTR_ERR(uart3_class);
    }
    uart3_class->devnode = uart3_devnode; // 선택

    /*  4) 디바이스 생성 → /dev/uart3_raw 자동 생성됨
        /dev/DEVICE_NAME가 자동 생성됨 (devtmpfs/udev가 켜져 있을 때)
        mknod 명령어 없이 insmod만 해도 접근 가능*/
    if (IS_ERR(device_create(uart3_class, NULL, devno, NULL, DEVICE_NAME)))
    {
        pr_err("device_create failed\n");
        class_destroy(uart3_class);
        cdev_del(&uart3_cdev);
        unregister_chrdev_region(devno, 1);
        return -EINVAL;
    }

    /*  5) MMIO 매핑
        물리 주소(UART3_BASE_PHYS)를 커널 가상주소(uart3_base)로 매핑
        이후 readl/writel 등으로 레지스터 직접 접근 가능*/
    uart3_base = ioremap(UART3_BASE_PHYS, UART3_REG_SIZE);
    if (!uart3_base)
    {
        pr_err("Failed to map UART3 base\n");
        device_destroy(uart3_class, devno);
        class_destroy(uart3_class);
        cdev_del(&uart3_cdev);
        unregister_chrdev_region(devno, 1);
        return -ENOMEM;
    }

    pr_info("UART3 driver loaded (major=%d minor=%d) -> /dev/%s\n",
            MAJOR(devno), MINOR(devno), DEVICE_NAME);
    return 0;
}

static void __exit uart3_exit(void)
{
    /* 역순 해제 */
    iounmap(uart3_base);                // ioremap()으로 만든 MMIO 매핑을 해제. 커널 가상 주소(uart3_base)와 실제 하드웨어 레지스터 매핑을 끊어 버림.
    device_destroy(uart3_class, devno); // device_create()로 만든 sysfs 노드와 /dev 노드(devtmpfs/udev)를 제거
    class_destroy(uart3_class);         // class_create()로 만든 클래스 오브젝트를 정리. /sys/class/uart3_raw 항목 제거.
    cdev_del(&uart3_cdev);              // cdev_add()로 VFS에 등록했던 캐릭터 디바이스 엔트리 삭제.
    unregister_chrdev_region(devno, 1); // alloc_chrdev_region() 또는 register_chrdev_region()으로 예약했던 번호 범위(dev_t) 반환
    pr_info("UART3 driver unloaded\n");
}

module_init(uart3_init);
module_exit(uart3_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KimMS");
MODULE_DESCRIPTION("Bare-metal PL011 UART3 driver for BCM2711");
