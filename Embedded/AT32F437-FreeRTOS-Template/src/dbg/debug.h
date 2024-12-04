#ifndef DEBUG_H
#define DEBUG_H
/* Includes --------------------------------------------------------------------------------------*/
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

/* Define ----------------------------------------------------------------------------------------*/
#define LOG_LABLE_DEBUG "[D] "
/* Exported macro --------------------------------------------------------------------------------*/

/**
 * @brief 打印函数
 */
#define __PRINT(...) mlog(__VA_ARGS__)

/**
 * @brief 打印日志
 */
#define LOG_DEBUG(string, ...) \
    __PRINT(LOG_LABLE_DEBUG "%s(%d) %s: " string, __FILE__, __LINE__, __func__, __VA_ARGS__)

/* Exported typedef ------------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------------*/
extern const char *build_date;
extern const char *build_time;

/* Exported functions ----------------------------------------------------------------------------*/
void debug_init(void);
void mlog(char *fmt, ...);

#endif  // DEBUG_H
