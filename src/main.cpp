#include <Arduino.h>

const uint8_t ST_CENTER = 140;
const uint8_t ST_MAX = 255;
const uint8_t ST_MIN = 0;
const uint8_t TH_CENTER = 140;
const uint8_t TH_MAX = 255;
const uint8_t TH_MIN = 0;

uint16_t st = ST_CENTER;
uint16_t th = TH_CENTER;

void setup()
{
  Serial.begin(922190);
  dacWrite(DAC2, ST_CENTER);
  dacWrite(DAC1, TH_CENTER);

  delay(2000);

  xTaskCreatePinnedToCore(
      [](void *pvParameters)
      {
        while (true)
        {
          String data = Serial.readStringUntil('\n');
          if (data.length() > 0)
          {
            String stStr = data.substring(0, 3);
            String thStr = data.substring(3, 6);
            st = stStr.toInt();
            th = thStr.toInt();
          }
          // Serial.printf("Steering: %d, Throttle: %d\n", st, th);
        }
      },
      "readData", 10000, NULL, 1, NULL, 0);

  xTaskCreatePinnedToCore(
      [](void *pvParameters)
      {
        while (true)
        {
          dacWrite(DAC2, st);
          dacWrite(DAC1, th);
          // Serial.printf("Steering: %d, Throttle: %d\n", st, th);
        }
      },
      "writeData", 10000, NULL, 1, NULL, 1);
}

void loop()
{
}
