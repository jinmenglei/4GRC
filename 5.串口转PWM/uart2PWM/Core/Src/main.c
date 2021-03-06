/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define USART_REC_LEN  			100  	//定义最大接收字节数 200
#define RXBUFFERSIZE   			1 		//缓存大小
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART2_RX_STA = 0; //接收状态标记
uint8_t aRxBuffer2[RXBUFFERSIZE];		  //HAL库使用的串口接收缓冲
BaseSerialData SBUS_CH;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int rec_cnt = 0;
int PWM1ms = 100;
int PWMcenter =150;
int PWMlow = 100;
int PWMhigh = 200;
int pwmcnt = 0;
int PWM_CH1_rec = 150;
int PWM_CH1_check = 150;

int PWM_CH2_rec = 150;
int PWM_CH2_check = 150;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t send_data[5] = {0xA1, 0xF1, 0x1C, 0x2F, 0x33};

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
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
  while (1)
  {
		HAL_Delay(50);
		//HAL_GPIO_TogglePin(LED_SHOW_GPIO_Port,LED_SHOW_Pin);
		if (rec_cnt++ > 5)
		{
			PWM_CH2_rec = PWM_CH1_rec = PWMcenter;
		}
		//HAL_UART_Transmit(&huart1,send_data,5,10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

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
	
	HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer2, RXBUFFERSIZE); //该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_SHOW_GPIO_Port, LED_SHOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PWM_CH2_Pin|PWM_CH1_Pin|LIGHT_Pin|DIR_B_Pin
                          |DIR_A_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_SHOW_Pin */
  GPIO_InitStruct.Pin = LED_SHOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_SHOW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PWM_CH2_Pin PWM_CH1_Pin LIGHT_Pin DIR_B_Pin
                           DIR_A_Pin */
  GPIO_InitStruct.Pin = PWM_CH2_Pin|PWM_CH1_Pin|LIGHT_Pin|DIR_B_Pin
                          |DIR_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : E_Input_Pin */
  GPIO_InitStruct.Pin = E_Input_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(E_Input_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim2.Instance)
	{
		pwmcnt++;
		if (pwmcnt < PWM_CH1_check)
		{
			HAL_GPIO_WritePin(PWM_CH1_GPIO_Port, PWM_CH1_Pin,GPIO_PIN_SET);
		}else
		{
			HAL_GPIO_WritePin(PWM_CH1_GPIO_Port, PWM_CH1_Pin,GPIO_PIN_RESET);
		}
		
		if (pwmcnt < PWM_CH2_check)
		{
			HAL_GPIO_WritePin(PWM_CH2_GPIO_Port, PWM_CH2_Pin,GPIO_PIN_SET);
		}else
		{
			HAL_GPIO_WritePin(PWM_CH2_GPIO_Port, PWM_CH2_Pin,GPIO_PIN_RESET);
		}
		if (pwmcnt >= PWM1ms*10)
		{
			PWM_CH1_check = PWM_CH1_rec;
			PWM_CH2_check = PWM_CH2_rec;
			pwmcnt = 0;
		}
	}
}

int Usart1_Flag = 0;
uint8_t Usart1Rxbuf[38];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	int pwm_rec = 0;
	float pwm_percent = 0;
	if (huart->Instance == USART1) //如果是串口1
	{
		
		//HAL_UART_Transmit(&huart1,aRxBuffer2,1,10);
		uint8_t temp;
		static uint8_t U1_count,
									U1_last_data,
									U1_last_last_data,
									U1_last_last_last_data;
		temp = aRxBuffer2[0];
		if(Usart1_Flag==0)
		{	
			if(U1_last_data==0xFD&&U1_last_last_data==0xFE&&U1_last_last_last_data==0xFF)
			{ 
				Usart1_Flag=1,U1_count=0;	
				Usart1Rxbuf[U1_count++] = 0xFF;
				Usart1Rxbuf[U1_count++] = 0xFE;
				Usart1Rxbuf[U1_count++] = 0xFD;
			}
		}
		
		if(Usart1_Flag==1)
		{	
			Usart1Rxbuf[U1_count]=temp;
			     
			U1_count++;                
			if(U1_count==38)
			{
				Usart1_Flag=0;
				//方向
				if (Usart1Rxbuf[35] == 0xFD && Usart1Rxbuf[36] == 0xFE && Usart1Rxbuf[37] == 0xFF)
				{
					HAL_GPIO_TogglePin(LED_SHOW_GPIO_Port,LED_SHOW_Pin);
					rec_cnt = 0;
					pwm_rec = Usart1Rxbuf[3]* 0x100 + Usart1Rxbuf[4];
					if (pwm_rec > 2047)
					{
						pwm_rec = 2047;
					}
					pwm_percent = pwm_rec/2047.f;
					
					PWM_CH1_rec = PWM1ms + pwm_percent*100;
					
					pwm_rec = Usart1Rxbuf[5]* 0x100 + Usart1Rxbuf[6];
					if (pwm_rec > 2047)
					{
						pwm_rec = 2047;
					}
					pwm_percent = pwm_rec/2047.f;
					
					PWM_CH2_rec = PWM1ms + pwm_percent*100;

//					
//					//run 
//					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, Usart1Rxbuf[4]* 0xFF + Usart1Rxbuf[5]);
//					//turn
//					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, Usart1Rxbuf[6]* 0xFF + Usart1Rxbuf[7]);
//					//水平
//					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, Usart1Rxbuf[8]* 0xFF + Usart1Rxbuf[9]);
//					//垂直
//					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, Usart1Rxbuf[10]* 0xFF + Usart1Rxbuf[11]);
				}
					
				
			}
		}
		else
		{
		  Usart1_Flag =0;
		}
		U1_last_last_last_data=U1_last_last_data;
		U1_last_last_data=U1_last_data;
		U1_last_data=temp;
		
		HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer2, RXBUFFERSIZE); //该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
