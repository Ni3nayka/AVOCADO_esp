/*
   Write for pack lib AVOCADO_esp:
   https://github.com/Ni3nayka/AVOCADO_esp

   manual:
   https://wikihandbk.com/wiki/ESP8266:Примеры/Прошивка_ESP8266_методом_OTA

   install python 2.7.7:
   https://www.python.org/downloads/release/python-277/
   or instal from lib folder

   author: Egor Bakay <egor_bakay@inbox.ru>
   write:  november 2022
   modify: november 2022
*/

#define WIFI_NAME "test_name"
#define WIFI_PASSWORD "test_pass"

// uncomment this if you need:
//#define DEVICE_NAME "test_esp8266" 
//#define DEVICE_PASSWORD "1234"

#define ENABLE_AVOCADO_ESP_WIFI_BOOT

#include <AVOCADO_esp.h>

AVOCADO_esp esp;

void setup() {
  Serial.begin(115200); // not necessary
  esp.setup();
}

void loop() {
  esp.update();
}
