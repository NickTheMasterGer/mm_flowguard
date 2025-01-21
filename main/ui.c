#include "lvgl_ui.h"


static _lock_t lvgl_api_lock;
static const char *TAG = "Flowguard UI";

static void lvgl_task(void *arg)
{
    ESP_LOGI(TAG, "Starting LVGL task");
    int32_t time_till_next_ms = 0;
    int32_t time_threshold_ms = 1000 / CONFIG_FREERTOS_HZ;
    while (1) {
        _lock_acquire(&lvgl_api_lock);
        time_till_next_ms = lv_timer_handler();
        _lock_release(&lvgl_api_lock);
        // in case of triggering a task watch dog time out
        time_till_next_ms = MAX(time_till_next_ms, time_threshold_ms);
        usleep(1000 * time_till_next_ms);
    }
}

void ui_entry_func(void)
{
    lv_display_t *display= init_display();

    ESP_LOGI(TAG, "Create LVGL task");
    xTaskCreate(lvgl_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);

    ESP_LOGI(TAG, "Display LVGL Meter Widget");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    _lock_acquire(&lvgl_api_lock);
    flowguard_main_ui(display);
    _lock_release(&lvgl_api_lock);
}