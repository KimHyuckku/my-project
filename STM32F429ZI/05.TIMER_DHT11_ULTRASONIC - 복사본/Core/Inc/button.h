#include "main.h"	//for GPIO handling

#define BUTTON_RELEASE 1	//버튼을 땐 상태 1 pull-up
#define BUTTON_PRESS 0		//버튼을 누른 상태 0 ==> active-low 상태 push
#define BUTTON_NUMBER 4		//버튼 갯수 : 4

int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_PIN, uint8_t button_number);

