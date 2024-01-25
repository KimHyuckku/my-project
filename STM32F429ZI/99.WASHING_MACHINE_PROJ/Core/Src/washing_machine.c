#include "main.h"
#include "button.h"
#include "fnd4digit.h"
#include "DHT11.h"
#include "i2c_lcd.h"

extern TIM_HandleTypeDef htim4;

extern void lcd_string(uint8_t *str);
extern void move_cursor(uint8_t row, uint8_t column);
extern void make_trigger();
extern void FND4digit_off(void);
extern void fnd4digit_timer(unsigned int set_time);
extern void fnd4digit_timer2(unsigned int set_time);
extern void buzzer_school();
extern void buzzer_birthday();

extern uint8_t lcd_display_mode_flag;
extern uint8_t button1_mode_flag;
extern uint8_t btn3_act_index;

extern volatile int t1ms_counter;
extern volatile int distance;
extern volatile int ic_cpt_finish_flag;
extern volatile int distance;

volatile int washing_timer=10;
volatile int drying_timer=10;
uint16_t  washing_speed=60;
uint16_t  drying_speed=60;

void wm_menu(void);
void wm_washing(void);
void wm_drying(void);
void wm_water(void);
void wm_acting(void);




void wm_menu(void)
{
	if(lcd_display_mode_flag==0)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, 0);

		if(button1_mode_flag==1)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, 1);
			wm_acting();
		}

	}
	if(lcd_display_mode_flag==1)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, 0);

		if(button1_mode_flag==1)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, 1);
			wm_washing();
		}
	}
	if(lcd_display_mode_flag==2)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, 0);

		if(button1_mode_flag==1)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, 1);
			wm_drying();
		}
	}
	if(lcd_display_mode_flag==3)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, 0);

		if(button1_mode_flag==1)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, 1);
			wm_water();
		}
	}
}

void wm_washing(void)
{
	char lcd_buff[20];

	if(get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)	// 시간 추가
	{
		washing_timer += 10;

		if(washing_timer > 120) washing_timer = 0;

		sprintf(lcd_buff, "TIME: %03d", washing_timer);	// 바뀐 시간 표기
		move_cursor(0, 0);
		lcd_string(lcd_buff);
	}

	if(get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)	// 시간 추가
	{
//		washing_speed = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
		washing_speed += 10;

		if(washing_speed > 120) washing_speed = 60;

		sprintf(lcd_buff, "SPEED: %03d", washing_speed);	// 바뀐 시간 표기
		move_cursor(1, 0);
		lcd_string(lcd_buff);
	}

}
void wm_drying(void)
{
	char lcd_buff[20];

	if(get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)	// 시간 추가
	{
		drying_timer += 10;

		if(drying_timer > 60) drying_timer = 0;

		sprintf(lcd_buff, "TIME: %03d", drying_timer);	// 바뀐 시간 표기
		move_cursor(0, 0);
		lcd_string(lcd_buff);
	}

	if(get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)	// 시간 추가
	{
//		drying_speed = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
		drying_speed += 10;

		if(drying_speed > 120) drying_speed = 60;

		sprintf(lcd_buff, "SPEED: %03d", drying_speed);	// 바뀐 시간 표기
		move_cursor(1, 0);
		lcd_string(lcd_buff);
	}

}
void wm_water(void)
{
	char lcd_buff[20];
	int dis;
	uint8_t i_RH, d_RH, i_Tmp, d_Tmp;

	if(get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)	// 물높이
	{
		make_trigger();
		if(ic_cpt_finish_flag)	// 초음파 측정이 완료되엇으면 if(ic_cpt_finish_flag >= 1)
		{
			ic_cpt_finish_flag=0;
			dis=distance;
			dis=dis*0.034/2;

			sprintf(lcd_buff, "Dep: %03d cm", dis);
			move_cursor(0, 0);
			lcd_string(lcd_buff);
			if(dis < 5)
			{
				buzzer_birthday();
			}
		}
	}

	if(get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)	// 시간 추가
	{
		DHT11_trriger();
		DHT11_DataLine_Input();
		DHT11_dumi_read();

		i_RH = DHT11_rx_Data();
		d_RH = DHT11_rx_Data();
		i_Tmp = DHT11_rx_Data();
		d_Tmp = DHT11_rx_Data();

		DHT11_DataLine_Output();
		HAL_GPIO_WritePin(DHT11_PORT, DHT11_DATA_RIN, GPIO_PIN_SET);
		sprintf(lcd_buff, "Tmp:%d Wet:%d", (int)i_Tmp, (int)i_RH);
		move_cursor(1, 0);
		lcd_string(lcd_buff);
	}
}
void wm_acting(void)
{
	char lcd_buff[20];
	int t1s_counter;

	if(btn3_act_index == 1)
	{
		btn3_act_index=0;
		t1ms_counter=0;

		i2c_lcd_init();
		sprintf(lcd_buff, "Washing Start");
		move_cursor(0, 0);
		lcd_string(lcd_buff);
	}
	t1s_counter = t1ms_counter/1000;

	if(t1s_counter >= 0 && t1s_counter < washing_timer+1)
	{
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, washing_speed);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
		fnd4digit_timer(washing_timer);
	}

	if(t1ms_counter == (washing_timer+1)*1000)
	{
		FND4digit_off();
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);

		i2c_lcd_init();
		sprintf(lcd_buff, "Washing End");
		move_cursor(0, 0);
		lcd_string(lcd_buff);
		sprintf(lcd_buff, "Drying Ready");
		move_cursor(1, 0);
		lcd_string(lcd_buff);
	}

	if(t1ms_counter == (washing_timer+10)*1000)
	{
		i2c_lcd_init();
		sprintf(lcd_buff, "Drying Start");
		move_cursor(0, 0);
		lcd_string(lcd_buff);
	}

	if(t1s_counter > washing_timer+10 && t1s_counter < washing_timer+12+drying_timer)
	{
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, drying_speed);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
		fnd4digit_timer2(drying_timer);
	}

	if(t1ms_counter == (washing_timer+12+drying_timer)*1000 )
	{
		FND4digit_off();
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);

		i2c_lcd_init();
		sprintf(lcd_buff, "Drying End");
		move_cursor(0, 0);
		lcd_string(lcd_buff);
		buzzer_school();
	}
}
