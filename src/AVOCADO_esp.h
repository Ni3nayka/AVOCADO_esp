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

/*
// general
#include <ESP8266WiFi.h>

// OTA
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// gamepad
WiFiClient client;
*/

#ifndef WIFI_NAME
#error "You not defined WIFI_NAME"
#endif

#ifndef WIFI_PASSWORD
#error "You not defined WIFI_PASSWORD"
#endif

#include "OTA.h"
#include "monitor.h"

class AVOCADO_esp: public OTA, public AVOCADO_monitor {
  public:

    // general
    void setup();
    void update();
    
  private:
    // general

    // OTA

    // gamepad
    
};

void AVOCADO_esp::setup() {

  // general
  Serial.printf("AVOCADO_lib: Connecting to %s ", WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  // OTA
  #ifdef ENABLE_AVOCADO_ESP_WIFI_BOOT
  AVOCADO_esp::OTA_setup();
  #endif

  // monitor
  #if defined(ENABLE_AVOCADO_ESP_WIFI_MONITOR) || defined(ENABLE_AVOCADO_ESP_WIFI_GAMEPAD)
  AVOCADO_esp::monitor_setup();
  #endif

  // gamepad
  //#ifdef ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
  //AVOCADO_esp::gamepad_setup();
  //#endif
  
}

void AVOCADO_esp::update() {
  
  // OTA
  #ifdef ENABLE_AVOCADO_ESP_WIFI_BOOT
  AVOCADO_esp::OTA_update();
  #endif

  // monitor
  #if defined(ENABLE_AVOCADO_ESP_WIFI_MONITOR) || defined(ENABLE_AVOCADO_ESP_WIFI_GAMEPAD)
  AVOCADO_esp::monitor_update();
  #endif
  
  // gamepad
  //#ifdef ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
  //AVOCADO_esp::gamepad_update();
  //#endif
  
}
