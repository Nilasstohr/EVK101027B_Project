#include "cmsis_os2.h"
#include "usbd_cdc_if.h"
#include <stdio.h>
#include <string.h>
#include "edt_app_funTest.h"

extern osMessageQueueId_t QfunRxHandle;

int _write(int file, char *ptr, int len);

void StartFunTest(void *argument)
{
    for(;;)
    {
        CommandData_t rxCommand;
        osStatus_t status = osMessageQueueGet(QfunRxHandle, &rxCommand, NULL, 10); // 10ms timeout
        if(status == osOK){
        	if(rxCommand.command==CMD_TYPE_STRING){
        		_write(1, rxCommand.stringData, rxCommand.stringLength);
        	}
        }
        osDelay(500);
    }
}

int _write(int file, char *ptr, int len)
{
  /* Ignore file descriptor, assuming stdout */
  (void)file;

  if (CDC_Transmit_HS((uint8_t *)ptr, len) == USBD_OK)
  {
    return len;
  }
  return -1;
}
