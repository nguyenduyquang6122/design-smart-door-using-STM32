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
#include "rc522.h"
#include "lcd.h"
#include "string.h"
#include "stdio.h"
#include "keypad.h"
#include "stdbool.h"
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
// Trang thai
#define OK 0
#define NOT_OK 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
// ID default
char key_card[8] = {0x13,0xC8,0xC8,0x0D,0,0,0,0};
char status;
char str[MFRC522_MAX_LEN]; //MFRC522_MAX_LEN = 16
char serNum[5];
int count_error_rfid = 0;
int wrong_card = 0;

// Password default
char password[] = {'1','1','1','1'};
uint8_t key;
char i,j,tmp;
char count_key = 0;
char count_key_in = 0;
char count_enter_pass = 0;
char key_pass[5];
char buffer_pass[5];
char new_pass1[5];
char new_pass2[5];
char mode_pass = 2;
char status_pass = 2;
char check_pass = 2;
char checking = NOT_OK;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void run_Normal(void);
char run_CheckPass(void);
void run_ChangePass(void);
void run_InputPass(void);
void get_key(void);
void check_card_RFID(void);
void notify_audio(int s);
void loop_main(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  MFRC522_Init();
  lcd_init();
  lcd_put_cur(0, 1);
  lcd_send_string("WELLCOME HAUI");
  HAL_Delay(1000);
  lcd_clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    loop_main();
    check_card_RFID();
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA9 PA10 PA11
                           PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void add_card()
{
  char buff_uID[10];
  status = MFRC522_Request(PICC_REQIDL, str);
  status = MFRC522_Anticoll(str);
  memcpy(serNum, str, 4);
	if(status == MI_OK)
  {
		for(i=0; i<4; i++)
		{
			key_card[i+4] = serNum[i];
			
		}
    lcd_clear();
    lcd_put_cur(0, 1);
    lcd_send_string("Card's number:");
    memset(buff_uID,0,10);
    sprintf(buff_uID, "%02X-%02X-%02X-%02X", serNum[0],serNum[1],serNum[2],serNum[3]);
    lcd_put_cur(1,0);
    lcd_send_string(buff_uID);
		HAL_Delay(3000);
		lcd_clear();
		
	}
}
void less_card()
{
	char buff_uID[10];
	lcd_clear();
  lcd_put_cur(0, 1);
  lcd_send_string("Choose Card:");
	if ( key == '1')
	{
		lcd_put_cur(0, 1);
		lcd_send_string("Deleted Card:");
		sprintf(buff_uID, "%02X-%02X-%02X-%02X", key_card[0],key_card[1],key_card[2],key_card[3]);
    lcd_put_cur(1,0);
    lcd_send_string(buff_uID);
    HAL_Delay(1000);
		for(i=0; i<4; i++)
    {
      key_card[i] = key_card[i+4];
			key_card[i+4] = 0;
    }
		HAL_Delay(2000);
    lcd_clear();
	}
	else if ( key == '2')
	{
		lcd_put_cur(0, 1);
		lcd_send_string("Deleted Card:");
		sprintf(buff_uID, "%02X-%02X-%02X-%02X", key_card[4],key_card[5],key_card[6],key_card[7]);
    lcd_put_cur(1,0);
    lcd_send_string(buff_uID);
    HAL_Delay(1000);
		for(i=4; i<8; i++)
    {
      key_card[i] = 0;
    }
		HAL_Delay(2000);
    lcd_clear();
	}
}
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
    lcd_clear();
    count_key_in = 0;
    count_key = 0;
    mode_pass = MODE_CHANGE;
  }
  // Nhan * de backspace
  else if (key == '*')
  {
    if ((count_key > 0)&&(checking == OK))
    {
      count_key--;
      lcd_put_cur(1, count_key);
      lcd_send_data (' ');
    }
    if (count_key_in > 0&&(mode_pass==MODE_INPUT_PASS))
    {
      if(count_key_in<4)
      {
        lcd_put_cur(1, count_key_in-1);
        lcd_send_data (' ');
        count_key_in--;
      } 
      else
      {
        lcd_put_cur(1, count_key_in-5);
        lcd_send_data (' ');
        count_key_in--;
      }
    }
  }
  // Nhan # de xac nhan password or cho phep nhap password
  else if (key == '#') 
  {
    mode_pass = MODE_RUN;
  }
	else if (key == 'B')
	{
		add_card();
	}
	else if (key == 'C')
	{
		less_card();
	}
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
  checking = OK;
  if ((key >= '0')&&(key <= '9'))
  {
    if (count_key == 0)
    {
      lcd_clear(); // Xoa man hinh
    }
    if (count_key < 4)
    {
      buffer_pass[count_key] = key;
      lcd_put_cur(1,count_key);
      lcd_send_string("*"); // Hien thi '*' the hien dang nhap pass
      count_key++;
      key = 0;
    }
    if (count_key == 4)
    {
      count_key = 0;
      lcd_clear(); // Xoa man hinh
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
        lcd_clear();
        lcd_put_cur(0,0);
        lcd_send_string("Wrong password!"); // Hien thi sai mat khau
        notify_audio(5);
        HAL_Delay(3000);
        lcd_clear();
      }
    }
  }
  return check_pass;
  checking = NOT_OK;
}

// Ham run_Normal
void run_Normal()
{
  lcd_put_cur(0, 1);
  lcd_send_string("ENTER PASSWORD:");
  status_pass = run_CheckPass();
  if (status_pass == OK)
  {
    lcd_clear();
    lcd_put_cur(0,0);
    lcd_send_string("Door is open!"); // Hien thi mo cua
    notify_audio(3);
    HAL_Delay(3000);
    lcd_clear();
    count_enter_pass = 0;
    mode_pass = 2;
    check_pass = 2;
  }
  else if (status_pass == NOT_OK)
  {
    check_pass = 2;
    count_enter_pass++;
    if (count_enter_pass == 3)
    {
      count_enter_pass = 0;
      lcd_clear();
      lcd_put_cur(0,0);
      lcd_send_string("XXXXXXXXXXXXXXX"); // Canh bao
      notify_audio(11);
      lcd_clear();
    }
    mode_pass = MODE_RUN;
  }
  else {}
}

// Ham run_ChangePass
void run_ChangePass()
{
  lcd_put_cur(0, 1);
  lcd_send_string("OLD PASSWORD:");
  status_pass = run_CheckPass();
  if (status_pass == OK)
  {
    lcd_put_cur(0,1);
    lcd_send_string("NEW PASSWORD 1:");
    mode_pass = MODE_INPUT_PASS;
  }
  else if (status_pass == NOT_OK)
  {
    lcd_clear();
    status_pass = 2;
    mode_pass = MODE_RUN;
  }
  else {}
}

// Ham run_InputPass
void run_InputPass(){
  if ((key >= '0')&&(key <= '9'))
  {
    if (count_key_in < 4)
    {
      new_pass1[count_key_in] = key;
      lcd_put_cur(1,count_key_in);
      lcd_send_string("*");
      count_key_in++;
      if (count_key_in == 4)
      {
        lcd_clear();
        lcd_put_cur(0,1);
        lcd_send_string("NEW PASSWORD 2:");
      }
      key = 0;
    }
    else
    {
      new_pass2[count_key_in-4] = key;
      lcd_put_cur(1,count_key_in-4);
      lcd_send_string("*");
      count_key_in++;
      key = 0;
    }
    if (count_key_in == 8)
    {
      lcd_clear();
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
        
        lcd_clear();
        lcd_put_cur(0,0);
        lcd_send_string("CHANGE SUCCESSFULLY");
        check_pass = 2;
      }
      else
      {
        lcd_clear();
        lcd_put_cur(0,0);
        lcd_send_string("CHANGE UNSUCCESSFULLY");
        check_pass = 2;
      }
      HAL_Delay(2000);
      lcd_clear();
      status_pass = 2;
      mode_pass = MODE_RUN;
    }
  }
}

// Ham check card
void check_card_RFID()
{
  bool is_true_card = false;
  char buff_uID[10];
  status = MFRC522_Request(PICC_REQIDL, str);
  status = MFRC522_Anticoll(str);
  memcpy(serNum, str, 4);
  if(status == MI_OK)
  {
    lcd_clear();
    lcd_put_cur(0, 1);
    lcd_send_string("Card's number:");
    memset(buff_uID,0,10);
    sprintf(buff_uID, "%02X-%02X-%02X-%02X", serNum[0],serNum[1],serNum[2],serNum[3]);
    lcd_put_cur(1,0);
    lcd_send_string(buff_uID);
    HAL_Delay(2000);
    for(i=0; i<4; i++)
    {
      if(key_card[i] != serNum[i])
			{
				for(i=4; i<8; i++)
				{
					if(key_card[i] != serNum[i-4]) is_true_card = false;
				}
			}
      else is_true_card = true;
    }
    if(is_true_card == false)
    {
      lcd_clear();
      lcd_put_cur(0, 0);;
      lcd_send_string("Wrong card");
      notify_audio(5);
      HAL_Delay(3000);
      lcd_clear();
    }
    else
    {
      lcd_clear();
      lcd_put_cur(0, 0);
      lcd_send_string("Door is open!");
      notify_audio(3);
      mode_pass = 2;
      HAL_Delay(3000);
      lcd_clear();
    }
  }
}

// Ham thong bao bang am thanh
void notify_audio(int s)
{
  for(i=0; i<s; i++)
  {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_Delay(500);
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
