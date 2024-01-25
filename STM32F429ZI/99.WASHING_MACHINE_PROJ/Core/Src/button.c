#include "main.h"
#include "button.h"
#include "i2c_lcd.h"
// 초기버튼 상태 table
char button_status[BUTTON_NUMBER]=
{BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE};
uint8_t lcd_display_mode_flag=0;
uint8_t button1_mode_flag=0;
uint8_t btn3_act_index=0;

extern RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef mTime;	// time information

void lcd_display_mode_select(void)
{
	char lcd_buff[20];

	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		i2c_lcd_init();
		lcd_display_mode_flag++;
		lcd_display_mode_flag %= 4;

		if(lcd_display_mode_flag==0)
		{
			sprintf(lcd_buff, "MENU Number: %d", lcd_display_mode_flag);
			move_cursor(0, 0);
			lcd_string(lcd_buff);
			sprintf(lcd_buff, "Do Activate?");
			move_cursor(1, 0);
			lcd_string(lcd_buff);
		}
		if(lcd_display_mode_flag==1)
		{
			sprintf(lcd_buff, "MENU Number: %d", lcd_display_mode_flag);
			move_cursor(0, 0);
			lcd_string(lcd_buff);
			sprintf(lcd_buff, "Set Washing");
			move_cursor(1, 0);
			lcd_string(lcd_buff);
		}
		if(lcd_display_mode_flag==2)
		{
			sprintf(lcd_buff, "MENU Number: %d", lcd_display_mode_flag);
			move_cursor(0, 0);
			lcd_string(lcd_buff);
			sprintf(lcd_buff, "Set Dehydrate");
			move_cursor(1, 0);
			lcd_string(lcd_buff);
		}
		if(lcd_display_mode_flag==3)
		{
			sprintf(lcd_buff, "MENU Number: %d", lcd_display_mode_flag);
			move_cursor(0, 0);
			lcd_string(lcd_buff);
			sprintf(lcd_buff, "Set Water Depth");
			move_cursor(1, 0);
			lcd_string(lcd_buff);
		}
	}


	if(get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
	{
			i2c_lcd_init();
			button1_mode_flag++;
			button1_mode_flag %= 2;

			if(button1_mode_flag==0)
			{
				i2c_lcd_init();
				sprintf(lcd_buff, "SET COMPLETE");
				move_cursor(0, 0);
				lcd_string(lcd_buff);
			}

			if(lcd_display_mode_flag==0 && button1_mode_flag==1)
			{
				btn3_act_index=1;
			}
			if(lcd_display_mode_flag==1 && button1_mode_flag==1)
			{
				sprintf(lcd_buff, "TIME: 000");
				move_cursor(0, 0);
				lcd_string(lcd_buff);
				sprintf(lcd_buff, "SPEED: 000");
				move_cursor(1, 0);
				lcd_string(lcd_buff);
			}
			if(lcd_display_mode_flag==2 && button1_mode_flag==1)
			{
				sprintf(lcd_buff, "TIME: 000");
				move_cursor(0, 0);
				lcd_string(lcd_buff);
				sprintf(lcd_buff, "SPEED: 000");
				move_cursor(1, 0);
				lcd_string(lcd_buff);
			}
			if(lcd_display_mode_flag==3 && button1_mode_flag==1)
			{
				sprintf(lcd_buff, "Dep: 000");
				move_cursor(0, 0);
				lcd_string(lcd_buff);
				sprintf(lcd_buff, "Tmp:00 Wet:00");
				move_cursor(1, 0);
				lcd_string(lcd_buff);
			}

	}
}
// get_button(gpio, pin, button번호)
// 완전히 눌렀다 떼면 BUTTON_RELEASE (1)을 return
int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_PIN, uint8_t button_number)
{
	unsigned char curr_state;

	curr_state=HAL_GPIO_ReadPin(GPIO, GPIO_PIN);	//0, 1
	//버튼이 눌려졌으나 처음 상태

	if(curr_state== BUTTON_PRESS && button_status[button_number]== BUTTON_RELEASE)
	{
		HAL_Delay(100);		//noise가 지나가기를 기다린다.
		button_status[button_number]=BUTTON_PRESS;		// 현재의 버튼 상태를 저장
		return BUTTON_RELEASE;		//버튼이 눌러진 상태이나 아직은 noise상태로 인정
	}
	else if(curr_state== BUTTON_RELEASE && button_status[button_number]== BUTTON_PRESS)
	{		// 1. 이전에 버튼이 눌러진 상태였고 지금은 버튼을 뗀 상태이면
		button_status[button_number]=BUTTON_RELEASE;	// 2. button_status table을 초기화하고
		return BUTTON_PRESS;	// 3. 버튼을 1번 눌렀다 뗀것으로 인정한다.
	}
	return BUTTON_RELEASE;

}

