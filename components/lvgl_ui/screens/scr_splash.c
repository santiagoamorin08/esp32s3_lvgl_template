#include "scr_splash.h"
#include "screens.h"
#include "ui.h"
#include "bsp_display.h"

#include <stdio.h>

/* Temporizador de los puntos */
static lv_timer_t *s_dots_timer = NULL;
static uint8_t s_dot_count = 0;

/* Animación de los puntos suspensivos */
static void splash_dots_timer_cb(lv_timer_t *timer)
{
    (void)timer;

    s_dot_count = (s_dot_count + 1) % 4;

    char text[20];

    snprintf(text, sizeof(text), "Iniciando%.*s",
             (int)s_dot_count, "...");

    lv_label_set_text(ui_lblSplashStatus, text);
}

/* Animación del brillo */
static void splash_brightness_cb(void *var, int32_t value)
{
    (void)var;

    bsp_display_set_brightness((uint8_t)value);
}

/* Detectar toque en cualquier lugar */
static void splash_touch_cb(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        ui_screens_navigate(SCREEN_MAIN);
    }
}

/* Registrar eventos */
void scr_splash_prepare(void)
{
    lv_obj_add_flag(ui_scrSplash, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_flag(ui_lblSplashTitle, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_lblSplashStatus, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_add_event_cb(
        ui_scrSplash,
        splash_touch_cb,
        LV_EVENT_CLICKED,
        NULL
    );

    lv_obj_add_event_cb(
        ui_lblSplashTitle,
        splash_touch_cb,
        LV_EVENT_CLICKED,
        NULL
    );

    lv_obj_add_event_cb(
        ui_lblSplashStatus,
        splash_touch_cb,
        LV_EVENT_CLICKED,
        NULL
    );
}

/* Inicializar Splash */
void scr_splash_init(void)
{
    s_dot_count = 0;

    lv_label_set_text(ui_lblSplashStatus, "Iniciando");

    if (s_dots_timer != NULL) {
        lv_timer_del(s_dots_timer);
    }

    s_dots_timer = lv_timer_create(
        splash_dots_timer_cb,
        350,
        NULL
    );

    /* Comenzar con brillo apagado */
    bsp_display_set_brightness(0);

    /* Fade-in de 800 ms */
    lv_anim_t anim;

    lv_anim_init(&anim);
    lv_anim_set_var(&anim, NULL);
    lv_anim_set_values(&anim, 0, 100);
    lv_anim_set_time(&anim, 800);
    lv_anim_set_exec_cb(&anim, splash_brightness_cb);
    lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);

    lv_anim_start(&anim);
}

/* Liberar recursos */
void scr_splash_uninit(void)
{
    if (s_dots_timer != NULL) {
        lv_timer_del(s_dots_timer);
        s_dots_timer = NULL;
    }

    lv_anim_del(NULL, splash_brightness_cb);
}

/* Actualización periódica */
void scr_splash_step(void)
{
}