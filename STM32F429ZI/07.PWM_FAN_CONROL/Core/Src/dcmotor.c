#include <stdio.h>
#include "button.h"
#include "dcmotor.h"

extern TIM_HandleTypeDef htim4;
extern volatile int TIM10_10ms_counter;

extern void lcd_string(uint8_t *str);
extern void move_cursor(uint8_t row, uint8_t column);

void dcmotor_pwm_control(void);
// BUTTON0: start/stop : LED1 (toggle)
// BUTTON1: SPEED-UP   : LED2 (toggle)
// BUTTON2: SPEED-DOWN : LED3 (toggle)
uint8_t pwm_start_flag=0;	// dcmotor start/stop indicate flag
uint16_t  CCR_UP_Value=0;	// PWM UP control
uint16_t  CCR_DOWN_Value=0;	// PWM DOWN control
uint8_t forward_backword_dcmotor=0;	// PWM front/back conrtol
uint8_t led_index=2;		// manual모드에서 이것을 통해 선풍기 세기와 LED 불빛을 연동함
volatile int timer_set=500;	// Auto에서 모터를 켰을 때 기본 저장된 시간

void dcmotor_pwm_control(void)		// Default는 Auto모드
{
	char lcd_buff[20];

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)	// 버튼 0번 누르면 ON-OFF
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);		//정회전
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);

		if(pwm_start_flag==0)				// pwm_start_flag가 0이면 팬을 돌리기 시작
		{
			TIM10_10ms_counter=0;
			pwm_start_flag=1;
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

			sprintf(lcd_buff, "TIME: %d", timer_set);
			move_cursor(0, 0);
			lcd_string(lcd_buff);
		}
		else if(pwm_start_flag==2)
		{
			pwm_start_flag=1;
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
		}
		else
		{
			pwm_start_flag=0;
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 0);

			sprintf(lcd_buff, "left:           ");	// LCD에 남아있는 끝자리0을 지우기 위한 식
			move_cursor(1, 0);
			lcd_string(lcd_buff);
		}
	}
	// PLUS time : button1
	if(get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)	// 시간 추가
	{
		timer_set += 100;

		sprintf(lcd_buff, "TIME: %d", timer_set);	// 바뀐 시간 표기
		move_cursor(0, 0);
		lcd_string(lcd_buff);
	}
	// MINUS time : button2
	if(get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)	// 시간 빼기
	{
		timer_set -= 100;

		sprintf(lcd_buff, "TIME:           ");		// LCD에 남아있는 끝자리0을 지우기 위한 식
		move_cursor(0, 0);
		lcd_string(lcd_buff);

		sprintf(lcd_buff, "TIME: %d", timer_set);	// 바뀐 시간 표기
		move_cursor(0, 0);
		lcd_string(lcd_buff);
	}
	// turn-back : button3
	if(get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 0);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
		pwm_start_flag=2;
	}

	// 지정된 시간이 지나면 선풍기가 꺼짐
	if(TIM10_10ms_counter >= timer_set)
	{
		pwm_start_flag=0;
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
	}

	if(TIM10_10ms_counter < timer_set)
	{
		sprintf(lcd_buff, "left: %d", timer_set-TIM10_10ms_counter);
		move_cursor(1, 0);
		lcd_string(lcd_buff);

		if(TIM10_10ms_counter%100 == 0)		// LCD에 남아있는 끝자리0을 지우기 위한 식
		{
			sprintf(lcd_buff, "left:           ");
			move_cursor(1, 0);
			lcd_string(lcd_buff);
		}
	}




	if(get_button(BUTTON4_GPIO_Port, BUTTON4_Pin, 4) == BUTTON_PRESS)	// Manual Mode
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);	//stm32 내장led

		while(1)
		{
			// start/stop : button0
			if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
			{
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);

				if(pwm_start_flag==0)				// pwm_start_flag은 모터가 돌아가거나, 꺼지거나, 정회전으로 돌아오는 것을
				{									// 확인하는 역할을 한다.
					pwm_start_flag=1;
					HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
					HAL_GPIO_WritePin(GPIOD, 0x01, 1);		//LED는 2개를 기본값으로 시작한다.
					HAL_GPIO_WritePin(GPIOD, 0x02, 1);
				}
				else if(pwm_start_flag==2)			// 다시 정회전으로 돌아옴
				{
					pwm_start_flag=1;
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
				}
				else								// 모터가 꺼짐
				{
					pwm_start_flag=0;
					HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
					HAL_GPIO_WritePin(GPIOD, 0xff, 0);
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 0);
					led_index=2;
				}
			}
			// speed-up : button1
			if(get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)	//모터 속도 업
			{
				CCR_UP_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
				CCR_UP_Value += 10;

				if(CCR_UP_Value > 100)
				{
					CCR_UP_Value = 100;
					led_index--;
				}
				HAL_GPIO_WritePin(GPIOD, 0x01<<led_index, 1);
				led_index++;
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, CCR_UP_Value);
			}
			// speed-down : button2
			if(get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)
			{
				CCR_DOWN_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
				CCR_DOWN_Value -= 10;

				if(CCR_DOWN_Value < 60)
				{
					CCR_DOWN_Value = 60;
					led_index++;
				}
				led_index--;
				HAL_GPIO_WritePin(GPIOD, 0x01<<led_index, 0);

				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, CCR_DOWN_Value);
			}
			// turn-back : button3
			if(get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)
			{
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 0);
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
				pwm_start_flag=2;
			}

			if(pwm_start_flag==1)		//팬이 정회전 하고 있을 때 LED13이 50ms로 깜빡임
			{
				if(TIM10_10ms_counter >= 50)
				{
					TIM10_10ms_counter=0;
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
				}
			}
			if(pwm_start_flag==2)		//팬이 역회전 하고 있을 때 LED13이 100ms로 깜빡임
			{
				if(TIM10_10ms_counter >= 100)
				{
					TIM10_10ms_counter=0;
					HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
				}
			}

		if(get_button(BUTTON4_GPIO_Port, BUTTON4_Pin, 4) == BUTTON_PRESS)	// button4를 누르면 다시 auto모드로
		{
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			break;
		}
		}
	}
}
