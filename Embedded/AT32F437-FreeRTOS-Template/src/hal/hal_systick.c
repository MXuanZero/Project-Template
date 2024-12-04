/* Includes --------------------------------------------------------------------------------------*/
#include "hal_systick.h"

#include "mcu.h"
/* Private define --------------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------------------------*/
typedef struct {
    __IO uint32_t none : 8;
    __IO uint32_t val : 24;
} hal_systick_val_t;
/* Private function prototypes -------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
static __IO uint32_t hal_fac_us;
static __IO uint32_t hal_fac_ms;
static __IO uint32_t hal_ms;
static __IO uint32_t hal_us;
/* Private functions -----------------------------------------------------------------------------*/
void hal_systick_init(void)
{
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
    SysTick_Config(system_core_clock / 1000U);
    hal_systick_set_it(false);

    hal_fac_us = system_core_clock / (1000000U);
    hal_fac_ms = hal_fac_us * (1000U);
}

void hal_systick_set_it(bool state)
{
    if (state) {
        SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    } else {
        SysTick->CTRL &= (~SysTick_CTRL_TICKINT_Msk);
    }
}

void hal_delay_ms(uint16_t ms)
{
    if (ms == 0) {
        return;
    }
    while (ms--) {
        hal_delay_us(1000U);
    }
}

void hal_delay_us(uint16_t us)
{
    if (us == 0) {
        return;
    }

    register uint32_t temp = hal_get_us();
    while (hal_get_us() - temp < us) {
    }
}

uint32_t hal_get_us(void)
{
    register uint32_t pending = 0, us;
    if (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) {
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            pending = 1;
        }
        us = (SysTick->LOAD + 1 - SysTick->VAL) * 1000U / (SysTick->LOAD + 1);
        return (hal_ms + pending) * 1000U + us;
    }
    // us = (SysTick->LOAD + 1 - SysTick->VAL) * 1000U / (SysTick->LOAD + 1);
    us = (SysTick->LOAD + 1 - SysTick->VAL) * 1000U / (SysTick->LOAD);  // 实测去掉+1精度更高
    return hal_us + us;
}

uint32_t hal_get_ms(void) { return hal_ms; }

void hal_systick_update(void)
{
    __disable_irq();
    hal_ms++;
    hal_us += 1000;
    SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk;
    __enable_irq();
}