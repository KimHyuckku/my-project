#include "elevator.h"






void elevator_init(void)
{
	char lcd_buff[40];
	i2c_lcd_init();
	move_cursor(0, 0);
	sprintf(lcd_buff, "Elevator Moving");
	lcd_string(lcd_buff);

	while (1)
	{
		if (current_elevator_floor == 1) break;
		setpmotor_drive(DOWN);
		set_rpm(rpm);
	}
}


void elevator_main(void)
{

	elevator_inside();

}

void elevator_inside(void)
{
	char lcd_buff[40];



		if(get_button(BUTTON1F_GPIO_Port, BUTTON1F_Pin, 4) == BUTTON_PRESS)
		{
			destination = 1;
			dir = DOWN;

			move_cursor(1, 0);
			sprintf(lcd_buff, "Destination: 1F");
			lcd_string(lcd_buff);
		}
		else if(get_button(BUTTON1F_GPIO_Port, BUTTON2F_Pin, 5) == BUTTON_PRESS)
		{
			destination = 2;
			if (current_elevator_floor < 2) dir = UP;
			else dir = DOWN;

			move_cursor(1, 0);
			sprintf(lcd_buff, "Destination: 2F");
			lcd_string(lcd_buff);
		}
		else if(get_button(BUTTON1F_GPIO_Port, BUTTON3F_Pin, 6) == BUTTON_PRESS)
		{
			destination = 3;
			if (current_elevator_floor < 3) dir = UP;
			else dir = DOWN;

			move_cursor(1, 0);
			sprintf(lcd_buff, "Destination: 3F");
			lcd_string(lcd_buff);
		}
		else if(get_button(BUTTON1F_GPIO_Port, BUTTON4F_Pin, 7) == BUTTON_PRESS)
		{
			destination = 4;
			dir = UP;

			move_cursor(1, 0);
			sprintf(lcd_buff, "Destination: 4F");
			lcd_string(lcd_buff);
		}
		else{}

		if(current_elevator_floor == destination) dir = STOP;

		setpmotor_drive(dir);
		set_rpm(rpm);

		HAL_GPIO_WritePin(GPIOB, FND_all, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, FND_font[current_elevator_floor], GPIO_PIN_RESET);



}

