void TaskSerial(void *pvParameters)
{
  (void) pvParameters;
  for (;;)
  {
    Serial.println("======== Tasks status ========");
    Serial.print("Tick count: ");
    Serial.print(xTaskGetTickCount());
    Serial.print(", Task count: ");
    Serial.print(uxTaskGetNumberOfTasks());

    Serial.println();
    Serial.println();

    // Serial task status
    Serial.print("- TASK ");
    Serial.print(pcTaskGetName(NULL)); // Get task name without handler https://www.freertos.org/a00021.html#pcTaskGetName
    Serial.print(", High Watermark: ");
    Serial.print(uxTaskGetStackHighWaterMark(NULL)); // https://www.freertos.org/uxTaskGetStackHighWaterMark.html


    TaskHandle_t taskSerialHandle = xTaskGetCurrentTaskHandle(); // Get current task handle. https://www.freertos.org/a00021.html#xTaskGetCurrentTaskHandle

    Serial.println();

    Serial.print("- TASK ");
    Serial.print(pcTaskGetName(TaskAtem_Handler)); // Get task name with handler
    Serial.print(", High Watermark: ");
    Serial.print(uxTaskGetStackHighWaterMark(TaskAtem_Handler));
    Serial.println();

    Serial.print("- TASK ");
    Serial.print(pcTaskGetName(TaskWebserver_Handler)); // Get task name with handler
    Serial.print(", High Watermark: ");
    Serial.print(uxTaskGetStackHighWaterMark(TaskWebserver_Handler));
    Serial.print(" Has client:");
    Serial.println(haveClient);
    Serial.println();

    vTaskDelay( 10000 / portTICK_PERIOD_MS );
  }
}
