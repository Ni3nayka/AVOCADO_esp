/*
   Write for project AVOCADO:
   https://github.com/Ni3nayka/AVOCADO

   author: Egor Bakay <egor_bakay@inbox.ru>
   write:  november 2022
   modify: november 2022
*/

#pragma once

#include <ESP8266WiFi.h>

WiFiClient client;

#define JOYSTICK_QUANTITY 10
#define BUTTON_QUANTITY 30
#define ARROW_QUANTITY 10

class AVOCADO_gamepad_esp8266_nodeMCU {
  public:

    void setup();
    void update();

    String input_data;

    int joystick[JOYSTICK_QUANTITY];
    bool button[BUTTON_QUANTITY];
    int arrow[ARROW_QUANTITY];

  private:

    void update_data();
    void clear_arrays();
};

void AVOCADO_gamepad_esp8266_nodeMCU::setup() {
  Serial.printf("Connecting to %s ", WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void AVOCADO_gamepad_esp8266_nodeMCU::update() {
  if (!(client.connected() || client.available())) {
    Serial.println("error connect - restart");
    client.stop();
    client.connect(SERVER_IP, SERVER_PORT);
    input_data = "";
    AVOCADO_gamepad_esp8266_nodeMCU::clear_arrays();
  }
  
  while (client.available()) {
    input_data = client.readStringUntil('\n');
    AVOCADO_gamepad_esp8266_nodeMCU::update_data();
  }
}

int number(char a) {
  if      (a=='1') return 1;
  else if (a=='2') return 2;
  else if (a=='3') return 3;
  else if (a=='4') return 4;
  else if (a=='5') return 5;
  else if (a=='6') return 6;
  else if (a=='7') return 7;
  else if (a=='8') return 8;
  else if (a=='9') return 9;
  else return 0;
}

void AVOCADO_gamepad_esp8266_nodeMCU::clear_arrays() {
  for (int i = 0; i<JOYSTICK_QUANTITY; i++) joystick[i] = 0;
  for (int i = 0; i<BUTTON_QUANTITY; i++) button[i] = 0;
  for (int i = 0; i<ARROW_QUANTITY; i++) arrow[i] = 0;
}

void AVOCADO_gamepad_esp8266_nodeMCU::update_data() {
  AVOCADO_gamepad_esp8266_nodeMCU::clear_arrays();
  
  int flag = 0;
  //  { joystick: 0 0 0 0 button: 000000000000 arrow: 0 0 }
  for (int i = 0; input_data[i]!='\n' && input_data[i]!='}' && input_data[i]!=0; i++) {
    char c = input_data[i];
    if      (c=='{') flag = 1;
    else if (c=='}') flag = 1000;
    else if (c=='j') flag = 199;
    else if (c=='b') flag = 299;
    else if (c=='a') flag = 399;
    else if (c==':') {
      i++;
      flag++; 
      // continue;
    }
    else if (flag>100 && flag<1000 && flag%100!=99) {
      if (c==' ' || flag>=300 && flag<400) flag++;
      if (c==' ') {}
      else if (flag>=400) {
        if (c=='-') {
          arrow[flag-400] = -1;
          i++;
        }
        else if (c=='1') arrow[flag-400] = 1;
      }
      else if (flag>=300) button[flag-301] = number(c);
      else if (flag>=200) {
        int n = flag-200;
        if (joystick[n]==0 && input_data[i-1]=='-') joystick[n] = number(c)*(-1);
        else joystick[n] = joystick[n]*10 + number(c)*(joystick[n]>=0?1:-1);
      }
    }
  }
}
