#pragma once
#include "lvgl_ui.h"

extern TaskHandle_t th_LVGL;
extern TaskHandle_t th_UI_Update;
void ui_entry_func(void);