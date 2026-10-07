/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.22.1. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
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

/* USER CODE BEGIN STM32TouchController */
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/Types.hpp>
#include <STM32TouchController.hpp>
#include "main.h"

volatile bool doSampleTouch = false;

extern "C" I2C_HandleTypeDef hi2c1;

using namespace touchgfx;
extern "C"
{

#include "edt_bsp_ctp.h"
}

void STM32TouchController::init()
{

	  if( EDT_TS_Init( EDT_LCD_GetXSize(), EDT_LCD_GetYSize()) == TS_OK) {
	    isInitialized = true;
	  }
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{

	 TS_StateTypeDef state = { 0 };
	  if (isInitialized) {
	    EDT_TS_GetState(&state);
	    if (state.touchDetected) {
	      x = state.touchX[0];
	      y = state.touchY[0];

	      return true;
	    }
	  }
	  return false;
}
/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
