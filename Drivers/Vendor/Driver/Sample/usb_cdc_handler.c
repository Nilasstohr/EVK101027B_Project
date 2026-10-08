/**
  ******************************************************************************  
  * File Name          : usb_cdc_handler.c
  * @author            : EDT Embedded Application Team
  * Description        : This file provides sample usb cdc queue handling
  *                      embedded display board. 
  * @brief             : EDT <https://www.edtc.com/>
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT(c) 2020 Emerging Display Technologies Corp.
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
#include <string.h>
#include "usbd_cdc_if.h"
#include "edt_app_funTest.h"
#include "usb_cdc_handler.h"

extern osMessageQueueId_t QfunRxHandle;
extern osMessageQueueId_t QfunTxHandle;

static int _write(char *ptr, int len);
static char txBuf[65];

void handle_usb_cdc_transmit_to_host(CommandData_t *rxCommand){
	// Copy data to a persistent buffer before the asynchronous USB transmit
	_write(rxCommand->stringData, rxCommand->stringLength);
}

bool handle_usb_cdc_received_from_host(void){
	static MsgBox_TypeDef mbx;
	osStatus_t status;
	if(USBCDCHandleSt.CDC_HandleDataEn == true){
		// Copy the actual string data to send via QfunTxHandle
		mbx.dataSize = USBCDCHandleSt.CDC_HandleDataSize;
		if(mbx.dataSize > 64)
			mbx.dataSize = 64; // Limit to buffer size
		if (mbx.dataSize > sizeof(mbx.data) - 1){
			mbx.dataSize = sizeof(mbx.data) - 1;
		}
		memcpy(mbx.data, USBCDCHandleSt.CDC_HandleData, mbx.dataSize);
		mbx.data[mbx.dataSize] = '\0'; // Null terminate within bounds
		mbx.cmdID = CMD_ID_CDC_DATA; // Command ID for CDC data
		// Send the actual string data to QfunTxHandle
		status = osMessageQueuePut(QfunTxHandle, &mbx, 0, 0);
		if(status == osOK){
			// Clear flag after successful transmission
			USBCDCHandleSt.CDC_HandleDataEn = false;
		}
		memcpy(txBuf, mbx.data, mbx.dataSize); //
		_write(txBuf, mbx.dataSize);
		return true;
	}
	return false;
}

static int _write(char *ptr, int len)
{
  if (CDC_Transmit_HS((uint8_t *)ptr, len) == USBD_OK)
  {
    return len;
  }
  return -1;
}

 /*******(C) COPYRIGHT Emerging Display Technologies Corp. **** END OF FILE ***/

