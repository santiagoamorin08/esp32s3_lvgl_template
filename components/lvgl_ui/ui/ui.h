#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void ui_init(void);

/* Pantalla Splash */
extern lv_obj_t *ui_scrSplash;
extern lv_obj_t *ui_lblSplashTitle;
extern lv_obj_t *ui_lblSplashStatus;

/* Widgets de la pantalla principal */
extern lv_obj_t *ui_arcBattery;
extern lv_obj_t *ui_lblBatteryValue;
extern lv_obj_t *ui_lblTemperature;
extern lv_obj_t *ui_lblUptime;

/* Elementos originales */
extern lv_obj_t *ui_scrMain;
extern lv_obj_t *ui_lblTitle;
extern lv_obj_t *ui_lblSubtitle;
extern lv_obj_t *ui_arcTest;
extern lv_obj_t *ui_lblArcValue;
extern lv_obj_t *ui_btnTap;
extern lv_obj_t *ui_lblTapCount;

#ifdef __cplusplus
}
#endif

#endif