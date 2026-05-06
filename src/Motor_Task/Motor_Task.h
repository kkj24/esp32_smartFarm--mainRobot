#ifndef MOTOR_TASK_FILE_H
#define MOTOR_TASK_FILE_H

#include "MD_lib.h"
#include "ESPNow_Task/ESPNow_Task.h"

#include "LimitSwitch_Lib.h"

extern limitSwitch ir;

extern MotorDriv mdiver;

extern TaskHandle_t motorDriver_Task_handle;

class Motor_Task {
    public:
        Motor_Task();

        void beginTask();

    private:

};

#endif