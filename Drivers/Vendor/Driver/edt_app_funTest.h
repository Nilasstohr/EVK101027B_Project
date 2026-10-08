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
    char stringData[MAX_COMMAND_DATA_LEN]; // Buffer for string data (passed by value)
    uint8_t stringLength;     // Length of string data
} CommandData_t;

void StartFunTest(void *argument);
