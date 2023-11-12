/*
   Написано для проекта AVOCADO (AVOCADO_esp):
   https://github.com/Ni3nayka/AVOCADO_esp/releases

   Мануал по проекту:
   https://docs.google.com/document/d/1Rvoi-yDUz9T8iqtriVZaRBL97akOxsfKGw68NE6AFoM/edit?usp=sharing

   Мануал по прошивке по wifi (сторонний):
   https://wikihandbk.com/wiki/ESP8266:Примеры/Прошивка_ESP8266_методом_OTA

   Установите python 2.7.х:
   https://www.python.org/downloads/release/python-277/
   или установите из папки со скачанной библиотекой

   Автор: Бакай Егор <egor_bakay@inbox.ru>
*/

#define WIFI_NAME "test_name"                // Имя wifi сети
#define WIFI_PASSWORD "test_pass"            // Пароль от wifi сети

// Расскоментируйте, если хотите это использовать:
//#define DEVICE_NAME "test_esp8266"         // Имя сетевого устройства (чтобы ваша esp красиво отображалась)
//#define DEVICE_PASSWORD "1234"             // Пароль при прошивке по wifi

#define ENABLE_AVOCADO_ESP_WIFI_BOOT         // "Включить прошивку по wifi"

// ! ВСЕ #define (для библиотеки) ДОЛЖНЫ БЫТЬ НАПИСАНЫ ДО ПОДКЛЮЧЕНИЯ БИБЛИОТЕКИ !
#include <AVOCADO_esp.h>                     // Подключить библиотеку

AVOCADO_esp esp;                             // объявим esp (для использования функционала библиотеки)

void setup() {
  Serial.begin(115200);                      // Запустим монитор порта (не обязательно для работы)
  esp.setup();                               // Запустим esp (для подключения к wifi и др.)
  esp.disable_wifi_boot();                   // Отключить прошивку по вай-фаю (по умолчанию включена в этом режиме)
  esp.enable_wifi_boot();                    // Включить прошивку по вай-фаю (если не отключали, то включать не обязательно)
}

void loop() {
  esp.update();                              // Обновить esp (должно быть в рабочем цикле, иначе библиотека не будет работать)
}
