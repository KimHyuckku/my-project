#include "main.h"

extern int current_elevator_floor;

int dotmatrix_main_up(void);
void init_dotmatrix_up(void);
int dotmatrix_main_down(void);
void init_dotmatrix_down(void);
int dotmatrix_main_stop(void);

GPIO_TypeDef *col_port[] =
{
		COL1_GPIO_Port, COL2_GPIO_Port, COL3_GPIO_Port, COL4_GPIO_Port,
		COL5_GPIO_Port, COL6_GPIO_Port, COL7_GPIO_Port, COL8_GPIO_Port
};

GPIO_TypeDef *row_port[] =
{
		ROW1_GPIO_Port, ROW2_GPIO_Port, ROW3_GPIO_Port, ROW4_GPIO_Port,
		ROW5_GPIO_Port, ROW6_GPIO_Port, ROW7_GPIO_Port, ROW8_GPIO_Port
};

uint16_t col_pin[] =
{
		COL1_Pin, COL2_Pin, COL3_Pin, COL4_Pin,
		COL5_Pin, COL6_Pin, COL7_Pin, COL8_Pin,
};

uint16_t row_pin[] =
{
		ROW1_Pin, ROW2_Pin, ROW3_Pin, ROW4_Pin,
		ROW5_Pin, ROW6_Pin, ROW7_Pin, ROW8_Pin,
};

const uint8_t blank[4][8] = {
	{
		0b00000000,
		0b00000010,
		0b11111110,
		0b01100010,
		0b00100010,
		0b00000010,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b01111001,
		0b11011001,
		0b10001101,
		0b11000111,
		0b01100111,
		0b00000000,
		0b00000000
	},
	{
		0b00000000,
		0b01110110,
		0b11011101,
		0b10001001,
		0b11000011,
		0b01100010,
		0b00000000,
		0b00000000
	},
	{
		0b00000100,
		0b00000100,
		0b11111111,
		0b10000100,
		0b11100100,
		0b00110100,
		0b00011100,
		0b00000000
	}
};

uint8_t upward_data[4][10] =
{
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00001110,
		0b00011100,
		0b00111000,
		0b01110000,
		0b01110000,
		0b00111000,
		0b00011100,
		0b00001110
	},
	{
		0b00001110,
		0b00011100,
		0b00111000,
		0b01110000,
		0b01110000,
		0b00111000,
		0b00011100,
		0b00001110
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	}
};

uint8_t downward_data[4][10] =
{
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b01110000,
		0b00111000,
		0b00011100,
		0b00001110,
		0b00001110,
		0b00011100,
		0b00111000,
		0b01110000
	},
	{
		0b00001110,
		0b00011100,
		0b00111000,
		0b01110000,
		0b01110000,
		0b00111000,
		0b00011100,
		0b00001110
	},
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	}
};


unsigned char flower_on[] = {			// all_on 문자 정의
		0b01000010,
		0b10011001,
		0b00100100,
		0b01011010,
		0b01011010,
		0b00100100,
		0b10011001,
		0b01000010
};

unsigned char all_on[] = {			// all_on 문자 정의
		0b01000010,
		0b10011001,
		0b00100100,
		0b01011010,
		0b01011010,
		0b00100100,
		0b10011001,
		0b01000010

		/*0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111*/
};

void write_column_data(int col)
{
	for (int i=0; i<8; i++)
	{
#if 1
		if (i==col)
			HAL_GPIO_WritePin(col_port[i], col_pin[i], 0);
		else HAL_GPIO_WritePin(col_port[i], col_pin[i], 1);
#else
		if (i==col)
			HAL_GPIO_WritePin(col_port[i], col_pin[i], 1);
		else HAL_GPIO_WritePin(col_port[i], col_pin[i], 0);
#endif
	}
}

// 0b00111100
void write_row_data(unsigned char data)
{
	unsigned char d;

	d = data;

	for(int i=0; i<8; i++)
	{
		if(d & (1 << i)) // 1인 경우
			HAL_GPIO_WritePin(row_port[i], row_pin[i], 1);
		else
			HAL_GPIO_WritePin(row_port[i], row_pin[i], 0);
	}
}


unsigned char display_data_up[8]; // 최종 8x8 출력할 데이터
unsigned char scroll_buffer_up[50][8] = {0}; // 스트롤할 데이터가 들어있는 버퍼
int number_of_character = 2; //출력할 문자 갯수

// 초기화 작업
// 1. display_data에 upward_data의 [0]에 있는 내용 복사
// 2. upward_data를 scroll_buffer에 복사
// 3. dotmatrix의 led를 off

void init_dotmatrix_up(void)
{
	for (int i=0; i<8; i++)
	{
		display_data_up[i] = upward_data[i][0];
	}
	for (int i=1; i < number_of_character + 1; i++)
	{
		for (int j = 0; j < 8; j++)	// scroll_buffer[0] = blank
		{
			scroll_buffer_up[i][j] = upward_data[i-1][j];
		}
	}
	//3
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(col_port[i], col_pin[i] , 1);
	}
}


#if 1
// scroll 문자 출력 프로그램
int dotmatrix_main_up(void)
{
	static int count = 0;	// 컬럼 count
	static int index = 0;	// scroll_buffer의 2차원 index값
	static uint32_t past_time = 0;	// 이전 tick값 저장

	for (int i=0; i<8; i++)
	{
		scroll_buffer_up[0][i] = blank[current_elevator_floor-1][i];
	}

	uint32_t now = HAL_GetTick();	// 1ms
	// 1. 처음 시작 시 past_time = 0; now: 500 --> past_time = 500
	if(now - past_time >= 100)	// 500ms scroll
	{
		past_time = now;
		for (int i = 0 ; i < 8; i++)
		{
			display_data_up[i] = (scroll_buffer_up[index][i] << count) | (scroll_buffer_up[index+1][i] >> (8-count));
		}
		if (++count == 8)	// 8 칼럼을 다 처리했으면 다음 scroll_buffer로 이동하
		{
			count = 0;
			index++;
			if (index == number_of_character+1) index = 0;
		}
	}
	for(int i = 0; i < 8; i++)
	{
		// 공통 양극 방식
		// coulumn에는 0으르 ROW에는 1을 출력해야 해당 LED가 on된다.
		write_column_data(i);
		write_row_data(display_data_up[i]);

		HAL_Delay(1);
	}
}

#else

// 고정 문자 출력 demo program
int dotmatrix_main_test(void)
{
	while (1)
	{
		for(int i=0; i<8; i++)
		{
			// 공통 양극 방식
			// coulumn에는 0으르 ROW에는 1을 출력해야 해당 LED가 on된다.
			write_column_data(i);
			write_row_data(all_on[i]);

			HAL_Delay(1);
		}
	}


	return 0;
}
#endif



unsigned char display_data_down[8]; // 최종 8x8 출력할 데이터
unsigned char scroll_buffer_down[50][8] = {0}; // 스트롤할 데이터가 들어있는 버퍼

// 초기화 작업
// 1. display_data에 upward_data의 [0]에 있는 내용 복사
// 2. upward_data를 scroll_buffer에 복사
// 3. dotmatrix의 led를 off

void init_dotmatrix_down(void)
{
	for (int i=0; i<8; i++)
	{
		display_data_down[i] = downward_data[i][0];
	}
	for (int i=1; i < number_of_character + 1; i++)
	{
		for (int j = 0; j < 8; j++)	// scroll_buffer[0] = blank
		{
			scroll_buffer_down[i][j] = downward_data[i-1][j];
		}
	}
	//3
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(col_port[i], col_pin[i] , 1);
	}
}

// scroll 문자 출력 프로그램
int dotmatrix_main_down(void)
{
	static int count = 0;	// 컬럼 count
	static int index = 0;	// scroll_buffer의 2차원 index값
	static uint32_t past_time = 0;	// 이전 tick값 저장

	for (int i=0; i<8; i++)
	{
		scroll_buffer_down[0][i] = blank[current_elevator_floor-1][i];
	}

	uint32_t now = HAL_GetTick();	// 1ms
	// 1. 처음 시작 시 past_time = 0; now: 500 --> past_time = 500
	if(now - past_time >= 100)	// 500ms scroll
	{
		past_time = now;
		for (int i = 0 ; i < 8; i++)
		{
			display_data_down[i] = (scroll_buffer_down[index][i] >> count) | (scroll_buffer_down[index+1][i] << (8-count));
		}
		if (++count == 8)	// 8 칼럼을 다 처리했으면 다음 scroll_buffer로 이동하
		{
			count = 0;
			index++;
			if (index == number_of_character+1) index = 0;
		}
	}
	for(int i = 0; i < 8; i++)
	{
		// 공통 양극 방식
		// coulumn에는 0으르 ROW에는 1을 출력해야 해당 LED가 on된다.
		write_column_data(i);
		write_row_data(display_data_down[i]);

		HAL_Delay(1);
	}
}

int dotmatrix_main_stop(void)
{

	for (int i=0; i<8; i++)
	{
		display_data_down[i] = blank[current_elevator_floor-1][i];
	}

	for(int i = 0; i < 8; i++)
	{
		// 공통 양극 방식
		// coulumn에는 0으르 ROW에는 1을 출력해야 해당 LED가 on된다.
		write_column_data(i);
		write_row_data(display_data_down[i]);

		HAL_Delay(1);
	}

}

