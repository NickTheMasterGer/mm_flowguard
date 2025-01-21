/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include "esp_console.h"
#include "flowguard_main.h"
#include "ui.h"
#include "sdkconfig.h"

static void register_creating_task(void)
{
    const esp_console_cmd_t creating_task_cmd = {
        .command = "create_task",
        .help = "Run the example that demonstrates how to create and run pinned and unpinned tasks",
        .hint = NULL,
        .func = &comp_creating_task_entry_func,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&creating_task_cmd));
}

static void register_softap_ota_task(void)
{
    const esp_console_cmd_t creating_task_cmd = {
        .command = "create_task",
        .help = "Run the example that demonstrates how to create and run pinned and unpinned tasks",
        .hint = NULL,
        .func = &softap_ota_entry_func,
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&creating_task_cmd));
}

static void config_console(void)
{
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    /* Prompt to be printed before each line.
     * This can be customized, made dynamic, etc.
     */
    repl_config.prompt = PROMPT_STR ">";
    repl_config.max_cmdline_length = 1024;
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));

    esp_console_register_help_command();

    // register entry functions for each component
    register_creating_task();
    //register_softap_ota_task();

    ESP_ERROR_CHECK(esp_console_start_repl(repl));
    printf("\n"
           "Please type the component you would like to run.\n");
}

void app_main(void)
{
    config_console();
    softap_ota_entry_func(0, NULL);
    ui_entry_func();
}
