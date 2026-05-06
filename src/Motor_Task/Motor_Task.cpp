#include "Motor_Task/Motor_Task.h"

limitSwitch ir;
MotorDriv mdriver;

TaskHandle_t motorDriver_Task_handle;

void handleMotor_Task(void *param);

Motor_Task::Motor_Task() {
    // No Once Func at Here
};

#define R1 32
#define R2 33

void Motor_Task::beginTask() {
    ir.begin();
    mdriver.begin();

    pinMode(R1, OUTPUT);
    pinMode(R2, OUTPUT);

    digitalWrite(R1, HIGH);
    digitalWrite(R2, HIGH);

    xTaskCreatePinnedToCore(
        handleMotor_Task,
        "MotorTask_handle",
        2048,
        this,
        1,
        &motorDriver_Task_handle,
        1
    );
}

void handleMotor_Task(void *param) {
    TickType_t saveTick = xTaskGetTickCount();

    TickType_t lastTick = 0;

    uint8_t MIN = 0;
    uint8_t MAX = 10;
    
    uint8_t condition = 0;

    enum COND {
        STOP,
        RUN,
        HOME
    };

    bool IR1;
    bool IR2;

    // Looping 
    while(1) {
        TickType_t nowTick = xTaskGetTickCount();
        
        uint16_t interval = 1000;
        
        static bool timeOut = false;
        uint16_t timeOut_espnow = 3000;

        xQueueReceive(DataQueue, &data_espnow, pdMS_TO_TICKS(50));

        ir.readBt(&IR1, &IR2);

        if(nowTick - lastTick >= pdMS_TO_TICKS(100)) {
            lastTick = nowTick;

            Serial.printf("B: %d, D: %d\n", IR2, IR1);

            if(data_espnow.vMoisAv <= MIN)
                condition = RUN;
            else if(data_espnow.vMoisAv >= MAX && !IR2)
                condition = HOME;

            /*if(millis() - espnow_lib.getTimes() >= timeOut_espnow)
                condition = HOME;
                */
        }

        switch(condition) {
            case STOP:
                mdriver.run(0b00000000, 0, 0);

            break;
                
            case RUN:
                static bool lastIR1 = false;
                static bool lastIR2 = false;

                static bool state = false;

                static bool stateRelay = false;

                {
                    uint32_t now = millis();
                    static uint32_t last = 0;

                    if(now - last >= 50) {
                        last = now;

                        stateRelay = !stateRelay;

                        digitalWrite(R1, stateRelay);
                        digitalWrite(R2, stateRelay);
                    }
                }

                if((!lastIR1 && IR1) || (!lastIR2 && IR2)) {
                    state = false;
                }

                lastIR1 = IR1;
                lastIR2 = IR2;

                if(state) {
                    if (IR1 == 1)
                        mdriver.run(0b01010000, 200, 200);
                    else if (IR2 == 1)
                        mdriver.run(0b10100000, 200, 200);
                } else {
                    mdriver.run(0b00000000, 0, 0);

                    static uint32_t last = 0;
                    uint32_t now = millis();

                    if(now - last >= 2000) {
                        last = now;

                        state = true;
                    }
                }
                break;

            case HOME:
                mdriver.run(0b10100000, 200, 200);
                if(IR2)
                    condition = STOP;

            break;
        }

        xTaskDelayUntil(&saveTick, pdMS_TO_TICKS(50));
    }
}