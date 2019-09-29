/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.

芯片脚位定义

             --------------------------------------------------
    模拟3V3 |01|VDDA                                EXT_RSTB|32| #RST
   WIFI_ANT |02|LNA                                   RES12K|31| RES_12K - GND
    功放3V3 |03|VDD3P3                                  VDDA|30| 模拟3V3
    功放3V3 |04|VDD3P3                                  VDDD|29| 模拟3V3
         NC |05|VDD_RTC                              XTAL_IN|28| 26MHz
        ADC |06|TOUT                                XTAL_OUT|27| 26MHz
            |07|CHIP_EN                  SPI_CS1/U0TXD/GPIO1|26| TXD
            |08|GPIO16/XPD_DCDC        I2SO_DATA/U0RXD/GPIO3|25| RXD
           <                                                    >
            |09|GPIO14/MTMS                            GPIO5|24| 
            |10|GPIO12/MTDI                      SD_D1/GPIO8|23| FL_DI
    数字3V3 |11|VDDPST                           SD_D0/GPIO7|22| FL_DO
            |12|GPIO13/MTCK                     SD_CLK/GPIO6|21| FL_CLK
            |13|GPIO15/MTDO/I2SO_BCK   SPI_CS0/SD_CMD/GPIO11|20| FL_#CS
            |14|GPIO2/U1TXD/I2SO_WS             SD_D3/GPIO10|19| FL_#WP
            |15|GPIO0/SPI_CS2                    SD_D2/GPIO9|18| FL_#HOLD
            |16|GPIO4                                 VDDPST|17| 数字3V3
             --------------------------------------------------
                                     |33|GND

原厂模块脚位定义
            |                                                  |
            |                      ANTENNA                     |
            |                                                  |
            |--------------------------------------------------|
            |01|3V3                                      GND|18| 
            |02|EN                                      IO16|17| 
            |03|IO14/HSPI_CLK                           TOUT|16| 
            |04|IO12/HSPI_MISO                           RST|15| 
            |05|IO13/HSPI_MOSI/UART0_CTS                 IO5|14| 
            |06|IO15/HSPI_CS/UART0_RTS                   GND|13| 
            |07|IO2/UART1_TXD                  UART0_TXD/IO1|12| 
            |08|IO0                            UART0_RXD/IO3|11| 
            |09|GND                                      IO4|10| 
             --------------------------------------------------
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"


void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP8266 chip with %d CPU cores, WiFi, ",
            chip_info.cores);

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
