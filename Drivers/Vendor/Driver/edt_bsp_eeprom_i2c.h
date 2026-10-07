/**
  ******************************************************************************  
  * File Name          : edt_h7xx_eerom_i2c.h
  * @author            : EDT Embedded Application Team
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  * @version           : V1.1.0
  * @date              : 24-Dec-2024
  * @brief             : EDT <https://www.edtc.com/>
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 EDT</center></h2>
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
#ifndef __EDT_H7XX_EEROM_I2C_H
#define __EDT_H7XX_EEROM_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif   
   
/* Includes ------------------------------------------------------------------*/
#include "main.h"

   /* EEPRON I2C address */
#define EEPROMAdderss    0xA2

void EDT_EEROM_I2Cx_Init(I2C_HandleTypeDef *EEI2c) ;

uint8_t EE_Read_Byte(void);
void EE_Write_Byte(uint8_t value);

uint32_t EE_returnCount(void);
void EE_Write_Count();
void EEP_clean();

#ifdef __cplusplus
}
#endif

#endif /* __EDT_H7XX_I2C_H */

/************************ (C) COPYRIGHT EDT *****END OF FILE****/
