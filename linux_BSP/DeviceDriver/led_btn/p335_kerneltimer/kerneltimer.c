#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <linux/moduleparam.h>

#define DEBUG 1

static int timerVal = 100; // f = 100HZ, T = 1/100 = 10ms, 100 * 10ms = 1sec
module_param(timerVal, int, 0);
static int ledVal = 0;
module_param(ledVal, int, 0);
struct timer_list timerLed;

static void kerneltimer_func(struct timer_list *t);
static void kerneltimer_registertimer(unsigned long timeover)
{
    timerLed.expires = get_jiffies_64() + timeover; // 10ms * 100 = 1sec
    timer_setup(&timerLed, kerneltimer_func, 0);
    add_timer(&timerLed);
}

static void kerneltimer_func(struct timer_list *t)
{
#if DEBUG
    printk("ledVal : %#04x\n", (unsigned int)(ledVal));
#endif
    ledVal = ~ledVal & 0xff;
    mod_timer(t, get_jiffies_64() + timerVal);
}

static int kerneltimer_init(void)
{
#if DEBUG
    printk("timerVal : %d, sec : %d\n", timerVal, timerVal / HZ);
#endif
    kerneltimer_registertimer(timerVal);
    return 0;
}

static void kerneltimer_exit(void)
{
    if(timer_pending(&timerLed))
        del_timer(&timerLed);
}

module_init(kerneltimer_init);
module_exit(kerneltimer_exit);

MODULE_AUTHOR("KCCI-AIOT KSM");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");
