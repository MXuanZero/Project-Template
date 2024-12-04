/* Includes --------------------------------------------------------------------------------------*/
#include "hal_uart.h"
#include "mcu.h"
#include <string.h>
/* Private define --------------------------------------------------------------------------------*/
#define UART USART1
#define UART_CRM_CLK CRM_USART1_PERIPH_CLOCK
#define UART_TX_PIN GPIO_PINS_9
#define UART_RX_PIN GPIO_PINS_10
#define UART_GPIO GPIOA
#define UART_GPIO_CRM_CLK CRM_GPIOA_PERIPH_CLOCK
#define UART_PIN_SOURCE GPIO_PINS_SOURCE9
#define UART_PIN_MUX_NUM GPIO_MUX_7

#define UART_TX_DMA DMA1_CHANNEL1
#define UART_TX_DMA_CRM_CLK CRM_DMA1_PERIPH_CLOCK
/* Private macro ---------------------------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------------*/
void hal_uart_init(void)
{
	/* uart gpio */
	gpio_init_type gpio_init_struct;

	crm_periph_clock_enable(UART_GPIO_CRM_CLK, TRUE);
	gpio_default_para_init(&gpio_init_struct);
	gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
	gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
	gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
	gpio_init_struct.gpio_pins = UART_TX_PIN | UART_RX_PIN;
	gpio_init(UART_GPIO, &gpio_init_struct);
	gpio_pin_mux_config(UART_GPIO, UART_PIN_SOURCE, UART_PIN_MUX_NUM);

	/* usart1 param */
	crm_periph_clock_enable(CRM_USART1_PERIPH_CLOCK, TRUE);
	usart_init(UART, 115200, USART_DATA_8BITS, USART_STOP_1_BIT);

	/* usart tx dma */
	dma_init_type dma_init_struct;
	crm_periph_clock_enable(UART_TX_DMA_CRM_CLK, TRUE);
	dmamux_enable(DMA1, TRUE);
	
	dma_reset(UART_TX_DMA);
	dma_default_para_init(&dma_init_struct);
	dma_init_struct.buffer_size = 0;
	dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
	dma_init_struct.memory_base_addr = (uint32_t)NULL;
	dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
	dma_init_struct.memory_inc_enable = TRUE;
	dma_init_struct.peripheral_base_addr = (uint32_t)&UART->dt;
	dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
	dma_init_struct.peripheral_inc_enable = FALSE;
	dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
	dma_init_struct.loop_mode_enable = FALSE;
	dma_init(UART_TX_DMA, &dma_init_struct);
	
	dmamux_init(DMA1MUX_CHANNEL1, DMAMUX_DMAREQ_ID_USART1_TX);
	
	/* usart rx dma */
	// dma_init_type dma_init_struct;
	// dma_reset(DMA1_CHANNEL3);
	// dma_default_para_init(&dma_init_struct);
	// dma_init_struct.buffer_size = USART2_TX_BUFFER_SIZE;
	// dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
	// dma_init_struct.memory_base_addr = (uint32_t)usart1_rx_buffer;
	// dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
	// dma_init_struct.memory_inc_enable = TRUE;
	// dma_init_struct.peripheral_base_addr = (uint32_t)&USART1->dt;
	// dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
	// dma_init_struct.peripheral_inc_enable = FALSE;
	// dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
	// dma_init_struct.loop_mode_enable = FALSE;
	// dma_init(DMA1_CHANNEL3, &dma_init_struct);

	/* enable */
	usart_transmitter_enable(UART, TRUE);
	usart_dma_transmitter_enable(UART, TRUE);
	usart_receiver_enable(UART, FALSE);
	usart_dma_receiver_enable(UART, FALSE);
	usart_enable(UART, TRUE);
}

inline uint16_t hal_uart_dma_get_dtcnt(void)
{
	return UART_TX_DMA->dtcnt;
}

void hal_uart_send_data(const uint8_t *data, uint16_t len)
{
	while (len--) {
		while (!(UART->sts & USART_TDBE_FLAG)) {
		}
		UART->dt = (*data++ & 0x01FF);
	}
}

void hal_uart_dma_send_data(const uint8_t *data, uint16_t len)
{
	while (hal_uart_dma_get_dtcnt()) {
	}

	dma_channel_enable(UART_TX_DMA, FALSE);
	UART_TX_DMA->paddr = (uint32_t)&UART->dt;
	UART_TX_DMA->maddr = (uint32_t)data;
	UART_TX_DMA->dtcnt = len;
	dma_channel_enable(UART_TX_DMA, TRUE);
}
