/** @file main.c *
 * entry point
 */

#include "main.h"
#include <stdio.h>

xQueueHandle hc_sr501_queue;


static void IRAM_ATTR hc_sr501_intr(void *args){

	uint32_t pin = (uint32_t) args;
	xQueueSendFromISR(hc_sr501_queue, &pin, NULL);
}

void hc_sr501_fired()
{
	uint32_t pin;

	while (true)
	{
		if(xQueueReceive(hc_sr501_queue, &pin, portMAX_DELAY))
		{
            printf("interrupt:  %d\n", gpio_get_level(HC_SR501));
		}
        //vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}


void app_main()
{
   gpio_config_t hc_sr501_conf = {
		.pin_bit_mask = GPIO_SEL_18,
		.mode = GPIO_MODE_INPUT,
		/* .pull_up_en = GPIO_PULLUP_DISABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE, */
		.intr_type = GPIO_INTR_POSEDGE,
	};

    gpio_config(&hc_sr501_conf);

	gpio_install_isr_service(0);

	gpio_isr_handler_add(HC_SR501, hc_sr501_intr, (void *)HC_SR501);

	hc_sr501_queue = xQueueCreate(10, sizeof(int));

	xTaskCreate(hc_sr501_fired, "button 1 task", 2048, NULL, 1, NULL);

    while(true)
    {
        printf("regular:    %d\n", gpio_get_level(HC_SR501));
        //vTaskDelay(10 / portTICK_PERIOD_MS);
    }

}
