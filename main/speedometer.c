#include "speedometer.h"
#include "core/lv_obj_style_gen.h"
#include "misc/lv_area.h"
#include <lvgl.h>
#include <stdio.h>
#include <stdlib.h>

speedometer_t *speedometer_create(lv_obj_t *parent, int min, int max) {
    speedometer_t *spd = malloc(sizeof(speedometer_t));
    if (!spd)
        return NULL;

    lv_color_t color_indicator = lv_color_make(0xFF, 0, 0);
    lv_color_t color_label = lv_color_make(0xFF, 0xFF, 0xFF);

    spd->scale = lv_scale_create(parent);
    lv_scale_set_range(spd->scale, min, max);
    lv_scale_set_angle_range(spd->scale, 270);
    lv_scale_set_rotation(spd->scale, 135);
    lv_scale_set_mode(spd->scale, LV_SCALE_MODE_ROUND_INNER);
    lv_obj_set_size(spd->scale, 200, 200);
    lv_obj_center(spd->scale);
    lv_obj_set_style_radius(spd->scale, LV_RADIUS_CIRCLE, 0);

    spd->needle = lv_line_create(spd->scale);

    lv_obj_set_style_line_width(spd->needle, 3, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(spd->needle, true, LV_PART_MAIN);
    lv_obj_set_style_line_color(spd->needle, color_indicator, LV_PART_MAIN);

    spd->label = lv_label_create(spd->scale);
    lv_obj_center(spd->label);
    lv_obj_align(spd->label, LV_ALIGN_CENTER, 0, 35);
    lv_obj_set_style_text_color(spd->label, color_label, 0);
    lv_label_set_text_fmt(spd->label, "%d", min);

    return spd;
}

void speedometer_set_value(speedometer_t *spd, int value) {
    if (!spd || !spd->scale || !spd->label || !spd->needle)
        return;

    lv_scale_set_line_needle_value(spd->scale, spd->needle, -35, value);
    lv_label_set_text_fmt(spd->label, "%d", value);
}

void speedometer_destroy(speedometer_t *spd) {
    if (!spd)
        return;

    lv_obj_del(spd->scale);
    free(spd);
}
