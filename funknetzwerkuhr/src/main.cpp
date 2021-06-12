#include <Arduino.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ezTime.h>
#include <SPI.h>

#include <ESPAsyncWebServer.h> //Local WebServer used to serve the configuration portal
#include <ESPAsyncWiFiManager.h> //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "clock_config.h"
#include "light_sensor.h"
#include "delay.hpp"

#ifdef AUSF_A
#include "ausf_a_display.h"
#elif defined(AUSF_B) || defined(AUSF_C)
#include "max_display.h"
#endif

int position = 0;

AsyncWebServer server(80);
DNSServer dns;

Delay delayer;

#if defined(AUSF_B) || defined(AUSF_C)
Display *display = new MaxDisplay();
#elif defined(AUSF_A)
Display *display = new AusfADisplay();
#endif

Timezone poland;
LightSensor lightSensor;

void deviceReset() {
    delay(3000);
    ESP.reset();
    delay(5000);
}

void setup() {
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

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

    AsyncWiFiManager wifiManager(&server, &dns);

    WiFi.persistent(true);

    //wifiManager.setDebugOutput(true);
    // wifiManager.setConnectTimeout(10);
    wifiManager.setConfigPortalTimeout(180);
    wifiManager.setSaveConfigCallback([]() {
        Serial.println("connection successful (ap connection saved)");
    });

    wifiManager.setAPCallback(
        [](AsyncWiFiManager *mgr) { display->setColor(0, 0, 255, false); });

    // exit after config instead of connecting
    wifiManager.setBreakAfterConfig(true);

    Serial.println("connecting...");
    // tries to connect to last known settings
    // if it does not connect it starts an access point with the specified name
    // here  "AutoConnectAP" with password "password"
    // and goes into a blocking loop awaiting configuration
    if (!wifiManager.autoConnect("funknetzwerkuhr")) {
        Serial.println(
            "failed to connect, we should reset as see if it connects");
        delay(3000);
        ESP.reset();
        delay(5000);
    }

    Serial.println("connected ... yay!");
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

    server.reset();

    server.on("/", [](AsyncWebServerRequest *request) {
        Serial.println("/ requested");
        request->send(200, "text/plain", "root - success");
    });

    server.on("/reset-wifi", [&](AsyncWebServerRequest *request) {
        Serial.println("requested a reset");
        request->send(200, "text/plain", "wifi reset - success");

        Serial.println("rebooting");
        delayer.delay([]() {
            WiFi.persistent(true);
            WiFi.disconnect();
            Serial.println("rebooting now");
            ESP.restart();
        });
    });

    server.on("/restart", [&](AsyncWebServerRequest *request) {
        Serial.println("reboot requested");
        request->send(200, "text/plain", "reboot - success");
        delayer.delay([]() {
            Serial.println("restarting now");
            ESP.restart();
        });
    });

    server.on("/reset", [&](AsyncWebServerRequest *request) {
        Serial.println("reboot requested");
        request->send(200, "text/plain", "reset - success");
        delayer.delay([]() {
            Serial.println("resetting now");
            ESP.reset();
        });
    });

    server.begin();


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

    display->handle();

    delayer.handle();

    //server->handleClient();
}
