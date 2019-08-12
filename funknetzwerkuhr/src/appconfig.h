#pragma once

#include <Arduino.h>

enum HardwareVariant : int {
    VFD,
    NIXIE_AUSF_A,
    NIXIE_AUSF_C,
    NIXIE_AUSF_D
};

#define CONFIG_FILE "/config.json"
#define DEFAULT_TIMEZONE "Europe/Warsaw"
#define DEFAULT_OFFSET 7200
#define DEFAULT_HOSTNAME "misio"
#define DEFAULT_TIMEZONEDB_API_KEY "U8GFP5SX0PJB"
#define DEFAULT_HW_VARIANT NIXIE_AUSF_C
#define CONF_JSON_SIZE JSON_OBJECT_SIZE(5)

class AppConfig {
   public:
    AppConfig();

    void save();
    void restore();

    const String &getTimeZone() const;
    void setTimeZone(const String &);

    const String &getNodeId() const;
    void setNodeId(const String &);

    int getGmtOffset() const;
    void setGmtOffset(int);

    const String &getTimezonedbApiKey() const;
    void setTimezonedbApiKey(const String &);

    HardwareVariant getHardwareVariant () const;
    void setHardwareVariant (HardwareVariant);

    uint8_t getDigitsCount () const;

    uint8_t getShutdownPin () const;
    uint8_t getFilamentPin () const;

   private:
    String _timezone;
    String _apiKey;

    String _nodeId;
    int _gmtOffset;

    HardwareVariant _hardwareVariant;
};

inline void AppConfig::setTimeZone(const String &timeZone) {
    _timezone = timeZone;
}
inline const String &AppConfig::getTimeZone() const { return _timezone; }

inline void AppConfig::setNodeId(const String &nodeId) { _nodeId = nodeId; }
inline const String &AppConfig::getNodeId() const { return _nodeId; }

inline int AppConfig::getGmtOffset() const { return _gmtOffset; }
inline void AppConfig::setGmtOffset(int gmtOffset) { _gmtOffset = gmtOffset; }

inline const String &AppConfig::getTimezonedbApiKey() const { return _apiKey; }
inline void AppConfig::setTimezonedbApiKey(const String &apiKey) {
    _apiKey = apiKey;
};

inline HardwareVariant AppConfig::getHardwareVariant () const {
    return _hardwareVariant;
}

inline void AppConfig::setHardwareVariant (HardwareVariant variant) {
    _hardwareVariant = variant;
}

inline uint8_t AppConfig::getDigitsCount () const {
    return 4; // magic!
}
