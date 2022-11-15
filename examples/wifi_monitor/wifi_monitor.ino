/*
   Write for pack lib AVOCADO_esp:
   https://github.com/Ni3nayka/AVOCADO_esp

   windows PC client:
   https://github.com/Ni3nayka/AVOCADO/releases

   author: Egor Bakay <egor_bakay@inbox.ru>
   write:  november 2022
   modify: november 2022
*/

#define WIFI_NAME "test_name"
#define WIFI_PASSWORD "test_pass"

#define SERVER_IP "192.168.1.82"
#define SERVER_PORT 1234

#define ENABLE_AVOCADO_ESP_WIFI_MONITOR

#include <AVOCADO_esp.h>

AVOCADO_esp esp;

void setup() {
  Serial.begin(115200);
  esp.setup();
}

void loop() {
  esp.update();

  if (esp.available()) {
    String input_data = esp.read();
    Serial.println(input_data);
    esp.print("Hello!");
  }
}
