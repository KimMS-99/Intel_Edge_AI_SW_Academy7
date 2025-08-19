#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       

#include <linux/gpio.h>
#include <linux/moduleparam.h>

#define   LEDKEY_DEV_NAME            "ledkey"
#define   LEDKEY_DEV_MAJOR            230      

#define OFF 0
#define ON 1
#define GPIOCNT 8

static int gpioLedInit(void);
static void gpioLedSet(char *);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static void gpioKeyGet(char *);
static void gpioKeyFree(void);

static int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
static int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};

static int onevalue = 1;
static char * twostring = NULL;
static int openFlag = 0;

module_param(onevalue, int ,0);
module_param(twostring,charp,0);

static int ledkey_open (struct inode *inode, struct file *filp)
{
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );

	if(openFlag)
		return -EBUSY;
	else
		openFlag = 1;

	if(!try_module_get(THIS_MODULE))
		return -ENODEV;

//    return -ENOMEM;
    return 0;
}

static loff_t ledkey_llseek (struct file *filp, loff_t off, int whence )
{
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
    return 0x23;
} 

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf[8];
    printk( "call read -> buf : %08X, count : %08X \n", (unsigned int)buf, count );
	gpioKeyGet(kbuf);

#if 0
	int ret=copy_to_user(buf,kbuf,count);
	if(ret < 0)
		return ret;
	return count;
#else
	for(int i=0;i<count;i++)
		put_user(kbuf[i],buf++);
	return count;
#endif
}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf[8];
    printk( "call write -> buf : %08X, count : %08X \n", (unsigned int)buf, count );

#if 0
	int ret=copy_from_user(kbuf,buf,count);
	if(ret < 0)
		return ret;
#else
	for(int i=0;i<count;i++)
		get_user(kbuf[i],buf++);
#endif
	gpioLedSet(kbuf);
	return count;
}

//int ledkey_ioctl (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{

    printk( "call ioctl -> cmd : %08X, arg : %08X \n", cmd, (unsigned int)arg );
    return 0x53;
}

static int ledkey_release (struct inode *inode, struct file *filp)
{
    printk( "call release \n" );
	module_put(THIS_MODULE);
	openFlag = 0;
    return 0;
}

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
static void gpioLedSet(char *pKbuff)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_set_value(gpioLed[i],pKbuff[i]);
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
static void	gpioKeyGet(char *pKbuff)
{
	int i;
//	int ret;
//	int keyData=0;
	for(i=0;i<GPIOCNT;i++)
	{
//		ret=gpio_get_value(gpioKey[i]) << i;
//		keyData |= ret;
//		ret=gpio_get_value(gpioKey[i]);
//		keyData = keyData | ( ret << i );
		pKbuff[i]=gpio_get_value(gpioKey[i]);
	}
//	return keyData;
}
static void gpioKeyFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioKey[i]);
	}
}

struct file_operations ledkey_fops =
{
//    .owner    = THIS_MODULE,
    .open     = ledkey_open,     
    .read     = ledkey_read,     
    .write    = ledkey_write,    
	.unlocked_ioctl = ledkey_ioctl,
    .llseek   = ledkey_llseek,   
    .release  = ledkey_release,  
};

static int ledkey_init(void)
{
    int result;

    printk( "call ledkey_init \n" );    
	result = gpioLedInit();
	if(result < 0)
		return result;

	result = gpioKeyInit();
	if(result < 0)
		return result;

    result = register_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if (result < 0) return result;

    return 0;
}

static void ledkey_exit(void)
{
    printk( "call ledkey_exit \n" );    
    unregister_chrdev( LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME );
	gpioLedFree();
	gpioKeyFree();
}

module_init(ledkey_init);
module_exit(ledkey_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("kcci");
MODULE_DESCRIPTION("led key test module");
