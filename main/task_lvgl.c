#include "task_lvgl.h"
#include "display/lv_display.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "freertos/projdefs.h"
#include "speedometer.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <inttypes.h>
#include <lvgl.h>
#include <stdbool.h>
#include <stdint.h>

static const char *TAG = "task_lvgl.c";

static speedometer_t *speedo;

esp_err_t lvgl_gui_setup(void) {
    ESP_LOGI(TAG, "Starting LVGL");

    lvgl_port_lock(0);

    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_scrollbar_mode(scr, LV_SCROLLBAR_MODE_OFF);

    /* Create widgets */
    /* A simple label to indicate git revision */
    lv_obj_t *version_info = lv_label_create(scr);
    lv_obj_align(version_info, LV_ALIGN_TOP_LEFT, 2, 2);
    lv_label_set_text(version_info, BUILD_GIT_HASH);

    speedo = speedometer_create(scr, 0, 100);
    speedometer_set_value(speedo, 50);
    animate_speedometer(speedo);

    lvgl_port_unlock();

    return ESP_OK;
}

void lvgl_gui_task(void *pvParams) {
    ESP_LOGI(TAG, "Entering Lvgl loop");

    TickType_t last_wake = xTaskGetTickCount();

    while (1) {
        /* Update widgets */
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(1000 / 30));
    }

    ESP_LOGI(TAG, "Lvgl gui task is exiting. This should not happen.");
    vTaskDelete(NULL);
}
