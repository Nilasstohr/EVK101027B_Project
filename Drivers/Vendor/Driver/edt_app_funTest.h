#ifndef __EDT_APP_FUNTEST_H
#define __EDT_APP_FUNTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Command types definition

typedef enum {
    CMD_TYPE_STRING = 0,    // String transmission command
    CMD_TYPE_FLASH_1_WRITE,   // Flash 1 write command
    CMD_TYPE_FLASH_1_READ,    // Flash 1 read command
    CMD_TYPE_FLASH_1_ERASE,   // Flash 1 erase command
    CMD_TYPE_FLASH_2_WRITE,   // Flash 2 write command
    CMD_TYPE_FLASH_2_READ,    // Flash 2 read command
    CMD_TYPE_FLASH_2_ERASE,   // Flash 2 erase command
    CMD_ID_CDC_DATA,          // CDC data command
    CMD_ID_CAN_DATA,           // CAN data command
    CMD_ID_RS485_DATA,         // RS485 data command
    CMD_SD_WRITE,          // SD card write command
    CMD_SD_READ,            // SD card read command
    CMD_SD_SHOW_IMAGE      // SD card image show command
} CommandType_t;

#define MAX_COMMAND_DATA_LEN 64

typedef struct {
    CommandType_t command;      // Command type
    uint8_t stringData[MAX_COMMAND_DATA_LEN]; // Buffer for string data (passed by value)
    uint8_t stringLength;     // Length of string data
} CommandData_t;

typedef struct
{
    CommandType_t cmdID; // Command ID
    char data[MAX_COMMAND_DATA_LEN]; // Data buffer (up to 64 bytes)
    uint8_t dataSize; // Size of the data in bytes
}MsgBox_TypeDef;

void StartFunTest(void *argument);

#ifdef __cplusplus
}
#endif

#endif /* __EDT_APP_FUNTEST_H */
