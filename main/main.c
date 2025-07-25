#include "esp_lcd_types.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "lcd.h"
#include "task_lvgl.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <lvgl.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static const char *TAG = "main.c";

/* Used in conjunction with lv_obj_add_event_cb */
void ui_event_screen(lv_event_t *e) {
    lv_event_code_t event_code = lv_event_get_code(e);

    if (event_code == LV_EVENT_CLICKED) {
        /* Clicked */
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "Entering Main");
    ESP_LOGI(TAG, "Git hash: %s\n", BUILD_GIT_HASH);

    static esp_lcd_panel_io_handle_t lcd_io;
    static esp_lcd_panel_handle_t    lcd_panel;
    static lv_display_t             *lvgl_display = NULL;

    ESP_ERROR_CHECK(lcd_display_brightness_init());

    ESP_ERROR_CHECK(app_lcd_init(&lcd_io, &lcd_panel));
    lvgl_display = app_lvgl_init(lcd_io, lcd_panel);
    if (lvgl_display == NULL) {
        ESP_LOGI(TAG, "fatal error in app_lvgl_init");
        esp_restart();
    }

#ifdef CYD_TOUCH
    static esp_lcd_touch_handle_t tp;
    static lvgl_port_touch_cfg_t  touch_cfg;

    ESP_ERROR_CHECK(touch_init(&tp));
    touch_cfg.disp = lvgl_display;
    touch_cfg.handle = tp;
    lvgl_port_add_touch(&touch_cfg);
#endif

    ESP_ERROR_CHECK(lcd_display_brightness_set(100));
    ESP_ERROR_CHECK(lcd_display_rotate(lvgl_display, LV_DISPLAY_ROTATION_90));
    ESP_ERROR_CHECK(lvgl_gui_setup());

    if (xTaskCreatePinnedToCore(lvgl_gui_task, "lvgl_task", 2 * 4096 * 2, NULL, 2, NULL, 1) != pdPASS) {
        ESP_LOGE(TAG, "Failed to create task: %s", "lvgl_task");
    }

    ESP_LOGI(TAG, "Exiting Main");
    vTaskSuspend(NULL); // Suspend self
}
