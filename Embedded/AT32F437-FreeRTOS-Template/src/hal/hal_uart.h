#ifndef HAL_UART_H
#define HAL_UART_H

/* Includes --------------------------------------------------------------------------------------*/
#include <stdint.h>
/* Define ----------------------------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------------*/
/* Exported typedef ------------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------------*/
void hal_uart_init(void);
uint16_t hal_uart_dma_get_dtcnt(void);
void hal_uart_send_data(const uint8_t *data, uint16_t len);
void hal_uart_dma_send_data(const uint8_t *data, uint16_t len);

#endif /* HAL_UART_H */
