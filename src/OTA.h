/*
   Write for wifi_boot_esp lib:
   https://github.com/Ni3nayka/wifi_boot_esp

   link:
   https://wikihandbk.com/wiki/ESP8266:Примеры/Прошивка_ESP8266_методом_OTA

   python 2.7.7:
   https://www.python.org/downloads/release/python-277/

   author: Egor Bakay <egor_bakay@inbox.ru>
   write:  november 2022
   modify: June 2023
*/

#pragma once

#ifdef ENABLE_AVOCADO_ESP_WIFI_BOOT

#if defined(ESP32)
  #include <WiFi.h>
  #include <ESPmDNS.h>
#endif
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif

#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class OTA {
  public:
  
    void OTA_setup();
    void OTA_update();
    
  private:
    
};

void OTA::OTA_setup() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("AVOCADO_lib: Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("AVOCADO_lib: Connection Failed! Rebooting...");
      delay(500);
      ESP.restart();
    }
  }

  // Port defaults to 8266 (esp8266) or 3232 (esp32)
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID] or esp3232-[MAC]
  #ifdef DEVICE_NAME
  ArduinoOTA.setHostname(DEVICE_NAME);
  #endif

  // No authentication by default
  #ifdef DEVICE_PASSWORD
  ArduinoOTA.setPassword(DEVICE_PASSWORD);
  #endif

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("AVOCADO_lib: Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nAVOCADO_lib: End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("AVOCADO_lib: Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("AVOCADO_lib: Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("AVOCADO_lib: Ready");
  Serial.print("AVOCADO_lib: IP address: ");
  Serial.println(WiFi.localIP());  
}

void OTA::OTA_update() {
  ArduinoOTA.handle();
}

#else
class OTA {};
#endif
