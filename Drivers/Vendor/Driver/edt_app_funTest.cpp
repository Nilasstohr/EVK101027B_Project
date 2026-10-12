#include "cmsis_os2.h"
#include <stdio.h>
#include "edt_app_funTest.h"
#include "Sample/usb_cdc_handler.h"
#include "Sample/cpp_test.hpp"

extern osMessageQueueId_t QfunRxHandle;
extern osMessageQueueId_t QfunTxHandle;

void StartFunTest(void *argument)
{
	Counter a = Counter();

	osStatus_t status;
	for(;;)
    {
		// check if there is data to transmit from host
		// (external device connected to smart embedded screen)
		handle_usb_cdc_received_from_host();

		// check if there is data to transmit from SE to host
		CommandData_t rxCommand;
		status = osMessageQueueGet(QfunRxHandle, &rxCommand, NULL, 500); // 10ms timeout
		if(status == osOK)
		{
			switch(rxCommand.command){
				case CMD_TYPE_STRING:{
					a.increment(); // C++ object: count string commands
					handle_usb_cdc_transmit_to_host(&rxCommand);
					break;
				}
				default:
					break;
			}
		}
        osDelay(1);
    }
}
