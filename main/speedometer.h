#ifndef SPEEDO_H
#define SPEEDO_H
#include "lvgl.h"

typedef struct {
    lv_obj_t *scale;
    lv_obj_t *needle;
    lv_obj_t *label;
} speedometer_t;

speedometer_t *speedometer_create(lv_obj_t *parent, int min, int max);
void speedometer_set_value(speedometer_t *spd, int value);
void speedometer_destroy(speedometer_t *spd);
void animate_speedometer(speedometer_t *spd);

#endif
