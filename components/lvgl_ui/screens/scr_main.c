#include "scr_main.h"
#include "screens.h"
#include "ui.h"

#include "bsp_battery.h"
#include "driver/temperature_sensor.h"
#include "esp_timer.h"
#include "esp_log.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

static const char *TAG = "scr_main";

/* Sensor interno de temperatura */
static temperature_sensor_handle_t s_temp_sensor = NULL;

/* Timer de actualización del Dashboard */
static lv_timer_t *s_home_timer = NULL;

/* Estado de inicialización */
static bool s_hardware_initialized = false;

/* -------------------------------------------------- */
/* Calcular porcentaje estimado de batería             */
/* -------------------------------------------------- */

static int battery_get_percent(float voltage)
{
    const float voltage_min = 3.3f;
    const float voltage_max = 4.2f;

    if (voltage <= voltage_min) return 0;
    if (voltage >= voltage_max) return 100;

    return (int)(
        ((voltage - voltage_min) /
        (voltage_max - voltage_min)) * 100.0f + 0.5f
    );
}

/* -------------------------------------------------- */
/* Actualizar los widgets del Dashboard                */
/* -------------------------------------------------- */

static void home_update_widgets(void)
{
    /* BATERÍA */
    float voltage = 0.0f;
    uint16_t adc_value = 0;

    bsp_battery_get_voltage(&voltage, &adc_value);

    if (voltage >= 2.5f && voltage <= 4.5f) {

        int battery = battery_get_percent(voltage);

        lv_arc_set_value(ui_arcBattery, battery);

        lv_label_set_text_fmt(
            ui_lblBatteryValue,
            "%d%%",
            battery
        );

    } else {

        lv_label_set_text(ui_lblBatteryValue, "--%");
    }

    /* TEMPERATURA */
    float temperature = 0.0f;

    if (
        s_temp_sensor != NULL &&
        temperature_sensor_get_celsius(
            s_temp_sensor,
            &temperature
        ) == ESP_OK
    ) {

        int temp_x10 = (int)(temperature * 10.0f);
        int decimal = abs(temp_x10 % 10);

        lv_label_set_text_fmt(
            ui_lblTemperature,
            "Temperatura: %d.%d °C",
            temp_x10 / 10,
            decimal
        );

    } else {

        lv_label_set_text(
            ui_lblTemperature,
            "Temperatura: -- °C"
        );
    }

    /* TIEMPO ACTIVO */
    int64_t uptime = esp_timer_get_time() / 1000000LL;

    uint64_t hours = uptime / 3600;
    uint32_t minutes = (uptime % 3600) / 60;
    uint32_t seconds = uptime % 60;

    lv_label_set_text_fmt(
        ui_lblUptime,
        "Tiempo activo: %02llu:%02u:%02u",
        (unsigned long long)hours,
        (unsigned)minutes,
        (unsigned)seconds
    );
}

/* -------------------------------------------------- */
/* Timer LVGL: actualización cada segundo              */
/* -------------------------------------------------- */

static void home_update_timer_cb(lv_timer_t *timer)
{
    (void)timer;

    home_update_widgets();
}

/* -------------------------------------------------- */
/* PREPARE                                             */
/* -------------------------------------------------- */

void scr_main_prepare(void)
{
    if (s_hardware_initialized) return;

    /* Inicializar medición de batería */
    bsp_battery_init();

    /* Configurar sensor interno de temperatura */
    temperature_sensor_config_t temp_config =
        TEMPERATURE_SENSOR_CONFIG_DEFAULT(-10, 80);

    esp_err_t err = temperature_sensor_install(
        &temp_config,
        &s_temp_sensor
    );

    if (err == ESP_OK) {

        err = temperature_sensor_enable(s_temp_sensor);

        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Error al habilitar temperatura");
            temperature_sensor_uninstall(s_temp_sensor);
            s_temp_sensor = NULL;
        }

    } else {

        ESP_LOGE(TAG, "Error al instalar sensor de temperatura");
        s_temp_sensor = NULL;
    }

    s_hardware_initialized = true;

    ESP_LOGI(TAG, "Hardware inicializado");
}

/* -------------------------------------------------- */
/* INIT                                                */
/* -------------------------------------------------- */

void scr_main_init(void)
{
    /* Crear timer de actualización de 1 segundo */
    if (s_home_timer == NULL) {

        s_home_timer = lv_timer_create(
            home_update_timer_cb,
            1000,
            NULL
        );
    }

    /* Actualizar valores inmediatamente */
    home_update_widgets();

    ESP_LOGI(TAG, "Dashboard iniciado");
}

/* -------------------------------------------------- */
/* UNINIT                                              */
/* -------------------------------------------------- */

void scr_main_uninit(void)
{
    if (s_home_timer != NULL) {

        lv_timer_del(s_home_timer);
        s_home_timer = NULL;
    }

    ESP_LOGI(TAG, "Dashboard detenido");
}

/* -------------------------------------------------- */
/* STEP                                                */
/* -------------------------------------------------- */

void scr_main_step(void)
{
    /* Las actualizaciones se realizan mediante lv_timer */
}