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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT24MAC402_H
#define __AT24MAC402_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

   /* EEPRON I2C address */
#define EEPROMAdderss    0xA0
#define AT24MAC402_Main_Adderss    0xA0
#define AT24MAC402_Exten_Adderss   0xB0
#define EEPROM_Serial_Address  0x80
#define EEPROM_Serial_Length   0x10
#define EEPROM_Mac_Address  0x9A
   
#define EEPROM_Mac_Length   0x06

void READ_MAC_ADDRESS(void);
HAL_StatusTypeDef Read_AT24MAC402_Mac(I2C_HandleTypeDef *hi2c, uint8_t MacAddrbuf[EEPROM_Mac_Length]);
HAL_StatusTypeDef Read_AT24MAC402_Serial(I2C_HandleTypeDef *hi2c, uint8_t Serialbuf[EEPROM_Serial_Length]);
HAL_StatusTypeDef Read_AT24MAC402_Byte(I2C_HandleTypeDef *hi2c, uint8_t address, uint8_t *buf);
HAL_StatusTypeDef Read_AT24MAC402_Multi_Byte(I2C_HandleTypeDef *hi2c, uint8_t address, uint8_t *buf, uint8_t size);

HAL_StatusTypeDef Write_AT24MAC402_Byte(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData);
HAL_StatusTypeDef Write_AT24MAC402_Multi_Byte(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* __AT24MAC402_H */

/************************ (C) COPYRIGHT EDT *****END OF FILE****/
