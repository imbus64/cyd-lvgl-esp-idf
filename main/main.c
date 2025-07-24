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

static const char *TAG = "surgehud.c";

void app_main(void) {
    ESP_LOGI(TAG, "Entering Main");

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

    ESP_ERROR_CHECK(lcd_display_brightness_set(100));

    if (xTaskCreate(lvgl_task, "lvgl_task", 2 * 4096 * 2, NULL, 2, NULL) != pdPASS) {
        ESP_LOGE(TAG, "Failed to create task: %s", "lvgl_task");
    }

    ESP_LOGI(TAG, "Exiting Main");
    vTaskSuspend(NULL); // Suspend self
}
