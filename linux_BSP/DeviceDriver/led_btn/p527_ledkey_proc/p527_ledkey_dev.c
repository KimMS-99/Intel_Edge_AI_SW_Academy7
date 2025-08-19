#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       
#include <linux/moduleparam.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>

#define gpioName(a,b) #a#b     //"led""0" == "led0"
#define GPIOLEDCNT 8
#define GPIOKEYCNT 8
#define OFF 0
#define ON 1

#define   LED_DEV_NAME            "ledkeydev"
#define   LED_DEV_MAJOR            230      
#define DEBUG 1

DECLARE_WAIT_QUEUE_HEAD(WaitQueue_Read);
static unsigned long ledvalue = 15;
static char * twostring = NULL;
static int sw_irq[8] = {0};
static char sw_no = 0;

static struct proc_dir_entry *keyledproc_root_fp   = NULL;
static struct proc_dir_entry *keyledproc_led_fp    = NULL;
static struct proc_dir_entry *keyledproc_key_fp    = NULL;

module_param(ledvalue, ulong ,0);
module_param(twostring,charp,0);

static int gpioLed[GPIOLEDCNT] = {518,519,520,521,522,523,524,525};
static int gpioKey[GPIOKEYCNT] = {528,529,530,531,532,533,534,535};

static int gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static int gpioKeyInit(void);
//static int gpioKeyGet(void);
static void gpioKeyFree(void);

static int	gpioLedInit(void)
{
	int i;
	int ret = 0;
	for(i=0;i<GPIOLEDCNT;i++)
	{
		ret = gpio_request(gpioLed[i], gpioName(led,i));
		if(ret < 0) {
			printk("Failed Request gpio%d error\n", 6);
			return ret;
		}
	}
	for(i=0;i<GPIOLEDCNT;i++)
	{
		ret = gpio_direction_output(gpioLed[i], OFF);
		if(ret < 0) {
			printk("Failed direction_output gpio%d error\n", 6);
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
		gpio_set_value(gpioLed[i], (val>>i) & 0x01);
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
	int ret=0;;
	for(i=0;i<GPIOKEYCNT;i++)
	{
		ret = gpio_request(gpioKey[i], gpioName(key,i));
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
/*
static int	gpioKeyGet(void) 
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
*/
static void gpioKeyFree(void) 
{
	int i;
	for(i=0;i<GPIOKEYCNT;i++)
	{
		gpio_free(gpioKey[i]);
	}
}


static void gpioKeyToIrq(void)
{
	int i;
    for (i = 0; i < GPIOKEYCNT; i++) {
        sw_irq[i] = gpio_to_irq(gpioKey[i]);
	}
}

static void gpioKeyFreeIrq(void)
{
	int i;
	for (i = 0; i < GPIOKEYCNT; i++){
		free_irq(sw_irq[i],NULL);
	}
}

static int ledkeydev_open (struct inode *inode, struct file *filp)
{
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "ledkeydev open -> major : %d\n", num0 );
    printk( "ledkeydev open -> minor : %d\n", num1 );

    return 0;
}

static ssize_t ledkeydev_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
//	char kbuf;
	int ret;
#if DEBUG
    printk( "ledkeydev read -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
#endif
//	kbuf = gpioKeyGet();     

	if(!(filp->f_flags & O_NONBLOCK))  //BLOCK Mode
	{
  		if(sw_no == 0)
			wait_event_interruptible(WaitQueue_Read,sw_no);
//  		wait_event_interruptible_timeout(WaitQueue_Read,sw_no,100); //100: 1/100 *100 = 1Sec

	}
	ret=copy_to_user(buf,&sw_no,count);
	sw_no = 0;
	if(ret < 0)
		return -ENOMEM;
    return count;
}

static ssize_t ledkeydev_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;
	int ret;
#if DEBUG
    printk( "ledkeydev write -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
#endif
	ret=copy_from_user(&kbuf,buf,count);
	if(ret < 0)
		return -ENOMEM;
	gpioLedSet(kbuf);
    return count;
}

static long ledkeydev_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

#if DEBUG
    printk( "ledkeydev ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
#endif
    return 0;
}
static unsigned int ledkeydev_poll(struct file * filp, struct poll_table_struct * wait)
{
	unsigned int mask = 0;
	printk("_key : %u \n",(wait->_key & POLLIN));
	if(wait->_key & POLLIN)
		poll_wait(filp, &WaitQueue_Read, wait);
	if(sw_no > 0)
		mask = POLLIN;
	return mask;
}

static int ledkeydev_release (struct inode *inode, struct file *filp)
{
    printk( "ledkeydev release \n" );
    return 0;
}

struct file_operations ledkeydev_fops =
{
    .owner    = THIS_MODULE,
    .open     = ledkeydev_open,     
    .read     = ledkeydev_read,     
    .write    = ledkeydev_write,    
	.unlocked_ioctl = ledkeydev_ioctl,
	.poll	  = ledkeydev_poll,
    .release  = ledkeydev_release,  
};

static irqreturn_t sw_isr(int irq, void *unuse)
{
	int i;
	for(i=0;i<GPIOKEYCNT;i++)
	{
		if(irq == sw_irq[i])
		{
			sw_no = i+1;
			break;
		}
	}
	printk("IRQ : %d, sw_no : %d\n",irq,sw_no);
	wake_up_interruptible(&WaitQueue_Read);
	return IRQ_HANDLED;
}
static ssize_t proc_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf[10];
	int ret;
	int len=0;
	kbuf[0] = sw_no+0x30;
//	kbuf[1] = '\n';
	kbuf[1] = 0;
	len = strlen(kbuf);
	ret=copy_to_user(buf,kbuf,len);
	sw_no = 0;
 	*f_pos = -1;
    return len;
}

static ssize_t proc_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf[10];
	int ret;
//	get_user(kbuf,buf);
//	printk("count %d %s\n",count,buf);
	ret=copy_from_user(kbuf,buf,count);
	gpioLedSet(simple_strtoul(kbuf,NULL,10));
    return count;
//	return -EFAULT;
}
struct  proc_ops proc_led_fops =
{
    .proc_write    = proc_write,
};
struct  proc_ops proc_key_fops =
{
    .proc_read     = proc_read,
};

static void mkproc(void)
{
	keyledproc_root_fp  = proc_mkdir( "ledkey", 0 );

	keyledproc_led_fp   = proc_create_data( "led", S_IFREG | S_IRWXU | S_IRWXG | S_IRWXO, keyledproc_root_fp, &proc_led_fops, NULL);
	keyledproc_key_fp   = proc_create_data( "key", S_IFREG | S_IRWXU | S_IRWXG | S_IRWXO, keyledproc_root_fp, &proc_key_fops, NULL);
}

static void rmproc(void)
{
	remove_proc_entry( "led"  , keyledproc_root_fp );
	remove_proc_entry( "key"  , keyledproc_root_fp );
	remove_proc_entry( "ledkey" , 0 );
}
static int ledkeydev_init(void)
{
    int result=0;
	int i;

    printk( "ledkeydev ledkeydev_init \n" );    

    result = register_chrdev( LED_DEV_MAJOR, LED_DEV_NAME, &ledkeydev_fops);
    if (result < 0) return result;

	result = gpioLedInit();
	if(result < 0)
  		return result;     /* Device or resource busy */

	result = gpioKeyInit();
	if(result < 0)
  		return result;     /* Device or resource busy */
	gpioKeyToIrq();

	for(i=0;i<GPIOKEYCNT;i++)
	{
		result = request_irq(sw_irq[i],sw_isr,IRQF_TRIGGER_RISING,gpioName(key,i),NULL);
		if(result)
		{
			printk("#### FAILED Request irq %d. error : %d \n", sw_irq[i], result);
			break;
		}
	}
	mkproc();
    return result;
}

static void ledkeydev_exit(void)
{
    printk( "ledkeydev ledkeydev_exit \n" );    
    unregister_chrdev( LED_DEV_MAJOR, LED_DEV_NAME );
	rmproc();
	gpioLedFree();
	gpioKeyFreeIrq();
	gpioKeyFree();
}

module_init(ledkeydev_init);
module_exit(ledkeydev_exit);

MODULE_AUTHOR("KCCI-AIOT KSH");
MODULE_DESCRIPTION("led key test module");
MODULE_LICENSE("Dual BSD/GPL");
