/* Includes --------------------------------------------------------------------------------------*/
#include "debug.h"
#include "hal.h"
/* Private define --------------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------------*/
extern void app_task_create(void);
void system_clock_init(void);
/* Private variables -----------------------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------------*/
int main(void)
{
    /* system clock config. */
    system_clock_init();


    debug_init();
    nvic_config();

    /* hal init */
    hal_uart_init();
    hal_systick_init();
    hal_systick_set_it(false);

    app_task_create();

    hal_systick_set_it(true);
    vTaskStartScheduler();  // 开启任务调度
    for (;;) {
    }
}

void system_clock_init(void)
{
    /* reset crm */
    crm_reset();

    /* enable pwc periph clock */
    crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

    /* config ldo voltage */
    pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V3);

    /* set the flash clock divider */
    flash_clock_divider_set(FLASH_CLOCK_DIV_3);

    crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

    /* wait till hext is ready */
    while (crm_hext_stable_wait() == ERROR) {
    }

    /* config pll clock resource */
    crm_pll_config(CRM_PLL_SOURCE_HEXT, 144, 1, CRM_PLL_FR_4);

    /* enable pll */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

    /* wait till pll is ready */
    while (crm_flag_get(CRM_PLL_STABLE_FLAG) != SET) {
    }

    /* config ahbclk */
    crm_ahb_div_set(CRM_AHB_DIV_1);

    /* config apb2clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
    crm_apb2_div_set(CRM_APB2_DIV_2);

    /* config apb1clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
    crm_apb1_div_set(CRM_APB1_DIV_2);

    /* enable auto step mode */
    crm_auto_step_mode_enable(TRUE);

    /* select pll as system clock source */
    crm_sysclk_switch(CRM_SCLK_PLL);

    /* wait till pll is used as system clock source */
    while (crm_sysclk_switch_status_get() != CRM_SCLK_PLL) {
    }

    /* disable auto step mode */
    crm_auto_step_mode_enable(FALSE);

    /* update system_core_clock global variable */
    system_core_clock_update();
}