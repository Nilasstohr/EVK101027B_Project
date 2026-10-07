/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RTC_TS_LED_Pin GPIO_PIN_3
#define RTC_TS_LED_GPIO_Port GPIOF
#define EE_WC_Pin GPIO_PIN_2
#define EE_WC_GPIO_Port GPIOF
#define LCD_STBYB_Pin GPIO_PIN_14
#define LCD_STBYB_GPIO_Port GPIOE
#define CTP_RST_Pin GPIO_PIN_4
#define CTP_RST_GPIO_Port GPIOF
#define HS_PW_SW_Pin GPIO_PIN_2
#define HS_PW_SW_GPIO_Port GPIOM
#define CAN_STB_Pin GPIO_PIN_13
#define CAN_STB_GPIO_Port GPIOE
#define LCD_BL_EN_Pin GPIO_PIN_4
#define LCD_BL_EN_GPIO_Port GPIOD
#define LCD_RST_Pin GPIO_PIN_15
#define LCD_RST_GPIO_Port GPIOE
#define LCD_IO_CTRL_Pin GPIO_PIN_12
#define LCD_IO_CTRL_GPIO_Port GPIOE
#define SD_DETECT_Pin GPIO_PIN_6
#define SD_DETECT_GPIO_Port GPIOC
#define SD_DETECT_EXTI_IRQn EXTI6_IRQn
#define LCD_BL_PWM_Pin GPIO_PIN_7
#define LCD_BL_PWM_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
