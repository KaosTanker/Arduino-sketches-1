#include <RTClib.h>
#include <Wire.h>
#include <dht.h>
#include <LiquidCrystal.h>
#include "RTClib.h"
#include <SPI.h>

LiquidCrystal LCD(10, 9, 5, 4, 3, 2);

RTC_DS3231 RTC;

#define REDLED_PIN 8
#define GREENLED_PIN 13






dht DHT;

#define DHT11_PIN 12

void setup() {
  // put your setup code here, to run once:

  pinMode(DHT11_PIN, INPUT);


  LCD.begin(16, 2);
  RTC.begin();
  Wire.begin();
  DateTime now = RTC.now();
  pinMode(GREENLED_PIN, OUTPUT);
  pinMode(REDLED_PIN,OUTPUT);

  RTC.setAlarm1Simple(21, 58);
  RTC.turnOnAlarm(1);
  if (RTC.checkAlarmEnabled(1)) {
    Serial.println("Alarm Enabled");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  int chk = DHT.read11(DHT11_PIN);

  DateTime now = RTC.now();


  LCD.setCursor(0, 0); // start postion of Humidity text on LCD
  LCD.print(DHT.humidity, 0); // 0 creates whole number, 1 two decimal
  LCD.print("% Humidity ");
  LCD.setCursor(0, 1); // start postion of temperature text on LCD
  LCD.print(DHT.temperature, 0);
  LCD.print(" C");
  LCD.setCursor(6, 1); // start postion of time text on LCD
  LCD.print(now.hour(), DEC);
  LCD.print(':');
  LCD.print(now.minute(), DEC);
  LCD.print('.');
  LCD.print(now.second(), DEC);
      
      if (DHT.temperature >= 20 )digitalWrite(GREENLED_PIN, (HIGH));
      delay(1000);
      digitalWrite(GREENLED_PIN, (LOW));
      delay(1000);

      if (DHT.humidity >= 30 )digitalWrite(REDLED_PIN, (HIGH));
      delay(1000);
      digitalWrite(REDLED_PIN, (LOW));
      delay(1000);
  


  delay(600);

}
