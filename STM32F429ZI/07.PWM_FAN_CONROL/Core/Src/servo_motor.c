#include "main.h"

void servo_motor_test_main(void);

extern TIM_HandleTypeDef htim2;

// 84000000(84 mHz)/1680 = 50000 Hz
// T= 1/f = 1/50000 Hz = 0.0002 sec(20 ms)
// 2 ms(180도) : 0.00002 * 100개
// 1.5(90도) : 0.00002 * 75개
// 1ms(0도) : 0.00002 * 50개
void servo_motor_test_main(void)
{
	while(1)
	{


		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 125);	// 180도
		HAL_Delay(1000);

		// 90도 회전
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 78);	// 90도
		HAL_Delay(1000);



		//0도
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 40);	// 0도
		HAL_Delay(1000);
	}


}
