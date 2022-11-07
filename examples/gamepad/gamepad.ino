#define WIFI_NAME "DIR-803B"
#define WIFI_PASSWORD "asdgszdfgfsdh"

#define SERVER_IP "192.168.1.82"
#define SERVER_PORT 1234

#include "AVOCADO_gamepad_esp8266_nodeMCU.h"

AVOCADO_gamepad_esp8266_nodeMCU gamepad;

void setup() {
  Serial.begin(115200);
  Serial.println();

  gamepad.setup();
}

String sss = "";

void loop() {
  gamepad.update();
  if (sss!=gamepad.input_data) { // if only have different data
    sss = gamepad.input_data;
    
    // button
    for (int i = 0; i<BUTTON_QUANTITY; i++) Serial.print(gamepad.button[i]);

    Serial.print(" <> ");
    
    // allow
    for (int i = 0; i<ARROW_QUANTITY; i++) {
      Serial.print(gamepad.arrow[i]);
      Serial.print(" ");
    }
    
    Serial.print(" <> ");
    
    // joystick
    for (int i = 0; i<JOYSTICK_QUANTITY; i++) {
      Serial.print(gamepad.joystick[i]);
      Serial.print(" ");
    }
    
    Serial.print(" <> ");

    // original data
    Serial.println(gamepad.input_data);
  }
}
