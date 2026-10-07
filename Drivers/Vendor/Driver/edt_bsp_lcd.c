/**
  ******************************************************************************  
  * File Name          : edt_bsp_lcd.c
  * @author            : EDT Embedded Application Team
  * Description        : This file includes the driver for LCD/TFT module on
  *                      smart embedded display board.
  * @brief             : EDT <https://www.edtc.com/>
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT(c) 2024 Emerging Display Technologies Corp.
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Emerging Display Technologies Corp. nor the names of 
  *      its contributors may be used to endorse or promote products derived from 
  *      this software without specific prior written permission.
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
#include "edt_bsp_lcd.h"

/*******LCD Sleep function*****/
LCD_StructDef LCD = {.width = TFT_WIDTH, .height = TFT_HEIGHT, .lcdstate = false};
uint16_t Sleep_cunter=0;
uint16_t Sleep_Time=180;
static bool SleepDetected;
extern osThreadId_t LCDSleepTaskHandle;

/*************************************************************
  * @brief  Initializes the LCD layer in RGB565 format (16 bits per pixel) or 
            RGB888(24 bits per pixel) depending on definitionof USE_BPP
  * @param  LayerIndex: Layer foreground or background
  * @param  FB_Address: Layer frame buffer
  * @retval None
***************************************************************/
void EDT_LCD_LayerInit(uint16_t LayerIndex, uint32_t FB_Address)
{
    LCD_LayerCfgTypeDef  layer_cfg;
   
    /* Layer Init */
    layer_cfg.WindowX0 = 0;
    layer_cfg.WindowX1 = EDT_LCD_GetXSize();
    layer_cfg.WindowY0 = 0;
    layer_cfg.WindowY1 = EDT_LCD_GetYSize();

    layer_cfg.FBStartAdress = FB_Address;
    layer_cfg.Alpha = 255;
    layer_cfg.Alpha0 = 0;
    layer_cfg.Backcolor.Blue = 0x0;
    layer_cfg.Backcolor.Green = 0;
    layer_cfg.Backcolor.Red = 0;
    layer_cfg.ImageWidth  = EDT_LCD_GetXSize();
    layer_cfg.ImageHeight = EDT_LCD_GetYSize();
#if !defined(USE_BPP) || USE_BPP==16
    layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
    layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;

#elif USE_BPP==24
    layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
    layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
#else
#error Unknown USE_BPP
#endif
    HAL_LTDC_ConfigLayer(&hltdc, &layer_cfg, LayerIndex);    
}
/******************************************************************************
  * @brief  EDT_LCD_GetXSize
  * @param  NONE
  * @retval DISPLAY Width uint32_t
  * @note   EDT DISPLAY Get Width Size
*******************************************************************************/
uint32_t EDT_LCD_GetXSize(void)
{
    return LCD.width;
}
/******************************************************************************
  * @brief  EDT_LCD_GetYSize
  * @param  NONE
  * @retval DISPLAY Height uint32_t
  * @note   EDT DISPLAY Get Height Size
*******************************************************************************/
uint32_t EDT_LCD_GetYSize(void)
{
    return (uint32_t) LCD.height;
}
/******************************************************************************
  * @brief  EDT_LCD_SetSize
  * @param  NONE
  * @retval NONE
  * @note   EDT Set DISPLAY Size
*******************************************************************************/
void EDT_LCD_SetSize(LCD_StructDef * lcd, uint16_t width, uint16_t height)
{
  lcd->width = width;
  lcd->height = height;
}
/******************************************************************************
  * @brief  EDT_LCD_DisplayOn
  * @param  NONE
  * @retval NONE
  * @note   EDT DISPLAY ON Ctrl hltdc/ RESET PIN
*******************************************************************************/
void EDT_LCD_DisplayOn(void)
{

	HAL_Delay( 10);
	  HAL_GPIO_WritePin( LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET );
	HAL_Delay( 10);
//	  HAL_GPIO_WritePin( LCD_VCOM_CTRL_GPIO_Port, LCD_VCOM_CTRL_Pin, GPIO_PIN_SET );
//   HAL_Delay(20);
      HAL_GPIO_WritePin( LCD_IO_CTRL_GPIO_Port, LCD_IO_CTRL_Pin, GPIO_PIN_SET );
	HAL_Delay( 50 );
	  HAL_GPIO_WritePin( LCD_STBYB_GPIO_Port, LCD_STBYB_Pin, GPIO_PIN_SET );

	  HAL_Delay( 100 );


  EDT_LCD_BL_ON();
  EDT_LCD_SetDisplayStatus( true );

}
/******************************************************************************
  * @brief  EDT_LCD_DisplayOff
  * @param  NONE
  * @retval NONE
  * @note   EDT DISPLAY ON Ctrl hltdc/RESET PIN
*******************************************************************************/
void EDT_LCD_DisplayOff(void)
{
  EDT_LCD_BL_OFF();
  
//  HAL_GPIO_WritePin( LCD_VCOM_CTRL_GPIO_Port, LCD_VCOM_CTRL_Pin, GPIO_PIN_RESET );
  HAL_Delay( 10 );
 HAL_GPIO_WritePin( LCD_IO_CTRL_GPIO_Port, LCD_IO_CTRL_Pin, GPIO_PIN_RESET );
  HAL_Delay( 50 );
  HAL_GPIO_WritePin( LCD_STBYB_GPIO_Port, LCD_STBYB_Pin, GPIO_PIN_RESET );
  HAL_GPIO_WritePin( LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET );



  EDT_LCD_SetDisplayStatus( false );
  
}
/******************************************************************************
  * @brief  EDT_LCD_SetDisplayStatus
  * @param  lcdstatus  : true :display enabled / false :display disable
  * @retval NONE
  * @note   EDT DISPLAY ON Ctrl hltdc/RESET PIN
*******************************************************************************/
void EDT_LCD_SetDisplayStatus(bool lcdstatus)
{
  LCD.lcdstate = lcdstatus;
}
/******************************************************************************
  * @brief  EDT_LCD_DisplayOff
  * @param  NONE
  * @retval lcdstatus  : true :display enabled / false :display disable
  * @note   EDT DISPLAY ON Ctrl hltdc/RESET PIN
*******************************************************************************/
bool EDT_LCD_GetDisplayStatus(void)
{
 return LCD.lcdstate ;
}

/******************************************************************************
  * @brief  EDT_LCD_Reset
  * @param  NONE
  * @retval NONE
  * @note   EDT DISPLAY RESET Control PIN
*******************************************************************************/
void EDT_LCD_Reset(void)
{ 

//  HAL_GPIO_WritePin( LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET );
//  HAL_GPIO_WritePin( LCD_STBYB_GPIO_Port, LCD_STBYB_Pin, GPIO_PIN_RESET );
//  HAL_GPIO_WritePin( LCD_VCOM_CTRL_GPIO_Port, LCD_VCOM_CTRL_Pin, GPIO_PIN_RESET );
  HAL_GPIO_WritePin( LCD_IO_CTRL_GPIO_Port, LCD_IO_CTRL_Pin, GPIO_PIN_RESET );  
  osDelay( 10 );
  
//  HAL_GPIO_WritePin( LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET );
//  HAL_GPIO_WritePin( LCD_STBYB_GPIO_Port, LCD_STBYB_Pin, GPIO_PIN_SET );
  HAL_GPIO_WritePin( LCD_IO_CTRL_GPIO_Port, LCD_IO_CTRL_Pin, GPIO_PIN_SET );
  
   osDelay( 50 );  
  
  EDT_LCD_DisplayOn();
  EDT_LCD_SetDisplayStatus(true);
}
/*****************************************************************
  * @brief  Sleep Function
  * @param  
  * @param  
  * @retval None
  * @note   turn off  LCD display and backlight
*****************************************************************/
void StartLCDSleepTask(void * argument)
{
  while(1) {
    #if defined( USE_LCD_SleepFunction )  
      EDT_LCD_Sleep_Function();
    #endif
      osDelay( TEMP_REFRESH_PERIOD );
    }   
}
/************************************************/
void EDT_LCD_Sleep_Time(uint16_t value)
{
  Sleep_Time = value;
}
/************************************************/
void EDT_LCD_Sleep_Function(void)
{  
  Sleep_cunter++; 

  if ( Sleep_cunter >= Sleep_Time ) {
    if ( LCD.lcdstate == true ) {
      Sleep_cunter = 0;
      EDT_LCD_DisplayOff();
    }
    SleepDetected = true; 
  }

  if ( EDT_TS_GetDetected() ) {
    Sleep_cunter = 0;
    EDT_TS_SetDetected( false );
    if ( LCD.lcdstate == false ) {
      EDT_LCD_DisplayOn();   
    }
  } 
}

bool EDT_Sleep_GetDetected(void) 
{
  return  SleepDetected;
}

void EDT_Sleep_SetDetected(bool bl) 
{
  SleepDetected = bl;
}
/******************************************************************************
  * @brief  SuspendLCDSleepTask
  * @param
  * @param
  * @note   Stop LCDSleep Task
  * @retval Create Task For LCDSleep
*******************************************************************************/
void EDT_Sleep_SuspendLCDSleepTask(void)
{
	osThreadSuspend(LCDSleepTaskHandle);
    Sleep_cunter=0;
}
/******************************************************************************
  * @brief  ResumeLCDSleepTask
  * @param
  * @param
  * @note   Start LCDSleep Task
  * @retval Create Task For LCDSleep
*******************************************************************************/
void EDT_Sleep_ResumeLCDSleepTask(void)
{
	osThreadResume(LCDSleepTaskHandle);
    Sleep_cunter=0;
}

/****************************************************************************************
  * @brief  EDT_LCD_Clear
  * @param  hltdc  :LTDC_HandleTypeDef hltdc
  * @param  Color  :uint32_t  0xFFFFFFFF
  * @retval NONE
  * @note   
****************************************************************************************/
//void EDT_LCD_Clear(LTDC_HandleTypeDef *hltdc , uint32_t Color)
//{
////  EDT_LL_FillBuffer(hltdc,0, (uint32_t *)(hltdc->LayerCfg[0].FBStartAdress), EDT_LCD_GetXSize(), EDT_LCD_GetYSize(), 0, Color);
//}

 /*******(C) COPYRIGHT Emerging Display Technologies Corp. **** END OF FILE ***/
