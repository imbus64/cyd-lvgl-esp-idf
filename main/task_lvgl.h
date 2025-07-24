#pragma once

#include <math.h>

/*
 * Useful for calculating heights of half-circles (i.e. meters/scales)
 * See: https://en.wikipedia.org/wiki/Sagitta_(geometry)
 */
#define SAGITTA(radius, angle_deg) ((radius) * (1.0f - cosf((angle_deg) * (float)M_PI / 360.0f)))

/* Diameter of the speedo if it were a complete circle */
#define SPEEDO_DIAM 240

/* The actual height of the now half-circle */
#define SPEEDO_Y_OFFSET ((SPEEDO_DIAM - SAGITTA((float)SPEEDO_DIAM / 2, 270)) / 2)

/* The length of needle part that is actually visible */
#define NEEDLE_LEN 80

/* The number of discrete levels on the scale/meter */
#define SCALE_MAX 1000

/* The max value displayed on the scale/meter */
#define SPEED_MAX 40

/* Convert meters per second to kilometers per hour */
#define MS_TO_KMH(ms) ((ms) * 3.6f)

#define SCALE_FACTOR ((float)(SCALE_MAX) / (float)(SPEED_MAX))

#define KMH_TO_SCALE(kmh) (kmh * SCALE_FACTOR)

/* Convert a value in ms to a value that fits on the scale interval */
#define MS_TO_SCALE(ms) (MS_TO_KMH(ms) * ((float)(SCALE_MAX) / (float)(SPEED_MAX)))

/* Golden ratio, because of course */
#define GRATIO 1.618

void lvgl_task(void *arg);
