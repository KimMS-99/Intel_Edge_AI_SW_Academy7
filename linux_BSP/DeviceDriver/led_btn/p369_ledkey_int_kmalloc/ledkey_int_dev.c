#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>          
#include <linux/errno.h>       
#include <linux/types.h>       
#include <linux/fcntl.h>       

#include <linux/gpio.h>
#include <linux/moduleparam.h>

#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/mutex.h>

#define DEBUG 1

#define   LEDKEY_DEV_NAME            "ledkey"
#define   LEDKEY_DEV_MAJOR            230      

#define OFF 0
#define ON 1
#define GPIOCNT 8

//static int keyNum = 0;
//static int irqKey[GPIOCNT];
typedef struct {
	int keyNum;
	int irqKey[GPIOCNT];
} keyDataStruct;

static int gpioLedInit(void);
static void gpioLedSet(long val);
static void gpioLedFree(void);
static int gpioKeyInit(void);
//static int gpioKeyGet(void);
static void gpioKeyFree(void);
static int irqKeyInit(keyDataStruct * pkeyData);
static void irqKeyFree(keyDataStruct * pKeyData);

static int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
static int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};

static int onevalue = 1;
static char * twostring = NULL;
static int openFlag = 0;


static DEFINE_MUTEX(keyMutex);

module_param(onevalue, int ,0);
module_param(twostring,charp,0);

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

static int ledkey_open (struct inode *inode, struct file *filp)
{

	int result=0;
	keyDataStruct * pKeyData;
	char * irqName[GPIOCNT] = {"irqKey0","irqKey1","irqKey2","irqKey3","irqKey4","irqKey5","irqKey6","irqKey7",};
#if DEBUG
    int num0 = MAJOR(inode->i_rdev); 
    int num1 = MINOR(inode->i_rdev); 
    printk( "call open -> major : %d\n", num0 );
    printk( "call open -> minor : %d\n", num1 );
#endif

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

	if(openFlag)
		return -EBUSY;
	else
		openFlag = 1;

	if(!try_module_get(THIS_MODULE))
		return -ENODEV;

	filp->private_data = pKeyData;
    return 0;
}

static loff_t ledkey_llseek (struct file *filp, loff_t off, int whence )
{
#if DEBUG
    printk( "call llseek -> off : %08X, whenec : %08X\n", (unsigned int)off, whence );
#endif
    return 0x23;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuf=0;
	keyDataStruct * pKeyData = (keyDataStruct *)filp->private_data;

//	kbuf=gpioKeyGet();
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

#if DEBUG
    printk( "call read -> key : %#04x\n", kbuf );
#endif

    return count;
}

static ssize_t ledkey_write (struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	char kbuf;

#if 1
	get_user(kbuf,buf);
#else
	int ret;
	ret=copy_from_user(&kbuf,buf,sizeof(kbuf));
#endif

#if DEBUG
    printk( "call write -> led : %#04x\n", kbuf );
#endif

	gpioLedSet(kbuf);
	return count;
}

static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	int err = 0;
    return err;
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

#if 0
static int	gpioKeyGet(void)
{
	int i;
	int ret;
	int keyData=0;
	for(i=0;i<GPIOCNT;i++)
	{
//		ret=gpio_get_value(gpioKey[i]) << i;
//		keyData |= ret;
		ret=gpio_get_value(gpioKey[i]);
		keyData = keyData | ( ret << i );
	}
	return keyData;
}
#endif
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

	mutex_init(&keyMutex);

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
	mutex_destroy(&keyMutex);
}

module_init(ledkey_init);
module_exit(ledkey_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("kcci");
MODULE_DESCRIPTION("led key test module");
