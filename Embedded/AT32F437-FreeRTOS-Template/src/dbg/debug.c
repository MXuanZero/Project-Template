/* Includes --------------------------------------------------------------------------------------*/
#include "debug.h"
#include "mcu.h"
#include <stdio.h>
#include <stdarg.h>
#include "hal_uart.h"
/* Private define --------------------------------------------------------------------------------*/
#define DEF_LOG_BUF_SIZE 128
/* Private macro ---------------------------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------------*/
const char *build_date = __DATE__;
const char *build_time = __TIME__;
static char buf[DEF_LOG_BUF_SIZE];
/* Private functions -----------------------------------------------------------------------------*/

void debug_init(void)
{

}

void mlog(char *fmt, ...)
{
	int len = 0;
	va_list args;
	va_start(args, fmt);
	len += vsnprintf(buf, DEF_LOG_BUF_SIZE, fmt, args);
	va_end(args);
	hal_uart_send_data((uint8_t *)buf, len);
}
