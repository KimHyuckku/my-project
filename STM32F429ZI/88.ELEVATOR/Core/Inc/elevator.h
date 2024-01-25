#include "main.h"
#include "button.h"
#include "i2c_lcd.h"
#include <stdio.h>

#define STOP 0
#define UP 1
#define DOWN 2

extern void setpmotor_drive(int direction);
extern void set_rpm(int rpm);

void elevator_init(void);
void elevator_main(void);
void elevator_inside(void);

int current_elevator_floor = 0;
int rpm = 13;
int dir = 0;
int destination = 0;

//FND
#define FND_a  GPIO_PIN_1
#define FND_b  GPIO_PIN_2
#define FND_c  GPIO_PIN_3
#define FND_d  GPIO_PIN_4
#define FND_e  GPIO_PIN_5
#define FND_f  GPIO_PIN_6
#define FND_g  GPIO_PIN_10
#define FND_h  GPIO_PIN_11

uint32_t FND_font[10] =
{
  FND_a|FND_b|FND_c|FND_d|FND_e|FND_h,  // 0
  FND_a|FND_b,                          // 1
  FND_a|FND_c|FND_d|FND_f|FND_h,        // 2
  FND_a|FND_b|FND_c|FND_f|FND_h,        // 3
  FND_a|FND_b|FND_e|FND_f,  			// 4
  FND_b|FND_c|FND_e|FND_f|FND_h,  		// 5
  FND_b|FND_c|FND_d|FND_e|FND_f|FND_h,  // 6
  FND_a|FND_b|FND_f|FND_e,  			// 7
  FND_a|FND_b|FND_c|FND_d|FND_e|FND_f|FND_h,   // 8
  FND_a|FND_b|FND_c|FND_e|FND_f|FND_h   // 9
};

uint16_t FND_all = FND_a|FND_b|FND_c|FND_d|FND_e|FND_f|FND_g|FND_h;
