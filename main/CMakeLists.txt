set(srcs "flowguard_main.c"
         "create_task_example.c"
         "softap_ota.c"
         "flowguard_ui.c"
         "lvgl_ui.c"
         "ui_helpers.c"
         "screens/ui_Screen1.c"
         "screens/ui_ScreenFWUpdate.c"
         "ui.c"
         "mm_flowguard.c")
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES console esp_timer esp_http_server app_update nvs_flash esp_wifi
                    EMBED_TXTFILES index.html)
