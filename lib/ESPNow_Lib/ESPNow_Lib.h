#ifndef ESP_NOW_LIBRARIES_H
#define ESP_NOW_LIBRARIES_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

class ESPNow_Lib {
        public:
                ESPNow_Lib();

                void begin();

                uint32_t getTimes();

        private:

};

typedef struct {
    uint8_t vMois1;     // Soil Mois1
    uint8_t vMois2;     // Soil Mois2
    uint8_t vMois3;     // Soil Mois3
    uint8_t vMois4;     // Soil Mois4
    uint8_t vMoisAv;    // Soil Mois Average
    
    uint8_t vTemp;      // DHT Air Temperature
    uint8_t vHum;       // DHT Air Humidity
} dataSensor;

extern dataSensor data_espnow;

#endif
