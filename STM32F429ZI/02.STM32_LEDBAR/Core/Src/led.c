#include "led.h"	// < >

void led_main(void);
void led_keepon_up();
void led_keepon_down();
void led_on_up();
void led_on_down();
void led_all_on(void);
void led_all_off(void);

void flower_on();
void flower_off();

void led_main(void)
{
	while (1)
	{

		flower_on();

		flower_off();



//		//phase#4
//		//0->1->2->3->4->5->6->7
//		//앞전에 ON했던 LED는 그대로 유지
//		led_keepon_up();
//		led_all_off();
//		HAL_Delay(200);
//		//7->6->5->4->3->2->1->0
//		led_keepon_down();
//		led_all_off();
//		HAL_Delay(200);


//		//0->1->2->3->4->5->6->7
//		//해당되는 bit의 led만 ON
//		led_on_up();
//		HAL_Delay(200);
//		//7->6->5->4->3->2->1->0
//		led_on_down();

		//phase#2
//		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_All);
//		HAL_Delay(500);

		//phase#1
//		led_all_on();
//		HAL_Delay(3000);
//		led_all_off();
//		HAL_Delay(3000);
	}
}

void flower_on()
{
	for(int i=0; i<4; i++)
	{
		HAL_GPIO_WritePin(GPIOD, 0x08>>i, 1);
		HAL_GPIO_WritePin(GPIOD, 0x10<<i, 1);
		HAL_Delay((i+1)*100);
	}
}


void flower_off()
{
	for(int i=0; i<4; i++)
	{

		HAL_GPIO_WritePin(GPIOD, 0x01<<i, 0);
		HAL_GPIO_WritePin(GPIOD, 0x80>>i, 0);
		HAL_Delay(400-i*100);
	}
	HAL_Delay(50);
}


void led_keepon_up()
{
	for(int i=0; i<8; i++)
	{
		HAL_GPIO_WritePin(GPIOD, 0x01<<i, 1);
		HAL_Delay(200);
	}
}

void led_keepon_down()
{
	for(int i=0; i<8; i++)
	{
		HAL_GPIO_WritePin(GPIOD, 0x80>>i, 1);
		HAL_Delay(200);
	}
}

void led_on_up()
{

	for(int i=0; i<8; i++)
	{
		led_all_off();
		HAL_GPIO_WritePin(GPIOD, 0x01<<i, 1);
		HAL_Delay(200);
	}

}

void led_on_down()
{
	for(int i=0; i<8; i++)
	{
		led_all_off();
		HAL_GPIO_WritePin(GPIOD, 0x80>>i, 1);
		HAL_Delay(200);
	}

}

void led_all_on(void)
{

//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
//            			GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, 1);
	HAL_GPIO_WritePin(GPIOD, 0xff, 1);
}

void led_all_off(void)
{
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
//            			GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, 0);

	HAL_GPIO_WritePin(GPIOD, 0xff, 0);
}

