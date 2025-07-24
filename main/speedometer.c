#include "speedometer.h"
#include "core/lv_obj_style_gen.h"
#include "misc/lv_area.h"
#include <lvgl.h>
#include <math.h>
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

/**
 * @brief Speedo animation function. For use as lv anim callback.
 *
 * @param obj Pointer to the speedometer_t (passed as void*)
 * @param v Integer between 0 - 2*pi*1000
 */
static void speedo_anim_set_value_wrapper(void *obj, int32_t v) {
    speedometer_t *speedo = (speedometer_t *)obj;
    float          s = sinf((float)v / 1000.0f);

    speedometer_set_value(speedo, 50.0f * (s + 1.0f));
}

/**
 * @brief Speedometer animation function
 *
 * @param spd The speedometer_t to animate
 */
void animate_speedometer(speedometer_t *spd) {
    lv_anim_t needle_anim;
    lv_anim_init(&needle_anim);
    lv_anim_set_var(&needle_anim, spd);
    lv_anim_set_exec_cb(&needle_anim, speedo_anim_set_value_wrapper);
    lv_anim_set_duration(&needle_anim, 3000);
    lv_anim_set_repeat_count(&needle_anim, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_values(&needle_anim, 0, 2 * M_PI * 1000);
    lv_anim_start(&needle_anim);
}

void speedometer_destroy(speedometer_t *spd) {
    if (!spd)
        return;

    lv_obj_del(spd->scale);
    free(spd);
}
