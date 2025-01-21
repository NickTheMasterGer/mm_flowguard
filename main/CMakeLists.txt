set(srcs "flowguard_main.c"
         "create_task_example.c"
         "softap_ota.c"
         "ui.c"
         "lvgl_ui.c"
         "ui_herlpers.c")
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES console esp_timer esp_http_server app_update nvs_flash esp_wifi
                    EM