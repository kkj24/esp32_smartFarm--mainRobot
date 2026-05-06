#ifndef ESPNOW_TASK_FREE_RTOS_H
#define ESPNOW_TASK_FREE_RTOS_H

#include "ESPNow_Lib.h"

extern ESPNow_Lib espnow_lib;

extern QueueHandle_t DataQueue;

class ESPNow_Task {
    public:
        ESPNow_Task();

        void beginTask();

    private:

};

#endif 