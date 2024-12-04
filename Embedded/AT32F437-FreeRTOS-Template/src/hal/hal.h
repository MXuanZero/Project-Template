#ifndef HAL_H
#define HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Define ----------------------------------------------------------------------------------------*/
/* Includes --------------------------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "mcu.h"
#include "hal_systick.h"
#include "hal_uart.h"

void nvic_config(void);

#ifdef __cplusplus
}
#endif

#endif // HAL_H
