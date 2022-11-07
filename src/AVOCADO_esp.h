/*
   Write for pack lib AVOCADO_esp:
   https://github.com/Ni3nayka/AVOCADO_esp

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
#include "gamepad.h"

class AVOCADO_esp: public OTA, public AVOCADO_gamepad_esp8266_nodeMCU {
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
  
  #ifdef ENABLE_AVOCADO_ESP_WIFI_BOOT
  AVOCADO_esp::OTA_setup();
  #endif
  
  #ifdef ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
  AVOCADO_esp::gamepad_setup();
  #endif
  
}

void AVOCADO_esp::update() {
  
  #ifdef ENABLE_AVOCADO_ESP_WIFI_BOOT
  AVOCADO_esp::OTA_update();
  #endif
  
  #ifdef ENABLE_AVOCADO_ESP_WIFI_GAMEPAD
  AVOCADO_esp::gamepad_update();
  #endif
  
}
