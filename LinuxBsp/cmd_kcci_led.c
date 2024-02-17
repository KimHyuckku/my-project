#include <common.h>
#include <command.h>
#include <asm/io.h>

#define BCM2711_GPIO_GPFSEL0 0xFE200000
#define BCM2711_GPIO_GPFSEL1 0xFE200004
#define BCM2711_GPIO_GPFSEL2 0xFE200008
#define BCM2711_GPIO_GPSET0  0xFE20001C
#define BCM2711_GPIO_GPCLR0	 0xFE200028
#define BCM2711_GPIO_GPLEV0	 0xFE200034

#define GPIO6_9_SIG_OUTPUT	 0x09240000
#define GPIO10_13_SIG_OUTPUT 0x00012249

#define GPIO16_19_SIG_INPUT  0x00012249
#define GPIO20_23_SIG_INPUT  0x00000000

void led_init(void)
{
	unsigned long temp;
	temp = readl(BCM2711_GPIO_GPFSEL0);
 	temp = temp & 0x0003ffff;
	//temp = temp &~ 0xfffc0000;
	temp = temp | GPIO6_9_SIG_OUTPUT;
	writel(temp, BCM2711_GPIO_GPFSEL0);

	temp = readl(BCM2711_GPIO_GPFSEL1);	// GPIO 10~13 read
    temp = temp & 0x3ffff000;			// GPIO 10~13 Clear
    temp = temp | GPIO10_13_SIG_OUTPUT;
    writel(temp, BCM2711_GPIO_GPFSEL1);
//	writel(GPIO6_9_SIG_OUTPUT, BCM2711_GPIO_GPFSEL0);
//	writel(GPIO10_13_SIG_OUTPUT, BCM2711_GPIO_GPFSEL1);
}

void led_write(unsigned long led_data)
{
	writel(0x3fc0, BCM2711_GPIO_GPCLR0);	//led all off
	led_data = led_data << 6;
	writel(led_data, BCM2711_GPIO_GPSET0);
}

void key_init(void)
{
	unsigned long temp;
	temp = readl(BCM2711_GPIO_GPFSEL1);
	temp = temp & 0x0003ffff;			//GPIO 16~19 INPUT
	writel(temp, BCM2711_GPIO_GPFSEL1);

	temp = readl(BCM2711_GPIO_GPFSEL2);
    temp = temp & 0x3ffff000;			//GPIO 20~23 INPUT
 	writel(temp, BCM2711_GPIO_GPFSEL2);
}

void key_read(unsigned long* key_data)
{
	*key_data= (readl(BCM2711_GPIO_GPLEV0) >> 16) & 0x000000ff;
}

static int do_KCCI_LED(struct cmd_tbl *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned long led_data, key_data, key_data_old = 0;
	unsigned long i;

	if(argc !=2)
	{
		cmd_usage(cmdtp);
		return 1;
	}
	printf("*LED TEST START(KHK)\n");
	led_init();
	led_data = simple_strtoul(argv[1], NULL, 16);
	led_write(led_data);

	key_init();
	do {
		key_read(&key_data);
//		key_data = key_data & 0xFF;
		if(key_data != key_data_old)
		{
			if(key_data)
			{
				led_write(key_data);
				puts("0:1:2:3:4:5:6:7\n");
				for(i=0; i<8; i++)
				{
					if(key_data & (0x01 << i) )
						putc('O');
					else
						putc('X');
					if(i !=7)
						putc(':');
					else
						putc(' ');
				}
				putc('\n');
			}
			key_data_old = key_data;
			if(key_data == 0x80)
				break;
		}

  	  } while(1);

	printf("*LED TEST END(%s : %#04x)\n\n ", argv[0], (unsigned int)led_data);
	return 0;
}

U_BOOT_CMD(
		led,2,0,do_KCCI_LED,
		"led - kcci LED Test.",
		"number - Input argument is only one.(led [0x00~0xff])\n");

