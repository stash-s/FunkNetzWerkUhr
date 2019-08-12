#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <NTPClient.h>
#include <SPI.h>
#include <FS.h>

#include "appconfig.h"
#include "clock_config.h"

#include "nixie_display.h"
#include "vfd_display.h"
#include "light_sensor.h"

#define HTTP_REST_PORT 80
#define STRING_SIZE 32
#define DBG_OUTPUT_PORT Serial


WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pl.pool.ntp.org", 2 * 3600, 236 * 1000);

int position = 0;

WiFiManager wifiManager;

ESP8266WebServer http_rest_server(HTTP_REST_PORT);


AppConfig config;
Display *display; // = new DISPLAY_HW_CLASS();

LightSensor lightSensor;

#ifdef NIXIE_AUSF_C
#warning we are nixie C
#endif

// flag for saving data
bool shouldSaveConfig = false;
bool needRestart = false;

String getContentType(String filename) {
  if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

void config_rest_server_routing() {
    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.send(200, "text/html",
                              "Welcome to the ESP8266 REST Web Server");
    });

    http_rest_server.on("/reset", HTTP_GET, []() {
        Serial.println("reset called");

        http_rest_server.send(200, "text/html", "Calling reset");
        needRestart = true;
    });

    http_rest_server.on("/timezone", HTTP_GET, []() {
        http_rest_server.send(200, "text/html", config.getTimeZone());
    });

    http_rest_server.on("/foo", HTTP_GET, []() {
        if ( ! http_rest_server.hasArg ("dir") ) {
            http_rest_server.send (500,"text/plain", "BAD ARGUMENTS");
            return;
        }

        String path = http_rest_server.arg("dir");
        DBG_OUTPUT_PORT.println("handleFileList: " + path);
        Dir dir = SPIFFS.openDir(path);
        path = String();

        String output = "[";

        while (dir.next()) {
            File entry = dir.openFile ("r");
            if (output != "[") {
                output += ','; 
            }
            bool isDir = false;
            output += "{\"type\":\"";
            output += (isDir) ? "dir" : "file";
            output += "\",\"name\":\"";
            output += String(entry.name()).substring(1);
            output += "\"}";
            entry.close();
        }

        output += "]";

        http_rest_server.send(200, "text/html", output);
    });

    http_rest_server.on("/file-read", HTTP_GET, []() {
        String path = http_rest_server.arg("path");
        DBG_OUTPUT_PORT.println("handleFileRead: " + path);
        if (path.endsWith("/")) {
            path += "index.htm";
        }
        String contentType = getContentType(path);
        String pathWithGz = path + ".gz";
        if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
            if (SPIFFS.exists(pathWithGz)) {
                path += ".gz";
            }
            File file = SPIFFS.open(path, "r");
            http_rest_server.streamFile(file, contentType);
            file.close();
            return true;
        }
        return false;
    });
}


void setup()
{
    Serial.begin(9600);

    DBG_OUTPUT_PORT.println ("Setup started");

    config.restore ();

    switch (config.getHardwareVariant()) {
        case VFD:
            display = new VfdDisplay (config);
            break;

        case NIXIE_AUSF_A:
        case NIXIE_AUSF_C:
        case NIXIE_AUSF_D:
            display = new NixieDisplay (config);
            break;
    }
    
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    //wifiManager.resetSettings();
    

    Serial.println("Initializing display");

    display->init();
    display->setColor(255, 0, 0);
    display->startAnimation();

    lightSensor.onLevelSet([](int value) {
        display->setBrightness(value);
    });

    wifiManager.setAPCallback([](WiFiManager *mgr) {
        display->setColor(0, 0, 255);
        display->startAnimation();
    });
    wifiManager.setConfigPortalTimeout(180);

    wifiManager.setSaveConfigCallback([&]() {
        config.save();
    });

    wifiManager.setHostname(config.getNodeId().c_str());

    Serial.println("connecting...");
    if (wifiManager.autoConnect("AutoconnectAP"))
    {
        Serial.println("connected ... yay!");
    }
    else
    {
        Serial.println("connection failed, rebooting");
        ESP.restart();
    }
    display->setColor(0, 255, 0);
    display->startAnimation();

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

    config_rest_server_routing();
    http_rest_server.begin();

    digitalWrite(LED_BUILTIN, HIGH);
}

void loop()
{
    // put your main code here, to run repeatedly:
    lightSensor.handle();

    static int ntpFailCount = 0;

    if (timeClient.update())
    {

        ntpFailCount = 0;
        //Serial.println (timeClient.getFormattedTime());

        display->setDigit(0, timeClient.getHours() / 10);
        display->setDigit(1, timeClient.getHours() % 10);
        display->setDigit(2, timeClient.getMinutes() / 10);
        display->setDigit(3, timeClient.getMinutes() % 10);
    }
    else
    {

        ++ntpFailCount;

        if (ntpFailCount > 5)
        {
            ESP.restart();
        }
    }

    ArduinoOTA.handle();
    http_rest_server.handleClient();

    if (needRestart) {
        delay(1000);
        wifiManager.resetSettings();
        wifiManager.erase();
        delay(1000);
        ESP.restart();
    }
}
