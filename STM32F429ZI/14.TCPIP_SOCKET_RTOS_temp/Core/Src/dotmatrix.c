#include "main.h"
#include "cmsis_os.h"

extern void lcd_string(uint8_t *str);
extern void move_cursor(uint8_t row, uint8_t column);

int dotmatrix_main_test(void);
void init_dotmatrix(void);

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

const uint8_t blank[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

uint8_t number_data[20][10] =
{
	{
		0b00001000,
		0b11101000,
		0b00101000,
		0b00101000,
		0b00000000,
		0b01111000,
		01001000,
		0b01111000
	},
	{
		0b01001000,
		0b11101000,
		0b01011000,
		0b10101000,
		0b01011000,
		0b00001000,
		0b11110000,
		0b00010000,
	    6   // 점 0b00000110
	},
	{
		0b00000000,
		0b11110000,
		0b00010000,
		0b00010000,
		0b00000000,
		0b11111000,
		0b00100000,
		0b00100000,
	    6
	},
	{
		0b00100000,
		0b01110000,
		0b11111000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00100000,
		0b00000000,
	    6
	},
	{
		0b00010000,	//4
		0b00110000,
		0b01010000,
		0b10010000,
		0b11111000,
		0b00010000,
		0b00010000,
	    6
	},
	{
		0b11111000,	//5
		0b10000000,
		0b11110000,
		0b00001000,
		0b00001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b00110000,	//6
		0b01000000,
		0b10000000,
		0b11110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b11111000,	//7
		0b10001000,
		0b00001000,
		0b00010000,
		0b00100000,
		0b00100000,
		0b00100000,
	    6
	},
	{
		0b01110000,	//8
		0b10001000,
		0b10001000,
		0b01110000,
		0b10001000,
		0b10001000,
		0b01110000,
	    6
	},
	{
		0b01110000,	//9
		0b10001000,
		0b10001000,
		0b01111000,
		0b00001000,
		0b00010000,
		0b01100000,
	    6
	},
	{
		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
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

unsigned char display_data[8]; // 최종 8x8 출력할 데이터
unsigned char scroll_buffer[50][8] = {0}; // 스트롤할 데이터가 들어있는 버퍼
int number_of_character = 11; //출력할 문자 갯수

// 초기화 작업
// 1. display_data에 number_data의 [0]에 있는 내용 복사
// 2. number_data를 scroll_buffer에 복사
// 3. dotmatrix의 led를 off

void init_dotmatrix(void)
{
	for (int i=0; i<8; i++)
	{
		display_data[i] = number_data[i][0];
	}
	for (int i=1; i < number_of_character + 1; i++)
	{
		for (int j = 0; j < 8; j++)	// scroll_buffer[0] = blank
		{
			scroll_buffer[i][j] = number_data[i-1][j];
		}
	}
	//3
	for (int i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(col_port[i], col_pin[i] , 1);
	}
}

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

#if 1
extern osMutexId_t myMutex01Handle;
// scroll 문자 출력 프로그램
int dotmatrix_main_test(void)
{
	static int count = 0;	// 컬럼 count
	static int index = 0;	// scroll_buffer의 2차원 index값
	static uint32_t past_time = 0;	// 이전 tick값 저장
	char lcd_buff[40];

	//init_dotmatrix();

	uint32_t now = HAL_GetTick();	// 1ms
	// 1. 처음 시작 시 past_time = 0; now: 500 --> past_time = 500
	if(now - past_time >= 300)	// 500ms scroll
	{
		sprintf(lcd_buff, "now : %d", now);
		// 기존에 lock이 걸려 있으면 풀릴 떄 까지 기다린다.
		// control이 다른 task로 넘어가지 않도록 lock을 건다.
		if(osMutexWait(myMutex01Handle, 1000) == osOK)
		{
			move_cursor(0, 0);
			lcd_string(lcd_buff);
			osMutexRelease(myMutex01Handle);
			// unlock control이 다른 task로 넘어가도록 한다.
		}
		past_time = now;
		for (int i = 0 ; i < 8; i++)
		{
			display_data[i] = (scroll_buffer[index][i] << count) | (scroll_buffer[index+1][i] >> (8-count));
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
		write_row_data(display_data[i]);

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
