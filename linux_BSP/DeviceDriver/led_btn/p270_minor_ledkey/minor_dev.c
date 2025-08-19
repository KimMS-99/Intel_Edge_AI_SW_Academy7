#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       
#include <linux/gpio.h>
#include <linux/moduleparam.h>
#include <asm/uaccess.h>

#define   MINOR_DEV_NAME        "minordev"
#define   MINOR_DEV_MAJOR            230

#define OFF 0
#define ON 1
#define GPIOCNT 8
//#define DEBUG

static int ledval = 0;
module_param(ledval, int, 0);

static long gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static long gpioKeyInit(void);
static long gpioKeyGet(void);
static void gpioKeyFree(void);

static int gpioLed[] = {518,519,520,521,522,523,524,525};
static int gpioKey[] = {528,529,530,531,532,533,534,535};

static long gpioLedInit(void)
{
	long ret = 0;
	int i;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"gpio%d",gpioLed[i]);
		ret = gpio_request(gpioLed[i],gpioName);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed request gpio%d error\n",gpioLed[i]);
#endif
			return ret;
		}
	}
	for(i=0;i<GPIOCNT;i++)
	{
		ret = gpio_direction_output(gpioLed[i],OFF);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed direction_output gpio%d error\n",gpioLed[i]);
#endif
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
		gpio_set_value(gpioLed[i],val & (0x1 << i));
//		gpio_set_value(gpioLed[i],(val>>i) & 0x1);
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

static long gpioKeyInit(void)
{
	long ret = 0;
	int i;
	char gpioName[10];
	for(i=0;i<GPIOCNT;i++)
	{
		sprintf(gpioName,"gpio%d",gpioKey[i]);
		ret = gpio_request(gpioKey[i],gpioName);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed request gpio%d error\n",6);
#endif
			return ret;
		}
	}
	for(i=0;i<GPIOCNT;i++)
	{
		ret = gpio_direction_input(gpioKey[i]);
		if(ret < 0) {
#ifdef DEBUG
			printk("Failed direction_output gpio%d error\n",6);
#endif
			return ret;
		}
	}
	return ret;
}
static long gpioKeyGet(void)
{
	long keyData=0;
	long temp;
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		temp = gpio_get_value(gpioKey[i]) << i;
		keyData |= temp;
	}
	return keyData;
}
static void gpioKeyFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
  		gpio_free(gpioKey[i]);
	}
}

static int minor0_open (struct inode *inode, struct file *filp)
{
    printk( "call minor0_open\n" );
    return 0;
}
static ssize_t minor0_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;    
	int ret;
	//  get_user(status,buf);
    ret=copy_from_user(&status,buf,count);
    gpioLedSet(status);

    return count;
}
static int minor0_release (struct inode *inode, struct file *filp)
{
    printk( "call minor0_release\n" );    
    return 0;
}

static int minor1_open (struct inode *inode, struct file *filp)
{
    printk( "call minor1_open\n" );
    return 0;
}
static ssize_t minor1_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;
	int ret;
    status = gpioKeyGet();
//  put_user(status,buf);
    ret=copy_to_user(buf,&status,count);

    return count;
}
static int minor1_release (struct inode *inode, struct file *filp)
{
    printk( "call minor1_release\n" );
    return 0;
}

static int minor2_open (struct inode *inode, struct file *filp)
{
    printk( "call minor1_open\n" );
    return 0;
}
static ssize_t minor2_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;
	int ret;
    status = gpioKeyGet();
//  put_user(status,buf);
    ret=copy_to_user(buf,&status,count);

    return count;
}
static ssize_t minor2_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    unsigned char status;    
	int ret;
	//  get_user(status,buf);
    ret=copy_from_user(&status,buf,count);
    gpioLedSet(status);

    return count;
}
static int minor2_release (struct inode *inode, struct file *filp)
{
    printk( "call minor1_release\n" );
    return 0;
}

struct file_operations minor0_fops =
{
    .owner    = THIS_MODULE,
    .write    = minor0_write,
    .open     = minor0_open,
    .release  = minor0_release,
};

struct file_operations minor1_fops =
{
    .owner    = THIS_MODULE,
    .read     = minor1_read,
    .open     = minor1_open,
    .release  = minor1_release,
};

struct file_operations minor2_fops =
{
    .owner    = THIS_MODULE,
    .read     = minor2_read,
	.write    = minor2_write,
    .open     = minor2_open,
    .release  = minor2_release,
};

static int minor_open (struct inode *inode, struct file *filp)
{
    printk( "call minor_open\n" );
    switch (MINOR(inode->i_rdev)) 
    {
    	case 0: filp->f_op = &minor0_fops; break;
    	case 1: filp->f_op = &minor1_fops; break;
    	case 2: filp->f_op = &minor2_fops; break;
    	default : return -ENXIO;
    }
    
    if (filp->f_op && filp->f_op->open)
        return filp->f_op->open(inode,filp);
        
    return 0;
}

struct file_operations minor_fops =
{
    .owner    = THIS_MODULE,
    .open     = minor_open,     
};

static int minor_init(void)
{
    int result;
    result = register_chrdev( MINOR_DEV_MAJOR, MINOR_DEV_NAME, &minor_fops);
    if (result < 0) return result;

	result = gpioLedInit();
    if(result < 0)
//      return result;
        return -EBUSY;
    result = gpioKeyInit();
    if(result < 0)
        return result;
    return 0;
}

static void minor_exit(void)
{
    unregister_chrdev( MINOR_DEV_MAJOR, MINOR_DEV_NAME );
	gpioLedSet(0);
    gpioLedFree();
    gpioKeyFree();

}

module_init(minor_init);
module_exit(minor_exit);

MODULE_AUTHOR("KCCI-AIOT KSH");
MODULE_DESCRIPTION("led key test module");
MODULE_LICENSE("Dual BSD/GPL");
