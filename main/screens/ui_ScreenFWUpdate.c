// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: SquareLine_Project

#include "../ui.h"

void ui_ScreenFWUpdate_screen_init(void)
{
    ui_ScreenFWUpdate = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_ScreenFWUpdate, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_image_recolor(ui_ScreenFWUpdate, lv_color_hex(0x76A7E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_recolor_opa(ui_ScreenFWUpdate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelUpdate = lv_label_create(ui_ScreenFWUpdate);
    lv_obj_set_width(ui_LabelUpdate, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LabelUpdate, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LabelUpdate, 0);
    lv_obj_set_y(ui_LabelUpdate, -50);
    lv_obj_set_align(ui_LabelUpdate, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelUpdate, "Firmwareupdate ...");
    lv_obj_set_style_text_font(ui_LabelUpdate, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelUpdate2 = lv_label_create(ui_ScreenFWUpdate);
    lv_obj_set_width(ui_LabelUpdate2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LabelUpdate2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LabelUpdate2, 0);
    lv_obj_set_y(ui_LabelUpdate2, 50);
    lv_obj_set_align(ui_LabelUpdate2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelUpdate2, "per Wlan verbinden mit:\nESP32 OTA Update\nund 192.168.4.1 im Browser öffnen");

    lv_obj_add_event_cb(ui_ScreenFWUpdate, cbScreenFWUpdate, LV_EVENT_SCREEN_LOADED, NULL);

    uic_Screen1 = ui_ScreenFWUpdate;
}
