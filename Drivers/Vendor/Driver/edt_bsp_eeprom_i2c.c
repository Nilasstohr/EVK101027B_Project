/**
  ******************************************************************************  
  * File Name          : edt_h7xx_eerom_i2c.c
  * @author            : EDT Embedded Application Team
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  * @version           : V1.1.0
  * @date              : 24-Dec-2024
  * @brief             : EDT <https://www.edtc.com/>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2024 EDT</center></h2>
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
#include "edt_bsp_eeprom_i2c.h"

#if defined(USE_EEROM_I2C)   
I2C_HandleTypeDef *EEROMI2cHandle;

static int32_t EE_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
static int32_t EE_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

/**
  * @brief  Initializes I2C HAL.
  * @param  i2c_handler : EEROMI2cHandle
  * @retval None
  */
/*****************************************************************************
  * @brief  EEROM I2C2 Initial
  * @param  
  * @retval None
******************************************************************************/
void EDT_EEROM_I2Cx_Init(I2C_HandleTypeDef *EEI2c) 
{ 
/*##-1- Configure the I2C peripheral ######################################*/
EEROMI2cHandle = EEI2c ; 
}

/*****************************************************************************
  * @ For example: ONE Byte data to EEPROM
  * @param
  * @retval None
******************************************************************************/

/* read function from EEPROM */
uint8_t EE_Read_Byte(void)
{
  uint8_t buf[1]={0};
    EE_Read(EEROMI2cHandle,0,buf,1);
    return buf[0];
}

void EE_Write_Byte(uint8_t value)
{
  uint8_t buf[1]={0};
  buf[0]=value;
  EE_Write(EEROMI2cHandle,0,buf,1);

}

/*****************************************************************************
  * @ For example: setting 3 Bytes data to EEPROM (read and write)
  *   Count presses (the maximum number is about ff ff ff =16,777,215)
  * @param
  * @retval None
******************************************************************************/
uint32_t EE_returnCount()
{
  uint8_t buf[3]={0};
    EE_Read(EEROMI2cHandle,0,buf,3);
    uint32_t EEPROMcountRead= ((uint32_t) buf[2]<<16 )+((uint32_t) buf[1]<<8) + ((uint32_t) buf[0]);
    return EEPROMcountRead;
}

/* write function to EEPROM */
void EE_Write_Count()
{
     uint8_t buf[3];

    /*read the EEPROM data */
    uint32_t EEPROMcount=EE_returnCount();

     uint8_t EEPROMcountByte1=EEPROMcount;
     uint8_t EEPROMcountByte2= EEPROMcount >> 8;
     uint8_t EEPROMcountByte3= EEPROMcount >> 16;


      /* Recounnt when EEPROM has been programmed over 16777215 times   */
      if( (EEPROMcountByte1==255) && (EEPROMcountByte2==255)&& (EEPROMcountByte3==255))
          {
             EEPROMcountByte3=0;
             EEPROMcountByte2=0;
             EEPROMcountByte1=0;
          }
      /*  *******************************/

        if((EEPROMcountByte2 == 255)&&(EEPROMcountByte1 == 255))
         {
            EEPROMcountByte3++;
            EEPROMcountByte2=255;
         }

      if(EEPROMcountByte1 == 255)
         {
            EEPROMcountByte2++;
            EEPROMcountByte1=255;
         }

            EEPROMcountByte1++;

        buf[0] = EEPROMcountByte1;
        buf[1] = EEPROMcountByte2;
        buf[2] = EEPROMcountByte3;

        EE_Write(EEROMI2cHandle,0,buf,3);
}

void EEP_clean()
{
	uint8_t buf[3];

	 buf[0] = 255; // FF
	 buf[1] = 255; // FF
	 buf[2] = 255; // FF

	        EE_Write(EEROMI2cHandle,0,buf,3);

}
/*****************************************************************************
  *  * @brief I2C EEROM USED Read function 
  *        
  * @param Handle         : EEROMI2cHandle pointer
  *        DevAddress   : I2C EEPROMAdderss
  *        pdata        : I2C Tramsmite Data pointer
  *        Size         : I2C Tramsmite Data Length Max:8
  *        Timeout      : I2C Tramsmite wait time out
  * @retval             HAL_StatusTypeDef
******************************************************************************/
static int32_t EE_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  
  HAL_I2C_Mem_Read(hi2c, EEPROMAdderss, DevAddress, I2C_MEMADD_SIZE_8BIT, pData,  Size, 100);  

  return 0;
}
/*****************************************************************************
  *  * @brief I2C EEROM USED write function 
  *        
  * @param Handle         : EEROMI2cHandle pointer
  *        DevAddress   : I2C EEPROMAdderss
  *        pdata        : I2C Tramsmite Data pointer
  *        Size         : I2C Tramsmite Data Length Max:8
  *        Timeout      : I2C Tramsmite wait time out
  * @retval             HAL_StatusTypeDef
******************************************************************************/
static int32_t EE_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  HAL_GPIO_WritePin(EEP_WC_GPIO_Port, EEP_WC_Pin, GPIO_PIN_RESET);
  
  HAL_I2C_Mem_Write(hi2c, EEPROMAdderss, DevAddress, I2C_MEMADD_SIZE_8BIT, pData,  Size, 100);  

  osDelay(10);
   HAL_GPIO_WritePin(EEP_WC_GPIO_Port, EEP_WC_Pin, GPIO_PIN_SET);
  return 0;
}
#endif

/************************ (C) COPYRIGHT EDT *****END OF FILE****/
