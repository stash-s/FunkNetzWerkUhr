#include "appconfig.h"

#include <ArduinoJson.h>
#include <FS.h>

AppConfig::AppConfig()
    : _timezone(DEFAULT_TIMEZONE),
      _apiKey(DEFAULT_TIMEZONEDB_API_KEY),
      _nodeId(DEFAULT_HOSTNAME),
      _gmtOffset(DEFAULT_OFFSET) {}

void AppConfig::restore() {
    if (SPIFFS.begin()) {
        Serial.println("mounted file system");
        if (SPIFFS.exists(CONFIG_FILE)) {
            Serial.println("Config file exists.");
            File configFile = SPIFFS.open(CONFIG_FILE, "r");
            if (configFile) {
                Serial.println("opened config file");
                size_t size = configFile.size();
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);

                StaticJsonDocument<CONF_JSON_SIZE> jsonDocument;
                DeserializationError err =
                    deserializeJson(jsonDocument, buf.get());

                if (err) {
                    Serial.print(F("deserializeJson failed with code: "));
                    Serial.println(err.c_str());
                }

                serializeJsonPretty (jsonDocument, Serial);
                
                setTimeZone(jsonDocument["timezone"].as<char *>());
                setNodeId(jsonDocument["hostname"].as<char *>());
                setGmtOffset(jsonDocument["offset"].as<int>());
                auto apiKey = jsonDocument["apikey"].as<char *>();
                if (apiKey) {
                    setTimezonedbApiKey(apiKey);
                }
                setHardwareVariant (HardwareVariant(jsonDocument["hardware"].as<int>()));

                Serial.println("Got this from saved data: ");
                serializeJsonPretty(jsonDocument, Serial);
                Serial.println();

                configFile.close();
            }
        } else {
            Serial.println("file does not exist");
        }
    } else {
        Serial.println("failed to mount FS");
    }
}

void AppConfig::save() {
    StaticJsonDocument<CONF_JSON_SIZE> doc;

    doc["timezone"].set(getTimeZone().c_str());
    doc["hostname"].set(getNodeId().c_str());
    doc["offset"].set(getGmtOffset());
    doc["apikey"].set(getTimezonedbApiKey().c_str());
    doc["hardware"].set(int(getHardwareVariant()));

    File configFile = SPIFFS.open(CONFIG_FILE, "w");
    if (!configFile) {
        Serial.println("failed to open config file for writing");
    }
    serializeJsonPretty(doc, Serial);
    serializeJson(doc, configFile);
    configFile.close();
}


uint8_t AppConfig::getShutdownPin () const {
    switch (getHardwareVariant()) {
        case VFD:
            return 4;

        default:
            return 0;
    }
}

uint8_t AppConfig::getFilamentPin () const {
switch (getHardwareVariant()) {
        case VFD:
            return 5;

        default:
            return 0;
    }
}