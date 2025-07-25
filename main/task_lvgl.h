#ifndef TASK_LVGL_H
#define TASK_LVGL_H

#include "esp_err.h"

void lvgl_gui_task(void *pvParams);
esp_err_t lvgl_gui_setup(void);

#endif // TASK_LVGL_H
