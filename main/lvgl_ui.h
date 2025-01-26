
#pragma once

#include "string.h"
#include <unistd.h>
#include <sys/param.h>

#include "esp_log.h"
#include "esp_timer.h"

#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_touch_xpt2046.h"

#include "lvgl.h"


// Using SPI2 in the example
#define LCD_HOST  SPI2_HOST
#define TOUCH_HOST  SPI3_HOST

#define LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)
#define LCD_BK_LIGHT_ON_LEVEL  1
#define LCD_BK_LIGHT_OFF_LEVEL !LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           26
#define EXAMPLE_PIN_NUM_MOSI           27
#define EXAMPLE_PIN_NUM_MISO           -1
#define EXAMPLE_PIN_NUM_LCD_DC         14
#define EXAMPLE_PIN_NUM_LCD_RST        12
#define EXAMPLE_PIN_NUM_LCD_CS         13
#define EXAMPLE_PIN_NUM_BK_LIGHT       2
#define EXAMPLE_PIN_NUM_TOUCH_CS       33

#define PIN_TOUCH_SCLK                 25
#define PIN_TOUCH_MOSI                 32
#define PIN_TOUCH_MISO                 35
#define PIN_NUM_TOUCH_CS               33
#define PIN_TOUCH_IRQ                  34

#define CONFIG_EXAMPLE_LCD_CONTROLLER_ILI9341 1
#define CONFIG_EXAMPLE_LCD_TOUCH_ENABLED 1

// The pixel number in horizontal and vertical
#if CONFIG_EXAMPLE_LCD_CONTROLLER_ILI9341
#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              320
#elif CONFIG_EXAMPLE_LCD_CONTROLLER_GC9A01
#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              240
#endif
// Bit number used to represent command and parameter
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8

#define EXAMPLE_LVGL_DRAW_BUF_LINES    20 // number of display lines in each draw buffer
#define EXAMPLE_LVGL_TICK_PERIOD_MS    2
#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 500
#define EXAMPLE_LVGL_TASK_MIN_DELAY_MS 1
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (4 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     2


extern void flowguard_main_ui(lv_disp_t *disp);
extern lv_display_t* init_display();