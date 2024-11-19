#include <Arduino.h>
#if CONFIG_FREERTOS_UNICORE
#define TASK_RUNNING_CORE 0
#else
#define TASK_RUNNING_CORE 1
#endif

#define ANALOG_INPUT_PIN A0

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

void TaskBlink(void *pvParameters);
void TaskAnalogRead(void *pvParameters);
TaskHandle_t analog_read_task_handle;

void setup() {
    Serial.begin(115200);

    uint32_t blink_delay = 1000;
    xTaskCreate(TaskBlink, "Task Blink", 2048, (void *)&blink_delay, 1, NULL);
    xTaskCreatePinnedToCore(TaskAnalogRead, "Analog Read", 2048, NULL, 5, &analog_read_task_handle, 0);

    Serial.println("Basic Multi Threading Arduino Example");
    Serial.print("Loop Core ID: ");
    Serial.println(xPortGetCoreID());
}

void loop() {
    if (analog_read_task_handle != NULL) {
        delay(1000);
        vTaskDelete(analog_read_task_handle);
        Serial.println("TaskAnalogRead Deleted");
        analog_read_task_handle = NULL;
    }
}

void TaskBlink(void *pvParameters) {
    uint32_t blink_delay = *((uint32_t *)pvParameters);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("TaskBlink created");
    Serial.print("TaskBlink Core ID: ");
    Serial.println(xPortGetCoreID());

    for (;;) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(blink_delay);
        digitalWrite(LED_BUILTIN, LOW);
        delay(blink_delay);
    }
}

void TaskAnalogRead(void *pvParameters) {
    (void)pvParameters;
    Serial.println("TaskAnalogRead created");

    if (digitalPinToAnalogChannel(ANALOG_INPUT_PIN) == -1) {
        Serial.printf("TaskAnalogRead cannot work because pin %d is not usable for ADC.\n", ANALOG_INPUT_PIN);
        analog_read_task_handle = NULL;
        vTaskDelete(NULL);
    }

    Serial.print("TaskAnalogRead Core ID: ");
    Serial.println(xPortGetCoreID());

    for (;;) {
        int sensorValue = analogRead(ANALOG_INPUT_PIN);
        Serial.println(sensorValue);
        delay(100);
    }
}
