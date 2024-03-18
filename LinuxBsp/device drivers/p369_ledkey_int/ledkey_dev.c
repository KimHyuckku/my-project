#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>

#define DEBUG 1
#define LEDKEY_DEV_NAME	"ledkey_dev"
#define LEDKEY_DEV_MAJOR	230

#define OFF 0
#define ON 1
#define GPIOLEDCNT 8
#define GPIOKEYCNT 8

static int gpioLed[GPIOLEDCNT] = {6,7,8,9,10,11,12,13};
static int gpioKey[GPIOKEYCNT] = {16,17,18,19,20,21,22,23};
static int key_irq[8] = {0};
static int keyNumber = 0;

static int gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);
static int gpioKeyIrqInit(void);
static void gpioKeyIrqFree(void);

irqreturn_t key_isr(int irq, void *data)
{
	int i;
	for(i=0; i<GPIOKEYCNT; i++)
	{
		if(irq == key_irq[i])
		{
			keyNumber = i+1;
			break;
		}
	}
#if DEBUG
	printk("key_isr() irq : %d, KeyNumber : %d\n", irq, keyNumber);
#endif
	return IRQ_HANDLED;
}

static int gpioLedInit(void)
{
	int i;
	int ret=0;
	char gpioName[10];
	for(i=0;i<GPIOLEDCNT;i++)
	{
		sprintf(gpioName,"led%d",i);
		ret = gpio_request(gpioLed[i],gpioName);
		if(ret < 0) {
			printk("Failed gpio_request() gpio%d error \n",i);
			return ret;
		}

		ret = gpio_direction_output(gpioLed[i],OFF);
		if(ret < 0) {
			printk("Failed gpio_direction_output() gpio%d error \n",i);
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
		gpio_set_value(gpioLed[i],(val>>i) & 0x1);
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
		sprintf(gpioName,"key%d",gpioKey[i]);
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
static int	gpioKeyGet(void)
{
	int i;
	int ret;
	int keyData=0;
	for(i=0;i<GPIOKEYCNT;i++)
	{
//		ret=gpio_get_value(gpioKey[i]) << i;
//		keyData |= ret;
		ret=gpio_get_value(gpioKey[i]);
		keyData = keyData | ( ret << i );
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
static int gpioKeyIrqInit(void)
{
	int i;
	for(i=0;i<GPIOKEYCNT;i++)
	{
		key_irq[i] = gpio_to_irq(gpioKey[i]);
		if(key_irq[i] < 0)
		{
			printk("tpioKeyIrq() Failed gpio %d\n", gpioKey[i]);
			return key_irq[i];
		}
	}
	return 0;
}
static void gpioKeyIrqFree(void)
{
	int i;
	for(i=0;i<GPIOKEYCNT;i++)
	{
		free_irq(key_irq[i],NULL);
	}
}
static int ledkey_open(struct inode *inode, struct file *filp)
{
	int num = MINOR(inode->i_rdev);
	printk("ledkey open-> minor : %d\n", num);
	num = MAJOR(inode->i_rdev);
    printk("ledkey open-> minor : %d\n", num);
	try_module_get(THIS_MODULE);
	return 0;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	char kbuff;
	printk("ledkey read -> buf : %08X, count : %08X \n", (unsigned int)buf, count);
	kbuff = (char)gpioKeyGet();
	put_user(kbuff,buf);
//	result = copy_to_user(buf, &buff, count);
	return count;
}

static ssize_t ledkey_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
//	int i;
	char kbuff;
/*	char kbuff[10];
	for(i=0; i < count; i++)
		get_user(kbuff[i], buf++);
*/
	printk("ledkey write -> buf : %08X, count : %08X \n", (unsigned int)buf, count);
	get_user(kbuff,buf);
//	copy_from_user(&kbuff,buf,count);
	gpioLedSet(kbuff);
	return count;
}

static long ledkey_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("ledkey ioctl -> cmd : %08X, arg : %08X\n", cmd, (unsigned int)arg);
	return 0x53;
}

static int ledkey_release(struct inode *inode, struct file *filp)
{
	printk("ledkey release \n"); 
	module_put(THIS_MODULE);
	return 0;
}

struct file_operations ledkey_fops=
{
//	.owner	= THIS_MODULE,
	.open	= ledkey_open,
	.read	= ledkey_read,
	.write	= ledkey_write,
	.unlocked_ioctl	= ledkey_ioctl,
	.release= ledkey_release,
};

static int ledkey_init(void)
{
	int result, i;
	char * irqName[8] = { "IrqKey0", "IrqKey1", "IrqKey2", "IrqKey3", "IrqKey4", "IrqKey5", "IrqKey6", "IrqKey7"};

	printk("ledkey ledkey_init\n");
	result=gpioLedInit();
    if(result < 0) return result;
	result=gpioKeyInit();
    if(result < 0) return result;

	result = gpioKeyIrqInit();
	if(result < 0) return result;
	for(i=0; i<GPIOKEYCNT; i++)
	{
		result = request_irq(key_irq[i], key_isr, IRQF_TRIGGER_RISING, irqName[i], NULL);
		if(result < 0)
		{
			printk("request_irq() failed irq %d\n", key_irq[i]);
			return result;
		}
	}

	result = register_chrdev(LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
	if(result < 0) return result;
	return 0;
}

static void ledkey_exit(void)
{
	printk("ledkey ledkey_exit \n");
	unregister_chrdev(LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME);
	gpioLedFree();
	gpioKeyIrqFree();
    gpioKeyFree();
}

module_init(ledkey_init);
module_exit(ledkey_exit);

MODULE_LICENSE("Dual BSD/GPL");
