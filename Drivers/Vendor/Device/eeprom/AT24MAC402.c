/**
  ******************************************************************************
  * File Name          : AT24MAC402.c
  * @author            : EDT Embedded Application Team
  * Description        : This file provides code for the configuration
  *                      of the I2C instances To eeprom.
  * @version           : V1.0.0
  * @date              : 3-Aug-2023
  * @brief             : EDT <https://smartembeddeddisplay.com/>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2023 EDT</center></h2>
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
#include "eeprom/AT24MAC402.h"
#include "i2c.h"


static HAL_StatusTypeDef EE_AT24MAC402_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,  uint8_t *pData, uint16_t Size);
/*****************************************************************************
  * @brief I2C AT24MAC402 read Mac address function
  *
  * @param Handle       : EEROMI2cHandle pointer
  *        MacAddrbuf   : I2C receiver Data pointer
  * @retval             : HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef Read_AT24MAC402_Mac(I2C_HandleTypeDef *hi2c, uint8_t MacAddrbuf[EEPROM_Mac_Length])
{
  HAL_StatusTypeDef err ;
//   err = HAL_I2C_Mem_Read(hi2c, 0xB0, 0x9A, I2C_MEMADD_SIZE_8BIT, MacAddrbuf, EEPROM_Mac_Length, 100); 
  err = HAL_I2C_Mem_Read(hi2c, 0xB0, 0x9A, I2C_MEMADD_SIZE_8BIT, MacAddrbuf, 0x06, 100);

  return err;
}
/*****************************************************************************
  * @brief I2C AT24MAC402 read serial number function
  * the serial number address range 80h - 8Fh
  * @param Handle       : EEROMI2cHandle pointer
  *        MacAddrbuf   : I2C receiver Data pointer
  * @retval             : HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef Read_AT24MAC402_Serial(I2C_HandleTypeDef *hi2c, uint8_t Serialbuf[EEPROM_Serial_Length])
{
  HAL_StatusTypeDef err ;

  err = HAL_I2C_Mem_Read(hi2c, AT24MAC402_Exten_Adderss, EEPROM_Serial_Address, I2C_MEMADD_SIZE_8BIT, Serialbuf, EEPROM_Serial_Length, 100);

  return err;
}
/*****************************************************************************
  * @brief I2C AT24MAC402 read sigle byte
  *
  * @param Handle       : EEROMI2cHandle pointer
  *        address      : I2C receiver Data pointer
  *        buf          : I2C receiver Data buffer
  * @retval             : HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef Read_AT24MAC402_Byte(I2C_HandleTypeDef *hi2c, uint8_t address, uint8_t *buf)
{
  HAL_StatusTypeDef err ;

  err = HAL_I2C_Mem_Read(hi2c, AT24MAC402_Main_Adderss, address, I2C_MEMADD_SIZE_8BIT, buf, 1, 100);

  return err;
}
/*****************************************************************************
  * @brief I2C AT24MAC402 read mulit bytes
  *
  * @param Handle       : EEROMI2cHandle pointer
  *        address      : I2C receiver Data pointer
  *        buf          : I2C receiver Data buffer
  *        size         : I2C receiver Data size
  * @retval             : HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef Read_AT24MAC402_Multi_Byte(I2C_HandleTypeDef *hi2c, uint8_t address, uint8_t *buf, uint8_t size)
{
  HAL_StatusTypeDef err ;

  err = HAL_I2C_Mem_Read(hi2c, AT24MAC402_Main_Adderss, address, I2C_MEMADD_SIZE_8BIT, buf, size, 100);

  return err;

}
/*****************************************************************************
  * @brief I2C AT24MAC402 write sigle byte
  *
  * @param Handle       : EEROMI2cHandle pointer
  *        address      : I2C receiver Data pointer
  *        buf          : I2C receiver Data buffer
  * @retval             : HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef Write_AT24MAC402_Byte(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData)
{
  HAL_StatusTypeDef err ;
  err = EE_AT24MAC402_Write(hi2c, DevAddress, pData, 1);
  return err;

}
/*****************************************************************************
  * @brief I2C AT24MAC402 write mulit bytes
  *
  * @param Handle       : EEROMI2cHandle pointer
  *        address      : I2C receiver Data pointer
  *        buf          : I2C receiver Data buffer
  *        size         : I2C receiver Data size
  * @retval             : HAL_StatusTypeDef
******************************************************************************/
HAL_StatusTypeDef Write_AT24MAC402_Multi_Byte(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t size)
{
  HAL_StatusTypeDef err ;
  err = EE_AT24MAC402_Write(hi2c, DevAddress, pData, size);
  return err;
}

static HAL_StatusTypeDef EE_AT24MAC402_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,  uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef err ;
  HAL_GPIO_WritePin(EE_WC_GPIO_Port, EE_WC_Pin, GPIO_PIN_RESET);

  err = HAL_I2C_Mem_Write(hi2c, AT24MAC402_Main_Adderss, DevAddress, I2C_MEMADD_SIZE_8BIT, pData,  Size, 100);
  osDelay(10);
  HAL_GPIO_WritePin(EE_WC_GPIO_Port, EE_WC_Pin, GPIO_PIN_SET);
  return err;
}

/************************ (C) COPYRIGHT EDT *****END OF FILE****/
