/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @file
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example_freertos
 *
 * @brief Blinky FreeRTOS Example Application main file.
 *
 * This file contains the source code for a sample application using FreeRTOS to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "bsp.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"
#include "sdk_errors.h"
#include "app_error.h"
#include "led.hpp"

#if LEDS_NUMBER <= 2
#error "Board is not equipped with enough amount of LEDs"
#endif

#define TIMER_PERIOD		1000	/**< Timer period. LED1 timer will expire after 1000 ms */

TaskHandle_t led_toggle_task_handle; /**< Reference to LED0 toggling FreeRTOS task. */
//TimerHandle_t led_toggle_timer_handle; /**< Reference to LED1 toggling FreeRTOS timer. */

/**@brief LED0 task entry function.
 *
 * @param[in] pvParameter   Pointer that will be used as the parameter for the task.
 */
//static void led_toggle_task_function(void * pvParameter) {
//	UNUSED_PARAMETER(pvParameter);
//	led led1(LED_1);
//	while (true) {
//		led1.toggle();
//		//bsp_board_led_invert(BSP_BOARD_LED_0);
//		/* Delay a task for a given number of ticks */
//		vTaskDelay(TASK_DELAY);
//
//		/* Tasks must be implemented to never return... */
//	}
//}
/**@brief The function to call when the LED1 FreeRTOS timer expires.
 *
 * @param[in] pvParameter   Pointer that will be used as the parameter for the timer.
 */

int main(void) {
	ret_code_t err_code;
	static led led1(LED_1), led2(LED_2), led3(LED_3);
	static led_blink led1Blinker("led1", 200, 1, &led1), led2Blinker("led1",
			400, 1, &led2), led3Blinker("led1", 600, 1, &led3);
	/* Initialize clock driver for better time accuracy in FREERTOS */
	err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);

	led1Blinker.Start(0);
	led2Blinker.Start(0);
	led3Blinker.Start(0);

	/* Activate deep sleep mode */
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

	/* Start FreeRTOS scheduler. */
	vTaskStartScheduler();

	while (true) {
		/* FreeRTOS should not be here... FreeRTOS goes back to the start of stack
		 * in vTaskStartScheduler function. */
	}
}

/**
 *@}
 **/
