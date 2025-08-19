#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define GPIOCNT 8
#define LED_OFF 0
#define LED_ON 1

unsigned int gpioLed[GPIOCNT] = {518,519,520,521,522,523,524,525};
int gpioLedInit(void);
void gpioLedSet(long val);
void gpioLedFree(void);

unsigned int gpioKey[GPIOCNT] = {528,529,530,531,532,533,534,535};
int gpioKeyInit(void);
int gpioKeyGet(void);
void gpioKeyFree(void);

static int led_init(void)
{
	printk(KERN_INFO "Hello, Led\n");
	int ret = gpioLedInit();
	if(ret < 0) return ret;
	ret = gpioKeyInit();
	if(ret < 0) return ret;
	int val;
    val = gpioKeyGet();     //val : 0x00 ~ 0xff
    gpioKeyFree();
//	gpioLedSet(val);
	gpioLedFree();
	return 0;
}

static void led_exit(void)
{
	printk(KERN_INFO "Goodbye, Led\n");
	int ret = gpioLedInit();
	int val;
	 ret = gpioKeyInit();
    val = gpioKeyGet();     //val : 0x00 ~ 0xff
    gpioKeyFree();
	gpioLedSet(val);
    gpioLedFree();
}

int gpioLedInit(void)
{
    int i;
    int ret=0 ;
    char gpioName[10];
    for(i=0;i<GPIOCNT;i++)
    {   
        sprintf(gpioName,"led%d",i);
        ret=gpio_request(gpioLed[i],gpioName);
        if(ret < 0)
        {
            printk("Failed request gpio%d error\n",gpioLed[i]);
            return ret;
        }
    }
    for(i=0;i<GPIOCNT;i++)
    {
        ret = gpio_direction_output(gpioLed[i],LED_OFF);
        if(ret < 0)
        {
            printk("Failed direction_output gpio%d error\n",gpioLed[i]);
            return ret;
        }
    }
    return ret;
}

void gpioLedSet(long val)
{
    int i;
    for(i=0;i<GPIOCNT;i++)
    {
        gpio_set_value(gpioLed[i],((val >> i) & 0x01));
    }
}

int gpioKeyInit(void)
{
	int ret;
	char gpioName[10];
	for (int i = 0; i < GPIOCNT; i++) {
		sprintf(gpioName, "key%d", i);
		ret = gpio_request(gpioKey[i], gpioName);
		if (ret < 0) {
			printk("Failed request gpio%d error\n", gpioKey[i]);
			return -1;
		}
		ret = gpio_direction_input(gpioKey[i]);
		if (ret < 0) {
			printk("Failed direction_input gpio%d error\n", gpioKey[i]);
			return -2;
		}
	}
	return 0;
}

int gpioKeyGet(void)
{
	int val = 0;
	for (int i = 0; i < GPIOCNT; i++) {
		if (gpio_get_value(gpioKey[i]) == 1) {
			val |= (1 << i);
		}
	}
	gpioLedSet(val);
	return val;
}
void gpioKeyFree(void)
{
	int i;
	for(i=0;i<GPIOCNT;i++)
	{
		gpio_free(gpioKey[i]);
	}
}

module_init(led_init);
module_exit(led_exit);

MODULE_AUTHOR("KCCI-AIOT");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");


