#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#define GPIOCNT 8
#define LED_OFF 0
#define LED_ON 1
// int gpioLed[GPIOCNT] = {6,7,8,9,10,11,12,13};
unsigned int gpioLed[GPIOCNT] = {518, 519, 520, 521, 522, 523, 524, 525};
int gpioLedInit(void);
void gpioLedSet(long val);
void gpioLedFree(void);
unsigned int gpioKey[GPIOCNT] = {528, 529, 530, 531, 532, 533, 534, 535};
int gpioKeyInit(void);
long gpioKeyGet(void);
void gpioKeyFree(void);

int gpioLedInit(void)
{
	int i;
	int ret = 0;
	char gpioName[10];
	for (i = 0; i < GPIOCNT; i++)
	{
		sprintf(gpioName, "led%d", i);
		ret = gpio_request(gpioLed[i], gpioName);
		if (ret < 0)
		{
			printk("Failed request gpio%d error\n", gpioLed[i]);
			return ret;
		}
	}
	for (i = 0; i < GPIOCNT; i++)
	{
		ret = gpio_direction_output(gpioLed[i], LED_OFF);
		if (ret < 0)
		{
			printk("Failed direction_output gpio%d error\n", gpioLed[i]);
			return ret;
		}
	}
	return ret;
}
void gpioLedSet(long val)
{
	int i;
	for (i = 0; i < GPIOCNT; i++)
	{
		gpio_set_value(gpioLed[i], ((val >> i) & 0x01));
	}
}
void gpioLedFree(void)
{
	int i;
	for (i = 0; i < GPIOCNT; i++)
	{
		gpio_free(gpioLed[i]);
	}
}

int gpioKeyInit(void)
{
	int i;
	int ret = 0;
	char gpioName[10];
	for (i = 0; i < GPIOCNT; i++)
	{
		sprintf(gpioName, "key%d", i);
		ret = gpio_request(gpioKey[i], gpioName);
		if (ret < 0)
		{
			printk("Failed request gpio%d error\n", gpioKey[i]);
			return ret;
		}
	}
	for (i = 0; i < GPIOCNT; i++)
	{
		ret = gpio_direction_input(gpioKey[i]);
		if (ret < 0)
		{
			printk("Failed direction_output gpio%d error\n", gpioKey[i]);
			return ret;
		}
	}
	return ret;
}
long gpioKeyGet(void)
{
	int i;
	int key = 0;
	for (i = 0; i < GPIOCNT; i++)
	{
		key |= gpio_get_value(gpioKey[i]) << i;
	}
	return key;
}
void gpioKeyFree(void)
{
	int i;
	for (i = 0; i < GPIOCNT; i++)
	{
		gpio_free(gpioKey[i]);
	}
}
static int hello_init(void)
{
	printk(KERN_INFO "Hello, ledkey \n");
	int ret = 0;
	ret = gpioLedInit(); // gpio_request(), gpiot_direction_output();
	if (ret < 0)
		return ret;

	ret = gpioKeyInit();
	if (ret < 0)
		return ret;

	ret = gpioKeyGet(); // val : 0x00 ~ 0xff
	gpioLedSet(ret);	// gpio_set_value();
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_INFO "Goodbye, ledkey\n");

	int ret = gpioKeyGet(); // val : 0x00 ~ 0xff
	gpioLedSet(ret);		// gpio_set_value();

	gpioLedFree(); // gpio_free();
	gpioKeyFree(); // gpio_free();
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("KCCI-AIOT");
MODULE_DESCRIPTION("test moudle");
MODULE_LICENSE("Dual BSD/GPL");
