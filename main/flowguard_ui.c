#include "flowguard_ui.h"
#include "ui.h"
#include "mm_flowguard.h"

static _lock_t lvgl_api_lock;
static const char *TAG = "Flowguard UI";
TaskHandle_t th_LVGL;
TaskHandle_t th_UI_Update;

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
        //usleep(1000 * time_till_next_ms);
        vTaskDelay(pdMS_TO_TICKS(time_till_next_ms));
    }
}
static void ui_update(void *arg)
{
    lv_slider_set_value(ui_Slider1, fg.offtime/100, LV_ANIM_OFF);
    while (1)
    {
        _lock_acquire(&lvgl_api_lock);
        if(fg.state==3)
        {
            int temp=0;
            if(fg.offtime>0)temp=(100*fg.timer)/fg.offtime;
            lv_bar_set_value(ui_Bar1, temp, LV_ANIM_OFF);
        }
        else
        {
            lv_bar_set_value(ui_Bar1, 100, LV_ANIM_OFF);
        }
        lv_label_set_text_fmt(ui_Label1, "%d", fg.trapcounter);
        lv_label_set_text_fmt(ui_Label2, "%.1f s", 0.001*(float)fg.offtime);
        _lock_release(&lvgl_api_lock);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
void ui_entry_func(void)
{
    lv_display_t *display= init_display();

    ESP_LOGI(TAG, "Create LVGL task");
    //xTaskCreate(lvgl_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);
    xTaskCreatePinnedToCore(lvgl_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, &th_LVGL,0);

    ESP_LOGI(TAG, "Display LVGL Meter Widget");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    _lock_acquire(&lvgl_api_lock);
    ui_init();
    //flowguard_main_ui(display);
    _lock_release(&lvgl_api_lock);

    //xTaskCreate(ui_update, "UI_Update", 1024, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);
    xTaskCreatePinnedToCore(ui_update, "UI_Update", 2048, NULL, EXAMPLE_LVGL_TASK_PRIORITY, &th_UI_Update,0);
}