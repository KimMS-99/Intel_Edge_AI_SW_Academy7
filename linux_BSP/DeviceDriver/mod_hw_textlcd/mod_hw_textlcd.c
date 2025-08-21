#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/delay.h>
#include <linux/gpio.h>
#include <asm/gpio.h>

#include <linux/debugfs.h>
#include <linux/uaccess.h>

#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))
#define MAX_DATA_LEN 16
//echo "string 0" > /sys/kernel/debug/textlcd_line_0
//echo "string 1" > /sys/kernel/debug/textlcd_line_1
int textlcd[] = {
    /* control */
    IMX_GPIO_NR(2, 8),	//RS, 0:command, 1:data
    IMX_GPIO_NR(2, 9),	//RW, 0:write, 1:read (default only write!)
    IMX_GPIO_NR(2, 10),	//EN, command plus enable
    /* data */
    IMX_GPIO_NR(5, 5),
    IMX_GPIO_NR(5, 6),
    IMX_GPIO_NR(5, 7),
    IMX_GPIO_NR(5, 8),
    IMX_GPIO_NR(5, 9),
    IMX_GPIO_NR(5, 10),
    IMX_GPIO_NR(5, 11),
    IMX_GPIO_NR(5, 12),
};

#define textlcd_rs textlcd[0]
#define textlcd_rw textlcd[1]
#define textlcd_en textlcd[2]
#define textlcd_data (textlcd + 3)

static void _set_command_data(u_int8_t command_data, int flags /*0:cmd, 1:data*/)
{
	int i;

	gpio_set_value(textlcd_rs, flags); //command
	gpio_set_value(textlcd_en,0);
	ndelay(40);
	gpio_set_value(textlcd_en,1);
	ndelay(80);

	for(i = 0; i < 8; ++i){
		gpio_set_value(textlcd_data[i], (command_data >> i) & 0x01);
	}

	ndelay(230);
	gpio_set_value(textlcd_en, 0);

	udelay(50); /* new setting */
}

static inline void _set_function(bool line, bool dot)
{
	u_int8_t cmd = 0x30;

	cmd = (line) ? (cmd | 0x08) : cmd; //1: 2 lines, 0: 1 line
	cmd = (dot) ? (cmd | 0x04) : cmd; //1: 5x10 dots, 0: 5x7 dots

	_set_command_data(cmd, 0);
}

static inline void _set_entry_mode(bool increment, bool accompanies_shift)
{
	u_int8_t cmd = 0x40;

	cmd = increment ? (cmd | 0x02) : cmd;
	cmd = accompanies_shift ? (cmd | 0x01) : cmd;

	_set_command_data(cmd, 0);
}

/////////////////////////////////////////////////////////////////////////
void textlcd_set_display(bool display, bool cursor, bool blink){
	u_int8_t cmd = 0x08;

	cmd = (display) ? (cmd | 0x04) : cmd;
	cmd = (cursor) ? (cmd | 0x02) : cmd;
	cmd = (blink) ? (cmd | 0x01) : cmd;

	_set_command_data(cmd, 0);
}

EXPORT_SYMBOL_GPL(textlcd_set_display);

void textlcd_shift_cursor(bool left){
	_set_command_data(left ? 0x10 : 0x14, 0);
}

EXPORT_SYMBOL_GPL(textlcd_shift_cursor);

void textlcd_set_pos(int row, int column){
	u_int8_t cmd = 0x80;

	cmd = (row == 0) ? (cmd | column) : (cmd | 0x40 | column);

	_set_command_data(cmd, 0);
}

EXPORT_SYMBOL_GPL(textlcd_set_pos);

void textlcd_set_home(void){
	_set_command_data(0x02, 0);
}

EXPORT_SYMBOL_GPL(textlcd_set_home);

void textlcd_clear(void){
	_set_command_data(0x01, 0);
}

EXPORT_SYMBOL_GPL(textlcd_clear);

void textlcd_write(const char * p, int len){
	int i;

	printk("#### %s, string = %s\n", __FUNCTION__, p);

	len = (len < MAX_DATA_LEN) ? len : MAX_DATA_LEN;

	for(i = 0; i < len; ++i){
		_set_command_data(p[i], 1);
	}
}

EXPORT_SYMBOL_GPL(textlcd_write);

static inline void _textlcd_init(void)
{
	mdelay(30);
	_set_function(true, true); //2 Lines, 5 x 10 Dots
	udelay(40);
	textlcd_set_display(true, false, false);
	udelay(40);
	textlcd_clear();
	mdelay(2);
	_set_entry_mode(true, true);
}


/////////////////////////////////////////////////////////////////////////
struct dentry * dentry_textlcd_line[2];
char textlcd_line_buf[2][MAX_DATA_LEN];
char * file_name[] = {
	"textlcd_line_0",
	"textlcd_line_1",
};

static ssize_t textlcd_line_0_read(struct file *file, char *buf, size_t count, loff_t *pos)
{
	return simple_read_from_buffer(buf, count, pos, textlcd_line_buf[0], MAX_DATA_LEN);
}

static ssize_t textlcd_line_0_write(struct file *file, const char *buf, size_t count, loff_t *pos)
{
	int ret;

	count = (count > MAX_DATA_LEN) ? MAX_DATA_LEN : count;

	ret = copy_from_user(textlcd_line_buf[0], buf, count);
	if(ret){
    	return -EFAULT;
    }

	textlcd_set_pos(0, 0);
	textlcd_write(textlcd_line_buf[0], count - 1);

	return count;
}

static ssize_t textlcd_line_1_read(struct file *file, char *buf, size_t count, loff_t *pos)
{
	return simple_read_from_buffer(buf, count, pos, textlcd_line_buf[1], MAX_DATA_LEN);
}

static ssize_t textlcd_line_1_write(struct file *file, const char *buf, size_t count, loff_t *pos)
{
	int ret;

	count = (count > MAX_DATA_LEN) ? MAX_DATA_LEN : count;

	ret = copy_from_user(textlcd_line_buf[1], buf, count);
	if(ret){
    	return -EFAULT;
    }

	textlcd_set_pos(1, 0);
	textlcd_write(textlcd_line_buf[1], count - 1);

	return count;
}


static const struct file_operations textlcd_fops[] = {
	{
		.read = textlcd_line_0_read,
		.write = textlcd_line_0_write,
	},

	{
		.read = textlcd_line_1_read,
		.write = textlcd_line_1_write,
	}
};
/////////////////////////////////////////////////////////////////////////

static int mod_hw_textlcd_init(void)
{
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(textlcd); i++) {
		ret = gpio_request(textlcd[i], "gpio sw");
		if(ret){
			printk("#### FAILED Request gpio %d. error : %d \n", textlcd[i], ret);
		} else {
			gpio_direction_output(textlcd[i], 0);
		}
	}

	if(ret){
		return ret;
	}
	
	_textlcd_init();

	for(i = 0; i < ARRAY_SIZE(dentry_textlcd_line); ++i){
		dentry_textlcd_line[i] = debugfs_create_file(file_name[i], 0644, NULL, NULL, &textlcd_fops[i]);
		if(dentry_textlcd_line[i] == NULL){
			printk("#### FAILED debugfs_create_file\n");
			return -EEXIST;
		}
	}

	return 0;
}

static void mod_hw_textlcd_exit(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(textlcd); i++) {
		gpio_free(textlcd[i]);
	}

	for(i = 0; i < ARRAY_SIZE(dentry_textlcd_line); ++i){
		debugfs_remove(dentry_textlcd_line[i]);
	}
}

module_init(mod_hw_textlcd_init);
module_exit(mod_hw_textlcd_exit);

MODULE_AUTHOR("PlanX Studio");
MODULE_DESCRIPTION("mod_hw_textlcd");
MODULE_LICENSE("Dual BSD/GPL");
