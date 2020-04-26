#include <Arduino.h>
#include <time.h>

#include "ntp.h"

void NTPConnect(int utc_offset, bool use_daylight_savings)
{
  time_t now;
  time_t nowish = 1510592825;
  struct tm timeinfo;

  uint8_t DST = int(use_daylight_savings);

  Serial.print("Setting time using SNTP");
  configTime(utc_offset * 3600, DST * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);

  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }

  Serial.println("done!");

  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}