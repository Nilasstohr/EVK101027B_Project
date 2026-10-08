#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
extern "C"
{
#include <string.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include "edt_app_funTest.h"

//extern osMessageQueueId_t QfunTxHandle;
extern osMessageQueueId_t QfunRxHandle;
//extern osMessageQueueId_t UICMDQueueHandle;
//extern osMessageQueueId_t TouchGFXQueueHandle;

}
#endif

#ifndef SIMULATOR
CommandData_t cmdData;
#endif


Model::Model() : modelListener(0)
{

}

void Model::tick()
{

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
