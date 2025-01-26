#include "mm_flowguard.h"
#include "driver/gpio.h"
#include <nvs_flash.h>

struct mm_flowguard fg;

static const char *TAG = "Flowguard MAIN";
nvs_handle_t my_handle;
TaskHandle_t th_mm_flowguard=0;

void mm_flowguard_entry_func(void)
{
    ESP_LOGI(TAG, "Setuo GPIO");
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
    //change gpio intrrupt type for one pin
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);

    ESP_LOGI(TAG, "Load Data from NVS");
    
     // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

	 // Open
	err = nvs_open("tapdata", NVS_READWRITE, &my_handle);
	ESP_ERROR_CHECK( err );

    err = nvs_get_i64(my_handle, "offtime", &fg.offtime);
	if (err == ESP_OK)
    {
        fg.offtime_old=fg.offtime;
    }
    else
    {
        fg.offtime=5000;
    }
    ESP_LOGI(TAG, "Offtime: %.2f",0.001*fg.offtime);

    ESP_LOGI(TAG, "Create Flowguard main task");
    //xTaskCreate(mm_flowguard_main, "MM_Flowguard", MM_FLOWGUARD_STACKSIZE, NULL, MM_FLOWGUARD_PRIO, NULL);
    xTaskCreatePinnedToCore(mm_flowguard_main, "MM_Flowguard", MM_FLOWGUARD_STACKSIZE, NULL, MM_FLOWGUARD_PRIO, &th_mm_flowguard,0);
}

void mm_flowguard_main(void *arg)
{
    int write_timer=0;
    while(1)
    {
        fg.sensor=gpio_get_level(GPIO_INPUT_IO_1)>0?0:1;

        switch(fg.state)
        {
            case 1: //valve is on
                fg.valve=1;
                if(fg.sensor==1)
                {
                    fg.trapcounter++;
                    fg.state=2;
                    fg.timer=0;
                }
                break;
            case 2: //sensor active
                fg.timer +=10;
                fg.valve=1;
                if(fg.timer > fg.sensor_threashold)
                {
                    fg.timer =0;
                    fg.state=3;
                } 
                if(fg.sensor==0)
                {
                    fg.timer =0;
                    fg.state=1;
                }
                break;
            case 3: //valve off
                if(fg.sensor==0)
                {
                    fg.timer +=10;
                }
                fg.valve=0;
                if(fg.timer > fg.offtime)
                {
                    fg.timer =0;
                    fg.state=1;
                }
                break;
            default:
                fg.trapcounter=0;
                fg.valve=1;
                fg.timer=0;
                fg.state=1;
        }
        gpio_set_level(GPIO_OUTPUT_IO_0, fg.valve);
        gpio_set_level(GPIO_OUTPUT_IO_1, fg.valve);

        if(write_timer>1000) //approx. every 10 seconds
        {
            if(fg.offtime!=fg.offtime_old)
            {   
                nvs_set_i64(my_handle, "offtime", fg.offtime);
            }
            write_timer=0;
        }
        else
        {
            write_timer++;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}