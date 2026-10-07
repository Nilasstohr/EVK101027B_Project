/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
static uint32_t PinDetect = {SD_DETECT_Pin};
static GPIO_TypeDef* SD_GPIO_PORT = {SD_DETECT_GPIO_Port};
volatile uint8_t sd_status = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

static uint8_t SD_IsDetected(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void MX_FATFS_Init(void)
{
  /* USER CODE BEGIN Init */
  /* additional user code for init */
  /*## FatFS: Link the disk I/O driver(s)  ###########################*/

  /* USER CODE END Init */
}

/* USER CODE BEGIN Application */
/**
  * @brief  Start task
  * @param  pvParameters not used
  * @retval None
  */

/**
  * @brief  Check whether the SD card is detected.
  * @retval 1: SD card is detected
  * @retval 0: SD card is not detected
  */
static uint8_t SD_IsDetected(void)
{
    uint8_t status;

    if (HAL_GPIO_ReadPin(SD_GPIO_PORT, PinDetect) == GPIO_PIN_RESET)
    {
      status = 1;
    }
    else
    {
      status = 0;
    }
      return status;
}

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin: Specifies the GPIO pin connected to the EXTI line.
  * @note   This callback is used to update the SD card detection status
  *         when the SD detect pin interrupt occurs.
  * @retval None
  */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == SD_DETECT_Pin)
  {
	  sd_status = SD_IsDetected();
  }
}
/* USER CODE END Application */
