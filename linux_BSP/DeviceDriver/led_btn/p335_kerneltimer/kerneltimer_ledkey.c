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

#define GPIOLEDCNT 8
#define GPIOKEYCNT 8
#define OFF 0
#define ON 1

static int gpioLed[] = {518,519,520,521,522,523,524,525};
static int gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static int gpioKey[] = {528,529,530,531,532,533,534,535};
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);

static void kerneltimer_func(struct timer_list *t);

static int timerVal = 100; // f = 100HZ, T = 1/100 = 10ms, 100 * 10ms = 1sec
module_param(timerVal, int, 0);
static int ledVal = 0, old_val;
module_param(ledVal, int, 0);
struct timer_list timerLed;

static int  gpioLedInit(void)
{
    int i;
    int ret = 0;
    char gpioName[10];
    for(i=0;i<GPIOLEDCNT;i++)
    {
        sprintf(gpioName,"led%d",i);
        ret = gpio_request(gpioLed[i], gpioName);
        if(ret < 0) {
            printk("Failed Request gpio%d error\n", gpioLed[i]);
            return ret;
        }
    }
    for(i=0;i<GPIOLEDCNT;i++)
    {
        ret = gpio_direction_output(gpioLed[i], OFF);
        if(ret < 0) {
            printk("Failed direction_output gpio%d error\n", gpioLed[i]);
         return ret;
        }
    }
    return ret;
}
static void gpioLedSet(long val)
{
    int i;
    for(i=0;i<GPIOLEDCNT;i++)
    {
        gpio_set_value(gpioLed[i], val & ( 0x01 << i));
    }
}
static void gpioLedFree(void)
{
    int i;
    for(i=0;i<GPIOLEDCNT;i++)
    {
        gpio_free(gpioLed[i]);
    }
}

static int gpioKeyInit(void)
{
    int i;
    int ret=0;
    char gpioName[10];
    for(i=0;i<GPIOKEYCNT;i++)
    {
        sprintf(gpioName,"key%d",i);
        ret = gpio_request(gpioKey[i], gpioName);
        if(ret < 0) {
            printk("Failed Request gpio%d error\n", 6);
            return ret;
        }
    }
    for(i=0;i<GPIOKEYCNT;i++)
    {
        ret = gpio_direction_input(gpioKey[i]);
        if(ret < 0) {
            printk("Failed direction_output gpio%d error\n", 6);
         return ret;
        }
    }
    return ret;
}
static int  gpioKeyGet(void)
{
    int i;
    int ret;
    int keyData=0;
    for(i=0;i<GPIOKEYCNT;i++)
    {
        ret=gpio_get_value(gpioKey[i]) << i;
        keyData |= ret;
    }
    return keyData;
}
static void gpioKeyFree(void)
{
    int i;
    for(i=0;i<GPIOKEYCNT;i++)
    {
        gpio_free(gpioKey[i]);
    }
}

static void kerneltimer_registertimer(unsigned long timeover)
{
    timerLed.expires = get_jiffies_64() + timeover; // 10ms * 100 = 1sec
    timer_setup(&timerLed, kerneltimer_func, 0);
	old_val = ledVal;
    add_timer(&timerLed);
}

static void kerneltimer_func(struct timer_list *t)
{
#if DEBUG
    printk("ledVal : %#04x\n", (unsigned int)(ledVal));
#endif
//    ledVal = ~ledVal & 0xff;
	ledVal = gpioKeyGet();
	if(ledVal != 0)
		old_val = ledVal;
	old_val = ~old_val & 0xff;
	gpioLedSet(old_val);
    mod_timer(t, get_jiffies_64() + timerVal);
}

static int kerneltimer_init(void)
{
#if DEBUG
    printk("timerVal : %d, sec : %d\n", timerVal, timerVal / HZ);
#endif
	int result = gpioKeyInit();
	if(result < 0) return result;
	result = gpioLedInit();
	if(result < 0) return result;
    kerneltimer_registertimer(timerVal);
    return 0;
}

static void kerneltimer_exit(void)
{
	gpioKeyFree();
	gpioLedFree();
    if(timer_pending(&timerLed))
        del_timer(&timerLed);
}

module_init(kerneltimer_init);
module_exit(kerneltimer_exit);

MODULE_AUTHOR("KCCI-AIOT KSM");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");
