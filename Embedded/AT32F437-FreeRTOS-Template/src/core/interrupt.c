/* Includes --------------------------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "hal.h"
/* Private define --------------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------------*/
extern void xPortSysTickHandler(void);
/* Private variables -----------------------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------------*/
void NMI_Handler(void) {}

void HardFault_Handler(void)
{
    /* go to infinite loop when hard fault exception occurs */
    while (1) {
    }
}

void MemManage_Handler(void)
{
    /* go to infinite loop when memory manage exception occurs */
    while (1) {
    }
}

void BusFault_Handler(void)
{
    /* go to infinite loop when bus fault exception occurs */
    while (1) {
    }
}

void UsageFault_Handler(void)
{
    /* go to infinite loop when usage fault exception occurs */
    while (1) {
    }
}

void DebugMon_Handler(void) {}

void SysTick_Handler(void)
{
    xPortSysTickHandler();
    hal_systick_update();
}
