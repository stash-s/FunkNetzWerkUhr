#include <Arduino.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <SPI.h>
#include <WiFiManager.h>

<<<<<<< HEAD
#define VFD 1
#define Nixie 2

#ifndef DISPLAY_HW
#define DISPLAY_HW Nixie
#endif // DISPLAY_HW

#if DISPLAY_HW == VFD
#include "vfd_display.h"
#elif DISPLAY_HW == Nixie
#include "nixie_display.h"
#else
#error "Unsupported or unknown display hardware: " #DISPLAY_HW
#endif // DISPLAY_HW

//#include "nixie_display.h"
=======
#include "clock_config.h"
>>>>>>> origin/hardware-reset
#include "light_sensor.h"

#ifdef AUSF_A
#include "ausf_a_display.h"
#elif defined(AUSF_B) || defined(AUSF_C)
#include "max_display.h"
#endif

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pl.pool.ntp.org", 2 * 3600, 236 * 1000);

int position = 0;

WiFiManager wifiManager;
<<<<<<< HEAD

Display *display = new DISPLAY_HW_CLASS();
=======
#if defined(AUSF_B) || defined(AUSF_C)
Display *display = new MaxDisplay();
#elif defined(AUSF_A)
Display *display = new AusfADisplay();
#endif
>>>>>>> origin/hardware-reset

LightSensor lightSensor;

void setup()
{
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

<<<<<<< HEAD
    //wifiManager.resetSettings();
=======
    // wifiManager.resetSettings();
>>>>>>> origin/hardware-reset
    Serial.begin(9600);

    Serial.println("Initializing display");

<<<<<<< HEAD
    display->init();
    display->setColor(255, 0, 0);
    display->startAnimation();

=======
>>>>>>> origin/hardware-reset
    lightSensor.onLevelSet([](int value) {
#ifdef DEBUG
        Serial.print("light sensor: level set: ");
        Serial.println(value);
#endif
        display->setBrightness(value);
    });

<<<<<<< HEAD
    wifiManager.setAPCallback([](WiFiManager *mgr) {
        display->setColor(0, 0, 255);
        display->startAnimation();
    });
    wifiManager.setConfigPortalTimeout(180);

    Serial.println("connecting...");
    if (wifiManager.autoConnect("AutoconnectAP"))
    {
        Serial.println("connected ... yay!");
    }
    else
    {
=======
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
>>>>>>> origin/hardware-reset
        Serial.println("connection failed, rebooting");
        ESP.restart();
    }
    display->setColor(0, 255, 0);
    display->startAnimation();

<<<<<<< HEAD
    timeClient.onStartUpdate([]() {
        Serial.println("NTP update started");
        display->setColor(0, 255, 0);
        display->startAnimation();
    });
    timeClient.onEndUpdate([]() {
        Serial.println("NTP update complete");
        display->setColor(0, 128, 128);
        display->stopAnimation();
    });
=======
    timeClient.onStartUpdate([]() { display->setColor(0, 255, 0, false); });
    timeClient.onEndUpdate([]() { display->setColor(0, 128, 128, true); });
>>>>>>> origin/hardware-reset

    timeClient.begin();

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
        {
            type = "sketch";
        }
        else
        { // U_SPIFFS
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
<<<<<<< HEAD
        if (error == OTA_AUTH_ERROR)
        {
            Serial.println("Auth Failed");
        }
        else if (error == OTA_BEGIN_ERROR)
        {
            Serial.println("Begin Failed");
        }
        else if (error == OTA_CONNECT_ERROR)
        {
=======
        if (error == OTA_AUTH_ERROR) {
            Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
>>>>>>> origin/hardware-reset
            Serial.println("Connect Failed");
        }
        else if (error == OTA_RECEIVE_ERROR)
        {
            Serial.println("Receive Failed");
        }
        else if (error == OTA_END_ERROR)
        {
            Serial.println("End Failed");
        }
    });
    ArduinoOTA.begin();

    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    // put your main code here, to run repeatedly:
    lightSensor.handle();

    static int ntpFailCount = 0;

<<<<<<< HEAD
    if (timeClient.update())
    {

        ntpFailCount = 0;
        //Serial.println (timeClient.getFormattedTime());
=======
    if (timeClient.update()) {
        // Serial.println ("time client update succesful");

        ntpFailCount = 0;
        // Serial.println (timeClient.getFormattedTime());
>>>>>>> origin/hardware-reset

        display->setDigit(0, timeClient.getHours() / 10);
        display->setDigit(1, timeClient.getHours() % 10);
        display->setDigit(2, timeClient.getMinutes() / 10);
        display->setDigit(3, timeClient.getMinutes() % 10);
<<<<<<< HEAD
    }
    else
    {

        ++ntpFailCount;

        if (ntpFailCount > 5)
        {
=======

    } else {
        Serial.println("failed ntp update");

        ++ntpFailCount;

        if (ntpFailCount > 5) {
            Serial.println("Number of failures exceeded limit, rebooting");
            Serial.println(
                "2nd time Number of failures exceeded limit, rebooting");
>>>>>>> origin/hardware-reset
            ESP.restart();
        }
    }

    ArduinoOTA.handle();
}
