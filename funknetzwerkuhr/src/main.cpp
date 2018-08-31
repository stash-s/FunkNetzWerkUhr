#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <NTPClient.h>
#include <SPI.h>

#include "max_display.h"

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 2 * 3600, 20);

int position=0;

WiFiManager wifiManager;
MaxDisplay display;

void setup() {
    // put your setup code here, to run once:
    pinMode (LED_BUILTIN, OUTPUT);
    digitalWrite (LED_BUILTIN, LOW);

    Serial.begin (9600);


    //wifiManager.resetSettings();

    Serial.println ("connecting...");
    wifiManager.autoConnect ("AutoconnectAP");
    Serial.println ("connected ... yay!");

    timeClient.begin();

    ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
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


  // tutaj
  display.init();

  //pinMode (15, OUTPUT);
  //digitalWrite (15, HIGH);

  digitalWrite (LED_BUILTIN, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (timeClient.update()) {
    //     Serial.println (timeClient.getFormattedTime());
    // }
    //    auto time = timeClient.getFormattedTime();
    //    memcpy (&payload, time.c_str(), sizeof(payload));
    }

    ArduinoOTA.handle();
    //digitalWrite (LED_BUILTIN, HIGH);
    //delay(1000);
    //digitalWrite (LED_BUILTIN, LOW);
    //delay(1000);
}
