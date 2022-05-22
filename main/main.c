/**
 * @file lv_demos.c
 * @brief Evaluate demos provided by LVGL
 * @version 0.1
 * @date 2021-10-19
 * 
 * @copyright Copyright 2021 Espressif Systems (Shanghai) Co. Ltd.
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include "bsp_board.h"
#include "bsp_lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "lv_port.h"
#include "esp_log.h"

static void event_handler(lv_event_t * e)
{
	ESP_LOGI("button", "clicked");
}

void ui(void) {
	static lv_style_t button_style;
	lv_style_init(&button_style);
	lv_style_set_bg_color(&button_style, lv_color_hex(0xff0000));
	lv_style_set_text_font(&button_style, &lv_font_montserrat_26);

	lv_obj_t *button = lv_btn_create(lv_scr_act());
	lv_obj_add_event_cb(button, event_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_height(button, (LV_VER_RES/5)*3);
	lv_obj_set_width(button, (LV_HOR_RES/5)*4);
	lv_obj_align(button, LV_ALIGN_CENTER,0,0);

	lv_obj_add_style(button, &button_style, 0);
	
	lv_obj_t *label = lv_label_create(button);
	lv_label_set_text(label, "Push the button");
	lv_obj_align(label, LV_ALIGN_CENTER,0,0);
}

void app_main(void)
{
    ESP_ERROR_CHECK(bsp_board_init());
    ESP_ERROR_CHECK(lv_port_init());
    bsp_lcd_set_backlight(true);
    
	ui();

    do {
        lv_task_handler();
    } while (vTaskDelay(1), true);
}