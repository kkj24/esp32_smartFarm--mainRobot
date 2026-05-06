#include "ESPNow_Lib.h"

dataSensor data_espnow;

volatile uint32_t times_espnow = 0;

void dataRecv(const uint8_t *mac, const uint8_t *dataBytes, int length) {
    memcpy(&data_espnow, dataBytes, sizeof(data_espnow));
    times_espnow = millis();
}

ESPNow_Lib::ESPNow_Lib() {
    // No Once Func at Here
};

void ESPNow_Lib::begin() {
    if(esp_now_init() != ESP_OK) {
        while(esp_now_init() != ESP_OK) {
            Serial.println(F("ESP-Now Initializing"));
            esp_now_init();
            delay(2000);
        }
    }

    Serial.println(F("ESP-Now Initialize [Success]"));

    esp_now_register_recv_cb(dataRecv);
}

uint32_t ESPNow_Lib::getTimes() {
    return times_espnow;
}