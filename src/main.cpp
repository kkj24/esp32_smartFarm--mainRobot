#include "WiFi_Task/WiFi_Task.h"
#include "ESPNow_Task/ESPNow_Task.h"
#include "Motor_Task/Motor_Task.h"

WiFi_Task wifiTask;
ESPNow_Task espnow_task;
Motor_Task mtask;

void setup() {
  Serial.begin(115200);

  wifiTask.beginTask();
  espnow_task.beginTask();
  mtask.beginTask();
}

void loop() {

}