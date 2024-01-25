#include "led.h"	// < >
#include "button.h"

void led_button_demo();

void led_main(void);
void led_keepon_up();
void led_keepon_down();
void led_on_up();
void led_on_down();
void led_all_on(void);
void led_all_off(void);

void flower_on();
void flower_off();

void led_button_demo()
{
	static int button0_count=0;	//static으로 선언을 하면 전역 변수처럼 동작을 한다.
	static int button1_count=0;
	static int button2_count=0;
	static int button3_count=0;


	// 버튼을 한번 눌렀다 뗀 상태라면
	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		button0_count++;
		button0_count %= 2;
		if(button0_count)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
		}
	}
	if(get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
		{
			button1_count++;
			button1_count %= 2;
			if(button1_count)
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);
			}
		}
	if(get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)
		{
			button2_count++;
			button2_count %= 2;
			if(button2_count)
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			}
		}
	if(get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)
		{
			button3_count++;
			button3_count %= 2;
			if(button3_count)
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			}
		}
}



void button0_led_all_on_off_toggle()
{
	static int button0_count=0;	//static으로 선언을 하면 전역 변수처럼 동작을 한다.


	// 버튼을 한번 눌렀다 뗀 상태라면
	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		button0_count++;
		button0_count %= 2;
		if(button0_count)
		{
			led_all_on();
		}
		else
		{
			led_all_off();
		}
	}
}


	// 1: led_all_on();
	// 2: led_all_off();
	// 3: flower_on();
	// 4: flower_off();
	// 5: led_keepon_up
	// 6: led_keepon_down
	// 7: led_on_up
	// 8: led_on_down
void button0_toggle()
{
	static int button0_count=0;	//static으로 선언을 하면 전역 변수처럼 동작을 한다.

	// 버튼을 한번 눌렀다 뗀 상태라면
	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		button0_count++;
		button0_count %= 8;
		if(button0_count == 0)
		{
			led_on_down();
		}
		else if (button0_count == 1)
		{
			led_all_on();
		}
		else if (button0_count == 2)
			{
			led_all_off();
			}
		else if (button0_count == 3)
			{
			flower_on();
			}
		else if (button0_count == 4)
			{
			flower_off();
			}
		else if (button0_count == 5)
			{
			led_keepon_up();
			}
		else if (button0_count == 6)
			{
			led_keepon_down();
			}
		else
			{
			led_on_up();
			}
	}
}

void led_main(void)
{
	while (1)
	{
		button0_toggle();
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
		HAL_GPIO_WritePin(GPIOD, 0x80>>i, 0);
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

