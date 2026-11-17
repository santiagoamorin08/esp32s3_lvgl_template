#include "ui.h"

/* Generic placeholder UI — see ui.h. Pure widget construction only, no
 * event wiring: that lives in components/lvgl_ui/screens/scr_main.c, same
 * as it would for a real SquareLine export (SquareLine never touches
 * board/event logic either). Layout uses percentages/alignment only, so it
 * adapts to whatever resolution and rotation the BSP reports — nothing
 * here depends on esp_bsp. */

lv_obj_t *ui_scrMain;
lv_obj_t *ui_scrSplash;
lv_obj_t *ui_lblSplashTitle;
lv_obj_t *ui_lblSplashStatus;
/* Widgets del dashboard */
lv_obj_t *ui_arcBattery;
lv_obj_t *ui_lblBatteryValue;
lv_obj_t *ui_lblTemperature;
lv_obj_t *ui_lblUptime;
lv_obj_t *ui_lblTitle;
lv_obj_t *ui_lblSubtitle;
lv_obj_t *ui_arcTest;
lv_obj_t *ui_lblArcValue;
lv_obj_t *ui_btnTap;
lv_obj_t *ui_lblTapCount;

void ui_init(void)
{
    /* Crear pantalla Splash */
    ui_scrSplash = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrSplash, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(
        ui_scrSplash,
        lv_color_hex(0x101B2D),
        0
    );

    ui_lblSplashTitle = lv_label_create(ui_scrSplash);
    lv_label_set_text(ui_lblSplashTitle, "ESP32-S3 MONITOR");
    lv_obj_set_style_text_color(
        ui_lblSplashTitle,
        lv_color_hex(0xFFFFFF),
        0
    );
    lv_obj_align(ui_lblSplashTitle, LV_ALIGN_CENTER, 0, -20);

    ui_lblSplashStatus = lv_label_create(ui_scrSplash);
    lv_label_set_text(ui_lblSplashStatus, "Iniciando");
    lv_obj_set_style_text_color(
        ui_lblSplashStatus,
        lv_color_hex(0xB0BEC5),
        0
    );
    lv_obj_align(ui_lblSplashStatus, LV_ALIGN_CENTER, 0, 25);

    ui_scrMain = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrMain, LV_OBJ_FLAG_SCROLLABLE);

    ui_lblTitle = lv_label_create(ui_scrMain);
    lv_label_set_text(ui_lblTitle, "ESP32-S3-Touch-LCD-2");
    lv_obj_align(ui_lblTitle, LV_ALIGN_TOP_MID, 0, 10);

    ui_lblSubtitle = lv_label_create(ui_scrMain);
    lv_label_set_long_mode(ui_lblSubtitle, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(ui_lblSubtitle, LV_PCT(85));
    lv_obj_set_style_text_align(ui_lblSubtitle, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(ui_lblSubtitle, "Demo generica -- arrastra el arco y toca el boton");
    lv_obj_align_to(ui_lblSubtitle, ui_lblTitle, LV_ALIGN_OUT_BOTTOM_MID, 0, 6);

    ui_arcTest = lv_arc_create(ui_scrMain);
    lv_obj_set_size(ui_arcTest, 110, 110);
    lv_arc_set_range(ui_arcTest, 0, 100);
    lv_arc_set_value(ui_arcTest, 50);
    lv_obj_align(ui_arcTest, LV_ALIGN_LEFT_MID, 24, 12);

    ui_lblArcValue = lv_label_create(ui_scrMain);
    lv_label_set_text(ui_lblArcValue, "50");
    lv_obj_align_to(ui_lblArcValue, ui_arcTest, LV_ALIGN_CENTER, 0, 0);

    ui_btnTap = lv_btn_create(ui_scrMain);
    lv_obj_set_size(ui_btnTap, 130, 50);
    lv_obj_align(ui_btnTap, LV_ALIGN_RIGHT_MID, -24, -18);
    lv_obj_t *btn_label = lv_label_create(ui_btnTap);
    lv_label_set_text(btn_label, "Toca aqui");
    lv_obj_center(btn_label);

    ui_lblTapCount = lv_label_create(ui_scrMain);
    lv_label_set_text(ui_lblTapCount, "Toques: 0");
    lv_obj_align_to(ui_lblTapCount, ui_btnTap, LV_ALIGN_OUT_BOTTOM_MID, 0, 12);
    /* ================= DASHBOARD HOME ================= */

/* Fondo */
lv_obj_set_style_bg_color(
    ui_scrMain,
    lv_color_hex(0x101B2D),
    0
);

/* Título */
lv_label_set_text(ui_lblTitle, "MONITOR ESP32-S3");
lv_obj_set_style_text_color(
    ui_lblTitle,
    lv_color_hex(0xFFFFFF),
    0
);
lv_obj_align(ui_lblTitle, LV_ALIGN_TOP_MID, 0, 10);

/* Ocultar los elementos de prueba originales */
lv_obj_add_flag(ui_lblSubtitle, LV_OBJ_FLAG_HIDDEN);
lv_obj_add_flag(ui_arcTest, LV_OBJ_FLAG_HIDDEN);
lv_obj_add_flag(ui_lblArcValue, LV_OBJ_FLAG_HIDDEN);
lv_obj_add_flag(ui_btnTap, LV_OBJ_FLAG_HIDDEN);
lv_obj_add_flag(ui_lblTapCount, LV_OBJ_FLAG_HIDDEN);

/* Indicador circular de batería */
ui_arcBattery = lv_arc_create(ui_scrMain);
lv_obj_set_size(ui_arcBattery, 115, 115);
lv_arc_set_range(ui_arcBattery, 0, 100);
lv_arc_set_value(ui_arcBattery, 0);

lv_obj_set_style_arc_width(
    ui_arcBattery, 10, LV_PART_MAIN
);
lv_obj_set_style_arc_width(
    ui_arcBattery, 10, LV_PART_INDICATOR
);

lv_obj_set_style_arc_color(
    ui_arcBattery,
    lv_color_hex(0x334155),
    LV_PART_MAIN
);

lv_obj_set_style_arc_color(
    ui_arcBattery,
    lv_color_hex(0x22C55E),
    LV_PART_INDICATOR
);

lv_obj_align(ui_arcBattery, LV_ALIGN_CENTER, 0, -25);

/* Porcentaje de batería */
ui_lblBatteryValue = lv_label_create(ui_scrMain);
lv_label_set_text(ui_lblBatteryValue, "--%");
lv_obj_set_style_text_color(
    ui_lblBatteryValue,
    lv_color_hex(0xFFFFFF),
    0
);
lv_obj_align_to(
    ui_lblBatteryValue,
    ui_arcBattery,
    LV_ALIGN_CENTER,
    0,
    0
);

/* Temperatura */
ui_lblTemperature = lv_label_create(ui_scrMain);
lv_label_set_text(ui_lblTemperature, "Temperatura: -- °C");
lv_obj_set_style_text_color(
    ui_lblTemperature,
    lv_color_hex(0xFFFFFF),
    0
);
lv_obj_align(ui_lblTemperature, LV_ALIGN_CENTER, 0, 65);

/* Tiempo activo */
ui_lblUptime = lv_label_create(ui_scrMain);
lv_label_set_text(ui_lblUptime, "Tiempo activo: 00:00:00");
lv_obj_set_style_text_color(
    ui_lblUptime,
    lv_color_hex(0xB0BEC5),
    0
);
lv_obj_align(ui_lblUptime, LV_ALIGN_CENTER, 0, 100);

/* ================================================== */

    /* lv_obj_create(NULL) only allocates the screen — it does not become
     * active on its own (lvgl_port_add_disp() already set an empty default
     * screen active before ui_init() ran). Load it explicitly so it's
     * actually shown, same as a real SquareLine ui_init() would. */
    lv_disp_load_scr(ui_scrSplash);
}
