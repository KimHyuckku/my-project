#include "main.h"
#include "button.h"

void set_rpm(int rpm);
void stepmotor_running(void);
void setpmotor_drive(int direction);

extern void delay_us(unsigned long us);
extern int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_PIN, uint8_t button_number);
// RPM(Revolution Per Minute) : 분당 회전수
// 1분 : 60초 : 1,000,000 us(1초) x 60 = 60,000,000 us
// 1,000,000 us(1초)
// --> 1초(1000 ms) ==> 1 ms(1000 us) * 1000 ms ==> 1,000,000 us
// 4096 스텝 : 1바퀴 (4096 스텝 이동)
// --1바퀴 도는데 필요한 총 스텝수 : 4096
// 4096 / 8 (0.7) ==> 512 sequence : 360도
// 1 sequence(8 step) : 0.70312도
// 0.70312도 x 512 sequence = 360도

// -------- set_rpm(13)으로 지정시의 동작 상황 -------
// 60,000,000 us(1분) / 4096 / rpm
// 1126 us(1스텝 idle타임) x 4096 = 4,612,096 us = 4612 ms = 4.6 s
// 60초 / 4.6 (1최전시 소요시간 초) ==> 13회전
// 시계 방향으로 1회전 <---> 반시계방향으로 1회전
void set_rpm(int rpm)
{
	delay_us(60000000/4096/rpm);
	// 최대 speed 기준(13) : delay_us(1126);
}

#if 1
void stepmotor_running(void)
{
	int direction = 0;
	int rpm = 13;
	while(1)
	{
		if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
		{
			direction %= 2;
			direction++;
		}
		if(get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
		{
			direction = 0;
		}
		setpmotor_drive(direction);
		set_rpm(rpm);
		//printf("turn number : %d\n", i);
	}
}

#else
void stepmotor_main_test(void)
{
	while(1)
	{
		for (int i=0; i<512; i++) //시계방향 1회전
		{
			for(int j=0; j<8; j++)
			{
				setpmotor_drive(7-j);
				set_rpm(13);	// rpm 값만큼 wait
			}
		}

	}
}
#endif

// direction : 1 == 시계방향 회전
//			   2 --> 반시계
//			   0 : idle
#if 1
void setpmotor_drive(int direction)
{
	static int step = 0;

	switch(step){
	case 0:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);

		break;
	case 4:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	}
	if (direction == 1) // 정회전 or 올라감
	{
		step++;			// for (step = 0; step < 8; step++)
		step %= 8;		// 다음 진행할 step 준비
		// if (step >= 8) step = 0;
	}
	else if (direction == 2) // 역회전 or 내려감
	{
		step--; 		//
		if(step < 0 ) step = 7;
	}
	else if (direction == 0)
	{

	}
}

#else
void setpmotor_drive(int step)
{
	switch(step){
	case 0:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);

		break;
	case 4:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOD, IN1_Pin, 1);
		HAL_GPIO_WritePin(GPIOD, IN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN3_Pin, 0);
		HAL_GPIO_WritePin(GPIOD, IN4_Pin, 1);
		break;
	}
}
#endif
