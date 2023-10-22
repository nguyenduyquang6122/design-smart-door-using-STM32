/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "i2c-lcd.h"
#include "string.h"
#include "stdio.h"
#include "keypad.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// Cac mode chuong trinh
#define MODE_RUN 0
#define MODE_CHANGE 1
#define MODE_INPUT_PASS 3
// Trang thai cua
#define OK 0
#define NOT_OK 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void run_Normal(void);
char run_CheckPass(void);
void run_ChangePass(void);
void run_InputPass(void);
void get_key(void);
void loop_main(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Password mac dinh
char password[] = {'0','0','0','0'};

uint8_t key;
char i,j,tmp;
char count_key = 0;
char count_key_in = 0;
char count_enter_pass = 0;
char key_pass[5];
char buffer_pass[5];
char new_pass1[5];
char new_pass2[5];
unsigned char data[]="NHOM 8 - KHOA DIEN TU \r\n		Welcome!		";
unsigned char buffer[100];
unsigned char clear[1] = {12};
unsigned char clear_[1] = {8};
char mode_pass = MODE_RUN;
char status_pass = 2;
char check_pass = 2;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Transmit(&huart1,data,strlen(data),100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		loop_main();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Ham nhan gia tri tu ban phim nhap
void get_key()
{
	uint8_t key_input = read_keypad();
	if (key_input != 0xFF)
	{
		key = key_input;
		HAL_Delay(100);
	}
	// Che do doi mat khau
	if ((key == 'A')&&(mode_pass == MODE_RUN))
	{
		HAL_UART_Transmit(&huart1,clear,1,100); //
		unsigned char doimk[] = "Nhap mat khau cu: \r\n";
		HAL_UART_Transmit(&huart1,doimk,strlen(doimk),100);
		count_key_in = 0;
		count_key = 0;
		mode_pass = MODE_CHANGE;
	}
	// Nhan * de backspace
	else if (key == '*')
	{
		if (count_key > 0)
		{
			count_key--;
			HAL_UART_Transmit(&huart1,clear_,1,100);
		}
		if (count_key_in > 0)
		{
			count_key_in--;
			HAL_UART_Transmit(&huart1,clear_,1,100);
		}
	}
	// Nhan # de xac nhan password or cho phep nhap password
	else if (key == '#') {}
	else {}
	key_input = 0;
}

// Ham vong lap chuong trinh chinh
void loop_main()
{
	get_key();
	switch (mode_pass)
	{
		case MODE_RUN:
			run_Normal();
			break;
		case MODE_CHANGE:
			run_ChangePass();
			break;
		case MODE_INPUT_PASS:
			run_InputPass();
			break;
		default:
			break;
	}
}

// Ham check password
char run_CheckPass()
{
	if ((key >= '0')&&(key <= '9'))
	{
		if (count_key == 0)
		{
			HAL_UART_Transmit(&huart1,clear,1,100); // Xoa man hinh
		}
		if (count_key < 4)
		{
			buffer_pass[count_key] = key;
			unsigned char display[] = "*";
			HAL_UART_Transmit(&huart1,display,strlen(display),100); // Hien thi '*' the hien dang nhap pass
			count_key++;
			key = 0;
		}
		if (count_key == 4)
		{
			count_key = 0;
			HAL_UART_Transmit(&huart1,clear,1,100); // Xoa man hinh
			for(i = 0; i < 4; i++){
				if(password[i] != buffer_pass[i])
					break;
			}
			if (i == 4)
			{
				check_pass = OK;
			}
			else
			{
				check_pass = NOT_OK;
				HAL_UART_Transmit(&huart1,clear,1,100);// Xoa man hinh
				unsigned char no_pass[] = "Wrong Password!";
				HAL_UART_Transmit(&huart1,no_pass,strlen(no_pass),100);// Hien thi sai mat khau
			}
		}
	}
	return check_pass;
}

// Ham run_Normal
void run_Normal()
{
	status_pass = run_CheckPass();
	if (status_pass == OK)
	{
		HAL_UART_Transmit(&huart1,data,strlen(data),100); // Hien thi mo cua
		count_enter_pass = 0;
		mode_pass = MODE_RUN;
		check_pass = 2;
	}
	else if (status_pass == NOT_OK)
	{
		check_pass = 2;
		count_enter_pass++;
		if (count_enter_pass == 3)
		{
			count_enter_pass = 0;
			HAL_UART_Transmit(&huart1,clear,1,100);
			unsigned char sos[] = "Ban nhap sai mat khau qua 3 lan";
			HAL_UART_Transmit(&huart1,sos,strlen(sos),100);// Canh bao
		}
		//mode_pass = MODE_RUN;
	}
	else {}
}

// Ham run_ChangePass
void run_ChangePass()
{
	status_pass = run_CheckPass();
	if (status_pass == OK)
	{
		unsigned char doimk[] = "Nhap new password 1: \r\n";
		HAL_UART_Transmit(&huart1,doimk,strlen(doimk),100);
		mode_pass = MODE_INPUT_PASS;
	}
	else if (status_pass == NOT_OK)
	{
		HAL_Delay(500);
		HAL_UART_Transmit(&huart1,clear,1,100);
		status_pass = 2;
		mode_pass = MODE_RUN;
	}
	else {}
}

// Ham run_InputPass
void run_InputPass(){
/*
	if (count_key_in < 4)
	{
		unsigned char doimk[] = "Nhap new password 1: \r\n";
		HAL_UART_Transmit(&huart1,doimk,strlen(doimk),100);
	}
	else
	{
		unsigned char doimk[] = "Nhap new password 2: \r\n";
		HAL_UART_Transmit(&huart1,doimk,strlen(doimk),100);
	}
*/
	if ((key >= '0')&&(key <= '9'))
	{
		if (count_key_in < 4)
		{
			new_pass1[count_key_in] = key;
			count_key_in++;
			unsigned char display[] = "*";
			HAL_UART_Transmit(&huart1,display,strlen(display),100);
			if (count_key_in == 4)
			{
				HAL_UART_Transmit(&huart1,clear,1,100);
				unsigned char doimk[] = "Nhap new password 2: \r\n";
				HAL_UART_Transmit(&huart1,doimk,strlen(doimk),100);
			}
			key = 0;
		}
		else
		{
			new_pass2[count_key_in-4] = key;
			count_key_in++;
			unsigned char display[] = "*";
			HAL_UART_Transmit(&huart1,display,strlen(display),100);
			key = 0;
		}
		if (count_key_in == 8)
		{
			HAL_UART_Transmit(&huart1,clear,1,100);
			count_key_in = 0;
			for(i = 0; i < 4; i++)
			{
				if (new_pass1[i] != new_pass2[i])
					break;
			}
			if (i == 4)
			{
				password[0] = new_pass1[0];
				password[1] = new_pass1[1];
				password[2] = new_pass1[2];
				password[3] = new_pass1[3];
				
				HAL_UART_Transmit(&huart1,clear,1,100);
				unsigned char doimk[] = "Doi mat khau thanh cong";
				HAL_UART_Transmit(&huart1,doimk,strlen(doimk),100);
			}
			else
			{
				HAL_UART_Transmit(&huart1,clear,1,100);
				unsigned char doimk[] = "Doi mat khau khong thanh cong";
				HAL_UART_Transmit(&huart1,doimk,strlen(doimk),100);
			}
			HAL_Delay(2000);
			HAL_UART_Transmit(&huart1,clear,1,100);
			status_pass = 2;
			mode_pass = MODE_RUN;
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
