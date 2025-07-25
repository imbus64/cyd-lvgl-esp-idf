#include "task_lvgl.h"
#include "core/lv_obj.h"
#include "display/lv_display.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "freertos/projdefs.h"
#include "misc/lv_area.h"
#include "misc/lv_style_gen.h"
#include "speedometer.h"
#include "widgets/image/lv_image.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <inttypes.h>
#include <lvgl.h>
#include <stdbool.h>
#include <stdint.h>

static const char *TAG = "task_lvgl.c";

static speedometer_t *speedo;
static lv_obj_t      *incr_label;
static uint32_t       incr_count = 0;

esp_err_t lvgl_gui_setup(void) {
    ESP_LOGI("LVGL gui setup", "Starting setup...");
    lvgl_port_lock(0);

    /* Create widgets */
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_scrollbar_mode(scr, LV_SCROLLBAR_MODE_OFF);

    /* A simple label to indicate git revision */
    lv_obj_t *version_info = lv_label_create(scr);
    lv_obj_align(version_info, LV_ALIGN_TOP_LEFT, 2, 2);
    lv_label_set_text(version_info, BUILD_GIT_HASH);

    /* Sample speedo with animation */
    speedo = speedometer_create(scr, 0, 100);
    speedometer_set_value(speedo, 50);
    animate_speedometer(speedo); // Remove this line to get rid of animation

    /* Label that gets incremented each update */
    incr_label = lv_label_create(scr);
    lv_obj_align(incr_label, LV_ALIGN_BOTTOM_MID, 0, -35);
    lv_obj_set_user_data(incr_label, (void *)&incr_count);

    lvgl_port_unlock();
    ESP_LOGI("LVGL gui setup", "All finished!");
    return ESP_OK;
}

void lvgl_gui_task(void *pvParams) {
    ESP_LOGI(TAG, "Entering Lvgl loop");

    TickType_t last_wake = xTaskGetTickCount();

    /* Update widgets */
    while (1) {
        lvgl_port_lock(0);

        uint32_t *icount = (uint32_t *)lv_obj_get_user_data(incr_label);
        lv_label_set_text_fmt(incr_label, "Updates: %" PRIu32, ++(*icount));

        lvgl_port_unlock();
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(1000 / 30)); // 30 Hz
    }

    ESP_LOGI(TAG, "Lvgl gui task is exiting. This should not happen.");
    vTaskDelete(NULL);
}
