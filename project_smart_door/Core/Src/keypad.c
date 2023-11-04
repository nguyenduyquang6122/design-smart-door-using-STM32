#include "keypad.h"

#define R1_PORT GPIOB
#define R1_PIN GPIO_PIN_7

#define R2_PORT GPIOB
#define R2_PIN GPIO_PIN_6

#define R3_PORT GPIOB
#define R3_PIN GPIO_PIN_5

#define R4_PORT GPIOB
#define R4_PIN GPIO_PIN_4

#define C1_PORT GPIOA
#define C1_PIN GPIO_PIN_12

#define C2_PORT GPIOA
#define C2_PIN GPIO_PIN_11

#define C3_PORT GPIOA
#define C3_PIN GPIO_PIN_10

#define C4_PORT GPIOA
#define C4_PIN GPIO_PIN_9

char read_keypad (void)
{
	// nhan cot 1
	HAL_GPIO_WritePin (C1_PORT, C1_PIN, 0);
	HAL_GPIO_WritePin (C2_PORT, C2_PIN, 1);
	HAL_GPIO_WritePin (C3_PORT, C3_PIN, 1);
	HAL_GPIO_WritePin (C4_PORT, C4_PIN, 1);
	
	if (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN)) // nhan phim 1
	{
		while (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN));
		return '1';
	}
	
	if (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN)) // nhan phim 4
	{
		while (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN));
		return '4';
	}
	
	if (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN))   // nhan phim 7
	{
		while (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN));
		return '7';
	}
	
	if (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN))   // nhan phim *
	{
		while (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN));
		return '*';
	}
	
	// nhan cot 2
	HAL_GPIO_WritePin (C1_PORT, C1_PIN, 1);
	HAL_GPIO_WritePin (C2_PORT, C2_PIN, 0);
	HAL_GPIO_WritePin (C3_PORT, C3_PIN, 1);
	HAL_GPIO_WritePin (C4_PORT, C4_PIN, 1);
	
	if (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN)) // nhan phim 2
	{
		while (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN));
		return '2';
	}
	
	if (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN))   // nhan phim 5
	{
		while (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN));
		return '5';
	}
	
	if (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN))   // nhan phim 8
	{
		while (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN));
		return '8';
	}
	
	if (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN))   // nhan phim 0
	{
		while (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN));
		return '0';
	}
	
	// nhan cot 3
	HAL_GPIO_WritePin (C1_PORT, C1_PIN, 1);
	HAL_GPIO_WritePin (C2_PORT, C2_PIN, 1);
	HAL_GPIO_WritePin (C3_PORT, C3_PIN, 0);
	HAL_GPIO_WritePin (C4_PORT, C4_PIN, 1);
	
	if (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN))   // nhan phim 3
	{
		while (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN));
		return '3';
	}
	
	if (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN))   // nhan phim 6
	{
		while (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN));
		return '6';
	}
	
	if (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN))   // nhan phim 9
	{
		while (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN));
		return '9';
	}
	
	if (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN))   // nhan phim #
	{
		while (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN));
		return '#';
	}

	// nhan cot 4
	HAL_GPIO_WritePin (C1_PORT, C1_PIN, 1);
	HAL_GPIO_WritePin (C2_PORT, C2_PIN, 1);
	HAL_GPIO_WritePin (C3_PORT, C3_PIN, 1);
	HAL_GPIO_WritePin (C4_PORT, C4_PIN, 0);
	
	if (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN))   // nhan phim A
	{
		while (!HAL_GPIO_ReadPin (R1_PORT, R1_PIN));
		return 'A';
	}
	
	if (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN))   // nhan phim B
	{
		while (!HAL_GPIO_ReadPin (R2_PORT, R2_PIN));
		return 'B';
	}
	
	if (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN))   // nhan phim C
	{
		while (!HAL_GPIO_ReadPin (R3_PORT, R3_PIN));
		return 'C';
	}
	
	if (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN))   // nhan phim D
	{
		while (!HAL_GPIO_ReadPin (R4_PORT, R4_PIN));
		return 'D';
	}
	return 0;
}