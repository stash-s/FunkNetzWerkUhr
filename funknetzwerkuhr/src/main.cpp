#include <Arduino.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ezTime.h>
#include <SPI.h>
#include <WiFiManager.h>

#include "clock_config.h"
#include "light_sensor.h"

#ifdef AUSF_A
#include "ausf_a_display.h"
#elif defined(AUSF_B) || defined(AUSF_C)
#include "max_display.h"
#endif

int position = 0;

WiFiManager wifiManager;
#if defined(AUSF_B) || defined(AUSF_C)
Display *display = new MaxDisplay();
#elif defined(AUSF_A)
Display *display = new AusfADisplay();
#endif

Timezone poland;
LightSensor lightSensor;

void setup() {
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // wifiManager.resetSettings();
    Serial.begin(9600);

    display->init();
    display->setColor(255, 0, 0, false);

    lightSensor.onLevelSet([](int value) {
#ifdef DEBUG
        Serial.print("light sensor: level set: ");
        Serial.println(value);
#endif
        display->setBrightness(value);
    });

#ifdef DEBUG
    lightSensor.onReading([](int value) {
        Serial.print("light sensor: value seen: ");
        Serial.println(value);
    });
#endif
    lightSensor.handle();
    
    wifiManager.setAPCallback(
        [](WiFiManager *mgr) { display->setColor(0, 0, 255, false); });
    wifiManager.setConfigPortalTimeout(180);

    Serial.println("connecting...");
    if (wifiManager.autoConnect("AutoconnectAP")) {
        Serial.println("connected ... yay!");
    } else {
        Serial.println("connection failed, rebooting");
        ESP.restart();
    }
    display->setColor(0, 255, 0, false);

    if (!poland.setCache(0)) {
        poland.setLocation("Europe/Warsaw");
    }

    ezt::onNtpUpdateStart([]() {
        Serial.println("NTP Update started ....");
        display->setColor(0, 255, 0, false);
    });
    ezt::onNtpUpdateEnd([](bool result) {
        Serial.println("NTP update finished.");
        display->setColor(0, 128, 128, true);
    });

    ezt::waitForSync();

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else { // U_SPIFFS
            type = "filesystem";
        }

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS
        // using SPIFFS.end()
        Serial.println("Start updating " + type);

        display->shutdown();
    });

    ArduinoOTA.onEnd([]() { Serial.println("\nEnd"); });
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

    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    lightSensor.handle();

    ezt::events();
    display->setDigit(0, poland.hour() / 10);
    display->setDigit(1, poland.hour() % 10);
    display->setDigit(2, poland.minute() / 10);
    display->setDigit(3, poland.minute() % 10);

    ArduinoOTA.handle();
}
