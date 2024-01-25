#include "led.h"	// < >
#include "button.h"

#define LED_ALL_ON 0
#define LED_ALL_OFF 1
#define FLOWER_ON 2
#define FLOWER_OFF 3
#define LED_KEEPON_UP 4
#define LED_KEEPON_DOWN 5
#define LED_ON_UP 6
#define LED_ON_DOWN 7

void led_main();
void flower_on();
void flower_off();
void led_keepon_up();
void led_keepon_down();
void led_on_up();
void led_on_down();
void led_all_on();
void led_all_off();


void button0_toggle();

extern void HAL_SYSTICK_Handler(void);

extern volatile int t1ms_counter;	//volatile: for disable optimize
int func_index=0;
void led_main()
{
	while (1)
	{
		button0_toggle();
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

		void(*fp[]) ()=
		{
		led_on_down,
		led_all_on,
		led_all_off,
		flower_on,
		flower_off,
		led_keepon_up,
		led_keepon_down,
		led_on_up
		};


		fp[button0_count] ();


	}

//HAL_GPIO_ReadPin(GPIO, GPIO_PIN)== BUTTON_PRESS;
}

void flower_on()
{
	int i=0;

	while(1)
	{
		if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0x08>>i, 1);
			HAL_GPIO_WritePin(GPIOD, 0x10<<i, 1);
			i++;

			if(i == 5)				//원래는 i==4여야 하지만 4가되면 마지막 led는 켜보지도 못한 채 꺼지기 때문에 5를 삽입
			{
				i=0;
				HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			}
		}


	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		func_index=FLOWER_OFF;
		HAL_GPIO_WritePin(GPIOD, 0xff, 1);
		break;
	}
	}

//	for(int i=0; i<4; i++)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0x08>>i, 1);
//		HAL_GPIO_WritePin(GPIOD, 0x10<<i, 1);
//		HAL_Delay((i+1)*100);
//	}
}


void flower_off()
{
	int i=0;

	while(1)
	{
		if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0x01<<i, 0);
			HAL_GPIO_WritePin(GPIOD, 0x80>>i, 0);
			i++;

			if(i == 5)				//원래는 i==4여야 하지만 4가되면 마지막 led는 켜보지도 못한 채 꺼지기 때문에 5를 삽입
			{
				i=0;
				HAL_GPIO_WritePin(GPIOD, 0xff, 1);
			}
		}


	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		func_index=FLOWER_OFF;
		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
		break;
	}
	}

//	for(int i=0; i<4; i++)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0x01<<i, 0);
//		HAL_GPIO_WritePin(GPIOD, 0x80>>i, 0);
//		HAL_Delay(400-i*100);
//	}
//	HAL_Delay(50);
}


void led_keepon_up()
{
	int i=0;

	while(1)
	{
		if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0x01<<i, 1);
			i++;

			if(i >= 9)				//원래는 i>=9여야 하지만 8이되면 마지막 led는 켜보지도 못한 채 꺼지기 때문에 9를 삽입
			{
				i=0;
				HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			}
		}

	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		func_index=LED_KEEPON_DOWN;
		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
		break;
	}
	}
//	for(int i=0; i<8; i++)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0x01<<i, 1);
//		HAL_Delay(200);
//	}
}

void led_keepon_down()
{
	int i=0;

	while(1)
	{
		if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0x80>>i, 1);
			i++;

			if(i >= 9)					//원래는 i>=9여야 하지만 8이되면 마지막 led는 켜보지도 못한 채 꺼지기 때문에 9를 삽입
			{
				i=0;
				HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			}
		}

	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		func_index=LED_ON_UP;
		HAL_GPIO_WritePin(GPIOD, 0xff, 0);
		break;
	}
	}
//	for(int i=0; i<8; i++)
//	{
//		HAL_GPIO_WritePin(GPIOD, 0x80>>i, 0);
//		HAL_Delay(200);
//	}
}

void led_on_up()
{

#if 1
	int i=0;

	while(1)
	{
		if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			HAL_GPIO_WritePin(GPIOD, 0x01<<i, 1);
			i++;

			if(i >= 8)
				i=0;
		}

	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		func_index=LED_ON_DOWN;
		break;
	}
	}

#else		//original
	for(int i=0; i<8; i++)
	{
		led_all_off();
		HAL_GPIO_WritePin(GPIOD, 0x01<<i, 1);
		HAL_Delay(200);
	}
#endif
}

void led_on_down()
{
#if 1

	int i=0;

	while(1)
	{
		if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);
			HAL_GPIO_WritePin(GPIOD, 0x80>>i, 1);
			i++;

			if(i >= 8)
				i=0;
		}

	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		func_index=LED_ALL_ON;
		break;
	}
	}

#else
	for(int i=0; i<8; i++)
	{
		led_all_off();
		HAL_GPIO_WritePin(GPIOD, 0x80>>i, 1);
		HAL_Delay(200);
	}
#endif
}

void led_all_on()
{
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
//            			GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, 1);
	if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 1);

			func_index=LED_ALL_OFF;
		}

}

void led_all_off()
{
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
//            			GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, 0);
	if(t1ms_counter >=200)
		{
			t1ms_counter=0;
			HAL_GPIO_WritePin(GPIOD, 0xff, 0);

			func_index=FLOWER_ON;
		}
}


