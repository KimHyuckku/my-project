#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define OFF 0
#define ON 1
#define GPIOLEDCNT 8
int gpioLed[GPIOLEDCNT] = {6,7,8,9,10,11,12,13};

int gpioLedInit(void);
void gpioLedSet(long);
void gpioLedFree(void);

static int hello_init(void)
{
	int ret;
    ret=gpioLedInit();
    if(ret < 0)
        return ret;
    gpioLedSet(0xff);
	printk("Hello, world \n");
	return 0;
}

static void hello_exit(void)
{
	gpioLedSet(0x00);
	gpioLedFree();
	printk("Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");






int gpioLedInit(void)
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
void gpioLedSet(long val)
{
    int i;
    for(i=0;i<GPIOLEDCNT;i++)
    {
        gpio_set_value(gpioLed[i],(val>>i) & 0x1);
    }
}
void gpioLedFree(void)
{
    int i;
    for(i=0;i<GPIOLEDCNT;i++)
    {
        gpio_free(gpioLed[i]);
    }
}

