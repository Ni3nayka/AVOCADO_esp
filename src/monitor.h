/*
   Write for pack lib AVOCADO_esp:
   https://github.com/Ni3nayka/AVOCADO_esp
   
   Write for project AVOCADO:
   https://github.com/Ni3nayka/AVOCADO

   author: Egor Bakay <egor_bakay@inbox.ru>
   write:  november 2022
   modify: november 2022
*/

#pragma once

#if defined(ENABLE_AVOCADO_ESP_WIFI_MONITOR) || defined(ENABLE_AVOCADO_ESP_WIFI_GAMEPAD)
//#ifdef ENABLE_AVOCADO_ESP_WIFI_MONITOR

#ifndef SERVER_IP
#error "You not defined SERVER_IP"
#endif

#ifndef SERVER_PORT
#error "You not defined SERVER_PORT"
#endif

#include <ESP8266WiFi.h>

WiFiClient client;

#include "gamepad.h"

class AVOCADO_monitor: public AVOCADO_gamepad_translater {
  public:

    void monitor_setup();
    void monitor_update();

    #ifdef ENABLE_AVOCADO_ESP_WIFI_MONITOR
    int available();
    String read();
    void print(String message);
    #endif

  private:

    #ifdef ENABLE_AVOCADO_ESP_WIFI_MONITOR
    String monitor_input_data;
    String send_message;
    #endif
    
};

void AVOCADO_monitor::monitor_setup() {
  //available_counter = 0;
  if (WiFi.status() == WL_CONNECTED) return;
  Serial.printf("AVOCADO_lib: Connecting to %s ", WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void AVOCADO_monitor::monitor_update() {
  if (!(client.connected() || client.available())) {
    Serial.println("AVOCADO_lib: error connect - restart");
    client.stop();
    client.connect(SERVER_IP, SERVER_PORT);
    
    #ifdef ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
    gamepad_clear_arrays();
    #endif
  }
  
  while (client.available()) {
   String last_input_data = client.readStringUntil('\n') + '\n';

    #ifdef ENABLE_AVOCADO_ESP_WIFI_MONITOR
    monitor_input_data += last_input_data;
    #endif
    
    #ifdef ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
    gamepad_update_data(last_input_data);
    #endif
  }

  if (send_message!="" && client.connected()) {
    client.print(send_message);
    send_message = "";
  }
}

#ifdef ENABLE_AVOCADO_ESP_WIFI_MONITOR

int AVOCADO_monitor::available() {
  //return available_counter;
  unsigned int a = 0;
  for (unsigned long int i = 0; i<monitor_input_data.length(); i++) {
    if (monitor_input_data[i]=='\n')
      a++;
  }
  return a;
}

String AVOCADO_monitor::read() {
  if (monitor_input_data.length()==0) return "";
  String answer = "";
  String monitor_input_data_cache = monitor_input_data;
  monitor_input_data = "";
  unsigned long int i = 0;
  for (;monitor_input_data_cache[i]!='\n'; i++) {
    answer += monitor_input_data_cache[i];
    if (i+1>=monitor_input_data_cache.length()) break;
  }
  // monitor_input_data.replace(answer+'\n',"");
  i++;
  for (;i<monitor_input_data_cache.length(); i++) {
    monitor_input_data += monitor_input_data_cache[i];
  }
  //available_counter--;
  return answer;
}

void AVOCADO_monitor::print(String message) {
  send_message += message + '\n';
}

#endif

#else
class AVOCADO_monitor {};
#endif
