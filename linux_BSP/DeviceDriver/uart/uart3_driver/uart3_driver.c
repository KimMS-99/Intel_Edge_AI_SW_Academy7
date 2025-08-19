#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "uart3_raw"
// #define UART3_BASE_PHYS 0x7E201600
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

        kbuf[i] = readl(uart3_base + UART_DR) & 0xFF; // FIFO에서 한 바이트 꺼냄
    }

    if (i == 0)
        return 0;

    if (copy_to_user(buf, kbuf, i))
        return -EFAULT;

    return i;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = uart3_open,
    .read = uart3_read,
    .write = uart3_write,
};

static int major;

static int __init uart3_init(void)
{
    // 첫 번째 인자를 0으로 주면 커널이 비어있는 메이저 번호를 자동 배정
    // major = register_chrdev(0, DEVICE_NAME, &fops); // cat /proc/devices 또는 dmesg로 할당된 메이저 번호 확인
    major = register_chrdev(237, DEVICE_NAME, &fops);
    if (major < 0)
    {
        pr_err("Failed to register char device\n");
        return major;
    }

    // 리눅스 커널에서 I/O 메모리 주소(하드웨어 레지스터 주소 등) 를 커널이 접근 가능한 가상 주소로 매핑해주는 함수
    uart3_base = ioremap(UART3_BASE_PHYS, UART3_REG_SIZE); // 물리 주소 → 가상 주소로 바꿔줌, 가상 주소를 통해 레지스터에 접근
    if (!uart3_base)
    {
        unregister_chrdev(major, DEVICE_NAME);
        pr_err("Failed to map UART3 base\n");
        return -ENOMEM;
    }

    pr_info("UART3 driver loaded (major %d)\n", major);
    return 0;
}

static void __exit uart3_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    iounmap(uart3_base); // ioremap()은 커널 공간에서만 사용 가능함으로 쓰고나면 해제해야함.
    pr_info("UART3 driver unloaded\n");
}

module_init(uart3_init);
module_exit(uart3_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KimMS");
MODULE_DESCRIPTION("PL011 UART3 driver for BCM2711");
