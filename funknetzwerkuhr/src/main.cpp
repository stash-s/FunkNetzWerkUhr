#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <NTPClient.h>
#include <SPI.h>

#define VFD 1
#define Nixie 2

#ifndef DISPLAY_HW
#  define DISPLAY_HW Nixie
#endif // DISPLAY_HW

#if DISPLAY_HW==VFD 
#  include "vfd_display.h"
#elif DISPLAY_HW==Nixie
#  include "nixie_display.h"
#else 
#  error "Unsupported or unknown display hardware: " #DISPLAY_HW
#endif // DISPLAY_HW

//#include "nixie_display.h"
#include "light_sensor.h"

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 1 * 3600, 236 * 1000);

int position=0;

WiFiManager wifiManager;

Display * display = new DISPLAY_HW_CLASS ();

LightSensor lightSensor;

void setup() {
    // put your setup code here, to run once:
    pinMode (LED_BUILTIN, OUTPUT);
    digitalWrite (LED_BUILTIN, LOW);

    //wifiManager.resetSettings();
    Serial.begin (9600);

    display->init();
    display->setColor(255, 0, 0);
    display->startAnimation();

    lightSensor.onLevelSet([](int value) {
        display->setBrightness(value);
    });

    wifiManager.setAPCallback([](WiFiManager * mgr){
        display->setColor(0, 0, 255);
        display->startAnimation();
    });
    wifiManager.setConfigPortalTimeout (180);
    
    Serial.println ("connecting...");
    if (wifiManager.autoConnect ("AutoconnectAP")) {
        Serial.println ("connected ... yay!");
    } else {
        Serial.println ("connection failed, rebooting");
        ESP.restart();
    }
    display->setColor(0, 255, 0);
    display->startAnimation();

    timeClient.onStartUpdate ([](){ 
        display->setColor (0,255,0);
        display->startAnimation();
    });
    timeClient.onEndUpdate ([](){ 
        display->setColor(0, 128, 128);
        display->stopAnimation();
    });

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

        display->shutdown();
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

    digitalWrite (LED_BUILTIN, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    lightSensor.handle ();

    static int ntpFailCount=0;

    if (timeClient.update()) {

        ntpFailCount=0;
        //Serial.println (timeClient.getFormattedTime());

        display->setDigit(0, timeClient.getHours() / 10);
        display->setDigit(1, timeClient.getHours() % 10);
        display->setDigit(2, timeClient.getMinutes() / 10);
        display->setDigit(3, timeClient.getMinutes() % 10);

    } else {

        ++ntpFailCount;

        if (ntpFailCount > 5) {
            ESP.restart();
        }
    }

    ArduinoOTA.handle();
}
