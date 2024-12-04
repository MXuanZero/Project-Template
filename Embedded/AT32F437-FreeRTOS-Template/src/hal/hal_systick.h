#ifndef HAL_SYSTICK_H
#define HAL_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------------*/
#include <stdint.h>
#include "stdbool.h"
/* Define ----------------------------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------------*/
/* Exported typedef ------------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------------*/

void hal_systick_init(void);
void hal_systick_set_it(bool state);
void hal_delay_ms(uint16_t ms);
void hal_delay_us(uint16_t us);
uint32_t hal_get_ms(void);
uint32_t hal_get_us(void);
void hal_systick_update(void);
#ifdef __cplusplus
}
#endif

#endif // HAL_SYSTICK_H
