#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
extern "C"
{
#include <string.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include "edt_app_funTest.h"

extern osMessageQueueId_t QfunTxHandle;
extern osMessageQueueId_t QfunRxHandle;
//extern osMessageQueueId_t UICMDQueueHandle;
//extern osMessageQueueId_t TouchGFXQueueHandle;

}
MsgBox_TypeDef msg;

#endif

#ifndef SIMULATOR
CommandData_t cmdData;
#endif


Model::Model() : modelListener(0)
{
  
}

void Model::tick()
{
#ifndef SIMULATOR
    memset(&msg, 0, sizeof(msg));
    char receivedString[65]; // Buffer for received string (64 chars + null terminator)
    osStatus_t status = osMessageQueueGet(QfunTxHandle, &msg, NULL, 10); // Non-blocking check
	if (status == osOK && modelListener)
	{
        // Copy received string to buffer (clip to fit the local buffer)
        size_t n2 = msg.dataSize;
        if (n2 > sizeof(receivedString) - 1) n2 = sizeof(receivedString) - 1;
        memcpy(receivedString, msg.data, n2);
        receivedString[n2] = '\0';
        // Regular CDC data, send to CDC_RX field
        modelListener->notifyUsbDataReceived(receivedString);
	}
#endif
}

void Model::sendCDCData(const char* data)
{
#ifndef SIMULATOR
    // Setup command structure
    cmdData.command = CMD_TYPE_STRING;

    // Copy data to the command structure, handling potential truncation
    size_t data_len = strlen(data);
    cmdData.stringLength = (data_len > MAX_COMMAND_DATA_LEN) ? MAX_COMMAND_DATA_LEN : data_len;
    memcpy(cmdData.stringData, data, ++cmdData.stringLength);	//including the EOF('\0')

    // Send command structure to QfunRxHandle
    // The entire struct, including the data array, is copied into the queue.
    osStatus_t status = osMessageQueuePut(QfunRxHandle, &cmdData, 0, 0);
    if (status != osOK)
    {
        // Handle error if needed
    }
#endif

}
