
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint16_t adcvalue[1];
const uint16_t sinus[300]= {0x800,0x82a,0x855,0x880,0x8ab,0x8d6,0x900,0x92b,
		0x955,0x97f,0x9a9,0x9d3,0x9fd,0xa26,0xa4f,0xa78,
		0xaa1,0xac9,0xaf1,0xb19,0xb40,0xb67,0xb8e,0xbb4,
		0xbda,0xbff,0xc24,0xc49,0xc6d,0xc90,0xcb3,0xcd5,
		0xcf7,0xd19,0xd39,0xd5a,0xd79,0xd98,0xdb6,0xdd4,
		0xdf1,0xe0d,0xe29,0xe44,0xe5e,0xe78,0xe91,0xea9,
		0xec0,0xed7,0xeed,0xf02,0xf16,0xf29,0xf3c,0xf4e,
		0xf5f,0xf6f,0xf7f,0xf8d,0xf9b,0xfa8,0xfb4,0xfbf,
		0xfc9,0xfd2,0xfdb,0xfe2,0xfe9,0xfef,0xff4,0xff8,
		0xffb,0xffd,0xfff,0xfff,0xfff,0xffd,0xffb,0xff8,
		0xff4,0xfef,0xfe9,0xfe2,0xfdb,0xfd2,0xfc9,0xfbf,
		0xfb4,0xfa8,0xf9b,0xf8d,0xf7f,0xf6f,0xf5f,0xf4e,
		0xf3c,0xf29,0xf16,0xf02,0xeed,0xed7,0xec0,0xea9,
		0xe91,0xe78,0xe5e,0xe44,0xe29,0xe0d,0xdf1,0xdd4,
		0xdb6,0xd98,0xd79,0xd5a,0xd39,0xd19,0xcf7,0xcd5,
		0xcb3,0xc90,0xc6d,0xc49,0xc24,0xbff,0xbda,0xbb4,
		0xb8e,0xb67,0xb40,0xb19,0xaf1,0xac9,0xaa1,0xa78,
		0xa4f,0xa26,0x9fd,0x9d3,0x9a9,0x97f,0x955,0x92b,
		0x900,0x8d6,0x8ab,0x880,0x855,0x82a,0x800,0x7d5,
		0x7aa,0x77f,0x754,0x729,0x6ff,0x6d4,0x6aa,0x680,
		0x656,0x62c,0x602,0x5d9,0x5b0,0x587,0x55e,0x536,
		0x50e,0x4e6,0x4bf,0x498,0x471,0x44b,0x425,0x400,
		0x3db,0x3b6,0x392,0x36f,0x34c,0x32a,0x308,0x2e6,
		0x2c6,0x2a5,0x286,0x267,0x249,0x22b,0x20e,0x1f2,
		0x1d6,0x1bb,0x1a1,0x187,0x16e,0x156,0x13f,0x128,
		0x112,0xfd,0xe9,0xd6,0xc3,0xb1,0xa0,0x90,
		0x80,0x72,0x64,0x57,0x4b,0x40,0x36,0x2d,
		0x24,0x1d,0x16,0x10,0xb,0x7,0x4,0x2,
		0x0,0x0,0x0,0x2,0x4,0x7,0xb,0x10,
		0x16,0x1d,0x24,0x2d,0x36,0x40,0x4b,0x57,
		0x64,0x72,0x80,0x90,0xa0,0xb1,0xc3,0xd6,
		0xe9,0xfd,0x112,0x128,0x13f,0x156,0x16e,0x187,
		0x1a1,0x1bb,0x1d6,0x1f2,0x20e,0x22b,0x249,0x267,
		0x286,0x2a5,0x2c6,0x2e6,0x308,0x32a,0x34c,0x36f,
		0x392,0x3b6,0x3db,0x400,0x425,0x44b,0x471,0x498,
		0x4bf,0x4e6,0x50e,0x536,0x55e,0x587,0x5b0,0x5d9,
		0x602,0x62c,0x656,0x680,0x6aa,0x6d4,0x6ff,0x729,
		0x754,0x77f,0x7aa,0x7d5};




const uint16_t triangle[298]= {0x1b,0x37,0x52,0x6d,0x89,0xa4,0xbf,0xda,
0xf6,0x111,0x12c,0x148,0x163,0x17e,0x19a,0x1b5,
0x1d0,0x1eb,0x207,0x222,0x23d,0x259,0x274,0x28f,
0x2ab,0x2c6,0x2e1,0x2fc,0x318,0x333,0x34e,0x36a,
0x385,0x3a0,0x3bb,0x3d7,0x3f2,0x40d,0x429,0x444,
0x45f,0x47b,0x496,0x4b1,0x4cd,0x4e8,0x503,0x51e,
0x53a,0x555,0x570,0x58c,0x5a7,0x5c2,0x5de,0x5f9,
0x614,0x62f,0x64b,0x666,0x681,0x69d,0x6b8,0x6d3,
0x6ef,0x70a,0x725,0x740,0x75c,0x777,0x792,0x7ae,
0x7c9,0x7e4,0x800,0x81b,0x836,0x851,0x86d,0x888,
0x8a3,0x8bf,0x8da,0x8f5,0x911,0x92c,0x947,0x962,
0x97e,0x999,0x9b4,0x9d0,0x9eb,0xa06,0xa22,0xa3d,
0xa58,0xa73,0xa8f,0xaaa,0xac5,0xae1,0xafc,0xb17,
0xb33,0xb4e,0xb69,0xb84,0xba0,0xbbb,0xbd6,0xbf2,
0xc0d,0xc28,0xc44,0xc5f,0xc7a,0xc95,0xcb1,0xccc,
0xce7,0xd03,0xd1e,0xd39,0xd55,0xd70,0xd8b,0xda6,
0xdc2,0xddd,0xdf8,0xe14,0xe2f,0xe4a,0xe66,0xe81,
0xe9c,0xeb7,0xed3,0xeee,0xf09,0xf25,0xf40,0xf5b,
0xf77,0xf92,0xfad,0xfc8,0xfe4,0xfff,0xfe4,0xfc8,
0xfad,0xf92,0xf77,0xf5b,0xf40,0xf25,0xf09,0xeee,
0xed3,0xeb7,0xe9c,0xe81,0xe66,0xe4a,0xe2f,0xe14,
0xdf8,0xddd,0xdc2,0xda6,0xd8b,0xd70,0xd55,0xd39,
0xd1e,0xd03,0xce7,0xccc,0xcb1,0xc95,0xc7a,0xc5f,
0xc44,0xc28,0xc0d,0xbf2,0xbd6,0xbbb,0xba0,0xb84,
0xb69,0xb4e,0xb33,0xb17,0xafc,0xae1,0xac5,0xaaa,
0xa8f,0xa73,0xa58,0xa3d,0xa22,0xa06,0x9eb,0x9d0,
0x9b4,0x999,0x97e,0x962,0x947,0x92c,0x911,0x8f5,
0x8da,0x8bf,0x8a3,0x888,0x86d,0x851,0x836,0x81b,
0x800,0x7e4,0x7c9,0x7ae,0x792,0x777,0x75c,0x740,
0x725,0x70a,0x6ef,0x6d3,0x6b8,0x69d,0x681,0x666,
0x64b,0x62f,0x614,0x5f9,0x5de,0x5c2,0x5a7,0x58c,
0x570,0x555,0x53a,0x51e,0x503,0x4e8,0x4cd,0x4b1,
0x496,0x47b,0x45f,0x444,0x429,0x40d,0x3f2,0x3d7,
0x3bc,0x3a0,0x385,0x36a,0x34e,0x333,0x318,0x2fc,
0x2e1,0x2c6,0x2ab,0x28f,0x274,0x259,0x23d,0x222,
0x207,0x1eb,0x1d0,0x1b5,0x19a,0x17e,0x163,0x148,
0x12c,0x111,0xf6,0xda,0xbf,0xa4,0x89,0x6d,
0x52,0x37};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM6_Init(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_DAC_Init();
  MX_TIM6_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */

  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcvalue,1);
  HAL_TIM_Base_Start(&htim6);
 // HAL_DAC_Start(&hdac,DAC1_CHANNEL_1);
  HAL_DAC_Start_DMA(&hdac,DAC1_CHANNEL_1,(uint32_t*)sinus,300,DAC_ALIGN_12B_R);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM6_DAC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* DAC init function */
static void MX_DAC_Init(void)
{

  DAC_ChannelConfTypeDef sConfig;

    /**DAC Initialization 
    */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**DAC channel OUT1 config 
    */
  sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM6 init function */
static void MX_TIM6_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 83;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 999;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
