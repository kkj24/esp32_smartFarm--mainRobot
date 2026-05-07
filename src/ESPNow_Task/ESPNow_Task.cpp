#include "ESPNow_Task/ESPNow_Task.h"

QueueHandle_t DataQueue;
ESPNow_Lib espnow_lib;

void ESPNow_Task_handle(void *param);

ESPNow_Task::ESPNow_Task() {
    // No Func at Here
};


void ESPNow_Task::beginTask() {
    espnow_lib.begin();

    DataQueue = xQueueCreate(7, sizeof(data_espnow));
    xTaskCreatePinnedToCore(
        ESPNow_Task_handle,
        "ESPNOW_task",
        4096,
        this,
        1,
        NULL,
        1
    );
}

void ESPNow_Task_handle(void *param) {
    TickType_t saveTick = xTaskGetTickCount();

    TickType_t lastTick = 0;

    while(1) {
        TickType_t nowTick = xTaskGetTickCount();

        xQueueSend(DataQueue, &data_espnow, pdMS_TO_TICKS(50));

        uint16_t timeOut_espnow = 3000; // 3000ms

        if(nowTick - lastTick >= pdMS_TO_TICKS(100)) {
            lastTick = nowTick;

            if(millis() - espnow_lib.getTimes() >= timeOut_espnow) {
                Serial.println(F("[ESP-NOW] TimeOut!..."));
            }

            #if 1

            Serial.println(F("================"));

            Serial.printf(
                "Mois1: %d\n"
                "Mois2: %d\n"
                "Mois3: %d\n"
                "Mois4: %d\n"
                "MoisAv: %d\n"
                "Hum: %d\n"
                "Temp: %d\n",
                data_espnow.vMois1,
                data_espnow.vMois2,
                data_espnow.vMois3,
                data_espnow.vMois4,
                data_espnow.vMoisAv,
                data_espnow.vHum,
                data_espnow.vTemp
            );

            Serial.println("Mac Address: " + String(WiFi.macAddress()));
            
            Serial.println(F("================"));

            #endif
        }
        

        xTaskDelayUntil(&saveTick, pdMS_TO_TICKS(500));
    }
}
