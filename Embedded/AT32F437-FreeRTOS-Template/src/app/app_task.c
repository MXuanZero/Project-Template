/* Includes --------------------------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "debug.h"
#include "task.h"

/* Private define --------------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------------------------*/
TaskHandle_t app_task_handle;
/* Private function prototypes -------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------------*/
void app_task_func(void *arg)
{
    (void)arg;
    LOG_DEBUG("build time: %s %s\n", build_date, build_time);
    for (;;) {
        vTaskDelay(1000);
        LOG_DEBUG("time: %d\n", xTaskGetTickCount());
    }
}

void app_task_create(void)
{
    xTaskCreate(app_task_func, "app_task", 1024, NULL, (UBaseType_t)4, &app_task_handle);
}

#if (configCHECK_FOR_STACK_OVERFLOW > 0)

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    /* Check pcTaskName for the name of the offending task,
     * or pxCurrentTCB if pcTaskName has itself been corrupted. */
    (void)xTask;
    (void)pcTaskName;
}

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */