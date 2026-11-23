
# ASIGNACIÓN 1 – SPLASH INTERACTIVO Y DASHBOARD

## Estado
Código implementado, compilado y publicado en GitHub.
Pendiente de prueba con la pantalla física.

## Rama
assignment/01-splash-events

## Commit
96ddeb8

## Hardware
Waveshare ESP32-S3-Touch-LCD-2.

## Desarrollo realizado

### Pantalla Splash
- Pantalla de inicio.
- Título ESP32-S3 MONITOR.
- Animación de puntos cada 350 ms.
- Encendido progresivo del brillo de 0 a 100%.
- Duración de animación: 800 ms.
- Navegación táctil hacia Home.

### Pantalla Home
- Indicador circular de batería.
- Visualización de temperatura.
- Tiempo de funcionamiento.

### Sensores y datos
- Lectura de batería mediante ADC.
- Cálculo estimado del porcentaje de batería.
- Sensor interno de temperatura ESP32-S3.
- Tiempo activo mediante esp_timer_get_time().
- Actualización de widgets cada 1000 ms.

### Archivos principales
- components/lvgl_ui/screens/scr_main.c
- components/lvgl_ui/screens/scr_splash.c
- components/lvgl_ui/screens/scr_splash.h
- components/lvgl_ui/screens/screens.c
- components/lvgl_ui/screens/screens.h
- components/lvgl_ui/ui/ui.c
- components/lvgl_ui/ui/ui.h
- main/main.c

## Comprobaciones
- Compilación ESP-IDF correcta.
- git diff --check sin errores.
- Commit creado.
- Rama publicada en GitHub.

## Pendiente de prueba física
- Funcionamiento del táctil.
- Encendido progresivo.
- Lecturas reales de batería.
- Medición de temperatura.
- Visualización del Dashboard.

## Repositorio
https://github.com/santiagoamorin08/esp32s3_lvgl_template/tree/assignment/01-splash-events
