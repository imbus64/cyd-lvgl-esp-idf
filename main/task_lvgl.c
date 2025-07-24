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

void lvgl_task(void *arg) {
    ESP_LOGI(TAG, "Starting LVGL");

    lvgl_port_lock(0);

    lv_obj_t *scr = lv_screen_active();

    /* Turn of the lights */
    lv_color_t bg = lv_color_black();
    lv_obj_set_style_bg_color(scr, bg, LV_PART_MAIN);

    /* Create widgets */
    speedo = speedometer_create(scr, 0, 100);
    speedometer_set_value(speedo, 50);

    lvgl_port_unlock();

    ESP_LOGI(TAG, "Entering Lvgl loop");

    TickType_t last_wake = xTaskGetTickCount();

    while (1) {
        /* Update widgets */
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(1000 / 30));
    }

    vTaskDelete(NULL);
}
