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

#define ENABLE_AVOCADO_ESP_WIFI_GAMEPAD

#include <AVOCADO_esp.h>

AVOCADO_esp esp;

void setup() {
  Serial.begin(115200);
  esp.setup();
}

void loop() {
  esp.update();
  
  // button
  for (int i = 0; i<GAMEPAD_BUTTON_QUANTITY; i++) {
    Serial.print(esp.gamepad_button[i]); // bool
  }

  Serial.print(" <> ");
  
  // allow
  for (int i = 0; i<GAMEPAD_ARROW_QUANTITY; i++) {
    Serial.print(esp.gamepad_arrow[i]); // int
    Serial.print(" ");
  }
  
  Serial.print(" <> ");
  
  // joystick
  for (int i = 0; i<GAMEPAD_JOYSTICK_QUANTITY; i++) {
    Serial.print(esp.gamepad_joystick[i]); // int
    Serial.print(" ");
  }
    
  Serial.println();
}
