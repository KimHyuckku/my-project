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

#define LEDKEY_DEV_NAME "kerneltimer_ledkey_dev"
#define LEDKEY_DEV_MAJOR    232

#define OFF 0
#define ON 1
#define GPIOLEDCNT 8
#define GPIOKEYCNT 8

#define DEBUG 1

static int gpioLed[GPIOLEDCNT] = {6,7,8,9,10,11,12,13};
static int gpioKey[GPIOKEYCNT] = {16,17,18,19,20,21,22,23};

static int gpioLedInit(void);
static void gpioLedSet(long);
static void gpioLedFree(void);
static int gpioKeyInit(void);
static int gpioKeyGet(void);
static void gpioKeyFree(void);

static int timerVal = 100; // f=100HZ, T=1/100= 10 ms, 100*10 ms = 1Sec
module_param(timerVal, int , 0);
static int ledVal = 0;
module_param(ledVal, int , 0);
struct timer_list timerLed;

void kerneltimer_func(struct timer_list *t );
void kerneltimer_registertimer(unsigned long timeover)
{
	timer_setup(&timerLed, kerneltimer_func, 0);
	timerLed.expires = get_jiffies_64() + timeover;
	add_timer( &timerLed);
}
void kerneltimer_func(struct timer_list *t )
{
#if DEBUG
	printk("ledVal : %#04x\n", (unsigned int)(ledVal));
#endif
	gpioLedSet(ledVal);
	ledVal = ~ledVal & 0xff;
	mod_timer(t, get_jiffies_64() + timerVal);
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
static int  gpioKeyGet(void)
{
    int i;
    int ret;
    int keyData=0;
    for(i=0;i<GPIOKEYCNT;i++)
    {
//      ret=gpio_get_value(gpioKey[i]) << i;
//      keyData |= ret;
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
static int ledkey_open(struct inode *inode, struct file *filp)
{
    int num = MINOR(inode->i_rdev);
    printk("ledkey open-> minor : %d\n", num);
    num = MAJOR(inode->i_rdev);
    printk("ledkey open-> minor : %d\n", num);
    try_module_get(THIS_MODULE);
    return 0;
}

static loff_t ledkey_llseek(struct file *filp, loff_t off, int whence)
{
    printk("ledkey llseek -> off : %08X, whence : %08X\n", (unsigned int)off, whence);
    return 0x23;
}

static ssize_t ledkey_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    char kbuff;
    printk("ledkey read -> buf : %08X, count : %08X \n", (unsigned int)buf, count);
	kbuff = (char)gpioKeyGet();
    put_user(kbuff,buf);
//  result = copy_to_user(buf, &buff, count);
    return count;
}

static ssize_t ledkey_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
//  int i;
    char kbuff;
/*  char kbuff[10];
    for(i=0; i < count; i++)
        get_user(kbuff[i], buf++);
*/
    printk("ledkey write -> buf : %08X, count : %08X \n", (unsigned int)buf, count);
    get_user(kbuff,buf);
//  copy_from_user(&kbuff,buf,count);
    gpioLedSet(kbuff);
	ledVal = kbuff;
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
//  .owner  = THIS_MODULE,
    .llseek = ledkey_llseek,
    .read   = ledkey_read,
    .write  = ledkey_write,
    .unlocked_ioctl = ledkey_ioctl,
    .open   = ledkey_open,
    .release= ledkey_release,
};
int kerneltimer_init(void)
{
    int result;
#if DEBUG
    printk("timerVal : %d, sec : %d\n", timerVal, timerVal/HZ);
#endif
    result = gpioLedInit();
    if(result < 0) return result;
    result = gpioKeyInit();
    if(result < 0) return result;
    result = register_chrdev(LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME, &ledkey_fops);
    if(result < 0) return result;

    kerneltimer_registertimer(timerVal);
    return 0;
}
void kerneltimer_exit(void)
{
    if(timer_pending(&timerLed))
        del_timer(&timerLed);
    unregister_chrdev(LEDKEY_DEV_MAJOR, LEDKEY_DEV_NAME);
    gpioLedFree();
    gpioKeyFree();
}

module_init(kerneltimer_init);
module_exit(kerneltimer_exit);

MODULE_AUTHOR("KCCI-AIOT KHK");
MODULE_DESCRIPTION("led key test module");
MODULE_LICENSE("Dual BSD/GPL");

