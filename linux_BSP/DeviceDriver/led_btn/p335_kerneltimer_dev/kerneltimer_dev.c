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
#include <linux/interrupt.h>

#define DEBUG 1

#define   LEDKEY_DEV_NAME            "ledkey"
#define   LEDKEY_DEV_MAJOR            230

#define GPIOCNT 8
#define OFF 0
#define ON 1

typedef struct {
    int keyNum;
    int irqKey[GPIOCNT];
} keyDataStruct;

static int gpioLed[] = {518,519,520,521,522,523,524,525};
static int gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static int gpioKey[] = {528,529,530,531,532,533,534,535};
static int gpioKeyInit(void);
//static int gpioKeyGet(void);
static void gpioKeyFree(void);

// 키 인터럽트 관련
static int irqKeyInit(keyDataStruct * pkeyData);
static void irqKeyFree(keyDataStruct * pKeyData);
// 타이머 관련
static void kerneltimer_func(struct timer_list *t);

static int openFlag = 0;

static DEFINE_MUTEX(keyMutex);

static int timerVal = 100; // f = 100HZ, T = 1/100 = 10ms, 100 * 10ms = 1sec
module_param(timerVal, int, 0);
static int ledVal = 0, old_val;
module_param(ledVal, int, 0);
struct timer_list timerLed;

static int gpioLedInit(void)
{
    int i;
    int ret=0;
    char gpioName[10];
    for(i=0;i<GPIOCNT;i++)
    {
        sprintf(gpioName,"led%d",i);
        ret = gpio_request(gpioLed[i], gpioName);
        if(ret < 0)
        {
            printk("Failed request gpio%d error\n",gpioLed[i]);
            return ret;
        }
        ret = gpio_direction_output(gpioLed[i],OFF);
        if(ret < 0)
        {
            printk("Failed directon_output gpio%d error\n",gpioLed[i]);
            return ret;
        }
    }
    return ret;
}
static void gpioLedSet(long val)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        gpio_set_value(gpioLed[i],(val & (0x01 << i)));
    }
}
static void gpioLedFree(void)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        gpio_free(gpioLed[i]);
    }
}
static int gpioKeyInit(void)
{
    int i;
    int ret=0;
    char gpioName[10];
    for(i=0;i<GPIOCNT;i++)
    {
        sprintf(gpioName,"key%d",i);
        ret = gpio_request(gpioKey[i], gpioName);
        if(ret < 0) {
            printk("Failed Request gpio%d error\n", gpioKey[i]);
            return ret;
        }
        ret = gpio_direction_input(gpioKey[i]);
        if(ret < 0) {
            printk("Failed direction_output gpio%d error\n", gpioKey[i]);
            return ret;
        }
    }
    return ret;
}
/*
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
}*/
static void gpioKeyFree(void)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        gpio_free(gpioKey[i]);
    }
}

static irqreturn_t keyIsr(int irq, void * data)
{
    int i;
    keyDataStruct * pKeyData = (keyDataStruct *)data;
    for(i=0;i<GPIOCNT;i++)
    {
        if(irq == pKeyData->irqKey[i])
        {
            if(mutex_trylock(&keyMutex) != 0)
            {
                pKeyData->keyNum = i + 1;
                mutex_unlock(&keyMutex);
                break;
            }
        }
    }
#if DEBUG
    printk("keyIsr() irq : %d, keyNum : %d\n",irq, pKeyData->keyNum);
#endif
    return IRQ_HANDLED;
}

static int irqKeyInit(keyDataStruct * pkeyData)
{   
    int i;
    int ret=0;
    for(i=0;i<GPIOCNT;i++)
    {   
        pkeyData->irqKey[i] = gpio_to_irq(gpioKey[i]);
        if(pkeyData->irqKey[i] < 0)
        {   
            printk("Failed gpio_to_irq() gpio%d error\n",gpioKey[i]);
            return pkeyData->irqKey[i];
        }
#if DEBUG
        else
            printk("gpio_to_irq() gpio%d (irq%d) \n",gpioKey[i],pkeyData->irqKey[i]);
#endif
    }
#if DEBUG
//    printk( "call read -> key : %#04x\n", kbuf );
#endif
    return ret;
}

static void irqKeyFree(keyDataStruct * pKeyData)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        free_irq(pKeyData->irqKey[i], pKeyData);
    }
}

static int ledkey_open (struct inode *inode, struct file *filp)
{

#if DEBUG
    int num0 = MAJOR(inode->i_rdev);
    int num1 = MINOR(inode->i_rdev);
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
#endif
    int result=0;
    keyDataStruct * pKeyData;
    char * irqName[GPIOCNT] = {"irqKey0","irqKey1","irqKey2","irqKey3","irqKey4","irqKey5","irqKey6","irqKey7",};

	pKeyData = (keyDataStruct *)kmalloc(sizeof(keyDataStruct),GFP_KERNEL);
    if(!pKeyData)
        return -ENOMEM;

	memset(pKeyData,0,sizeof(keyDataStruct));

	result = irqKeyInit(pKeyData);
    if(result < 0)
        return result;

	for(int i=0;i<GPIOCNT;i++)
    {
        result = request_irq(pKeyData->irqKey[i],keyIsr,IRQF_TRIGGER_RISING,irqName[i],pKeyData);
        if(result < 0 )
            return result;
    }

/*    if(openFlag)
        return -EBUSY;
    else
        openFlag = 1;
*/
    if(!try_module_get(THIS_MODULE))
        return -ENODEV;

    filp->private_data = pKeyData;

    return 0;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf = 0;
	keyDataStruct * pKeyData = (keyDataStruct *)filp->private_data;
	if(mutex_trylock(&keyMutex) != 0)
    {
        if(pKeyData->keyNum != 0)
        {
            kbuf=(char)(pKeyData->keyNum);
            pKeyData->keyNum = 0;
        }
        mutex_unlock(&keyMutex);
    }
#if 1

    put_user(kbuf,buf);
#else
    int ret=copy_to_user(buf,&kbuf,sizeof(kbuf));
    if(ret < 0)
        return ret;
#endif

    return count;

}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
//    char kbuf;

#if 1
    get_user(ledVal,buf);
//	if(kbuf != 0) // 사용자 영역에서 처리중
//	ledVal = kbuf;
#else
    int ret;
    ret=copy_from_user(&kbuf,buf,sizeof(kbuf));
#endif

#if DEBUG
    printk( "call write -> led(ledVal) : %#04x\n", ledVal );
#endif

    return count;
}

static int ledkey_release (struct inode *inode, struct file *filp)
{
	keyDataStruct * pKeyData = (keyDataStruct *)filp->private_data;

    printk( "call release \n" );

	irqKeyFree(pKeyData);

    module_put(THIS_MODULE);
    openFlag = 0;

    if(filp->private_data)
        kfree(filp->private_data);

    return 0;
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
    ledVal = ~ledVal & 0xff;
/*	if(ledVal != 0)
		old_val = ledVal;
	old_val = ~old_val & 0xff;
*/
	gpioLedSet(ledVal);
    mod_timer(t, get_jiffies_64() + timerVal);
}

struct file_operations ledkey_fops =
{
//    .owner    = THIS_MODULE,
    .open     = ledkey_open,
    .read     = ledkey_read,
    .write    = ledkey_write,
    .release  = ledkey_release,
};

static int kerneltimer_init(void)
{
#if DEBUG
    printk("timerVal : %d, sec : %d\n", timerVal, timerVal / HZ);
#endif

    mutex_init(&keyMutex);

	int result = gpioKeyInit();
	if(result < 0) return result;
	result = gpioLedInit();
	if(result < 0) return result;
    kerneltimer_registertimer(timerVal);

    result = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if (result < 0) return result;

    return 0;
}

static void kerneltimer_exit(void)
{
#if DEBUG
	printk("exit\n");
#endif
	unregister_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME );
	
	gpioKeyFree();
	gpioLedFree();
	mutex_destroy(&keyMutex);
    if(timer_pending(&timerLed))
        del_timer(&timerLed);
}

module_init(kerneltimer_init);
module_exit(kerneltimer_exit);

MODULE_AUTHOR("KCCI-AIOT KSM");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");
