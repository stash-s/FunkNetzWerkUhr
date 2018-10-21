#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <NTPClient.h>
#include <SPI.h>

#include "max_display.h"
#include "light_sensor.h"

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 2 * 3600, 10 * 1000);

int position=0;

WiFiManager wifiManager;
Display * display = new MaxDisplay();

LightSensor lightSensor;

void setup() {
    // put your setup code here, to run once:
    pinMode (LED_BUILTIN, OUTPUT);
    digitalWrite (LED_BUILTIN, LOW);

    //wifiManager.resetSettings();
    Serial.begin (9600);

    display->init();
    display->setColor(255, 0, 0, false);

    // lightSensor.onReading([](int value) {
    //     display.setDigit (0,  value / 1000);
    //     display.setDigit (1, (value % 1000) / 100);
    //     display.setDigit (2, (value % 100)  / 10);
    //     display.setDigit (3, (value % 10));
    // });

    lightSensor.onLevelSet([](int value) {
        display->setBrightness(value);
        // display.setDigit (0,  value / 1000);
        // display.setDigit (1, (value % 1000) / 100);
        // display.setDigit (2, (value % 100)  / 10);
        // display.setDigit (3, (value % 10));
    });

    wifiManager.setAPCallback([](WiFiManager * mgr){
        display->setColor(0, 0, 255, false);
    });

    Serial.println ("connecting...");
    wifiManager.autoConnect ("AutoconnectAP");
    Serial.println ("connected ... yay!");
    display->setColor(0, 255, 0, false);

    timeClient.onStartUpdate ([](){ display->setColor (0,255,0,false); });
    timeClient.onEndUpdate ([](){ 
        display->setColor(0, 128, 128, true); });

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

        if (ntpFailCount > 2) {
            ESP.restart();
        }
    }

    ArduinoOTA.handle();
}
