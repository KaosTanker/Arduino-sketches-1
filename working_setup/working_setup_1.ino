#include <RTClib.h>
#include <Wire.h>
#include <dht.h>
#include <LiquidCrystal.h>
#include "RTClib.h"
#include <SPI.h>

#define REDLED_PIN 8 // sets trigger pin for red led
#define GREENLED_PIN 13 // sets trigger pin for green led
#define BLUELED_PIN 11 // sets triffer pin for blue led
#define DHT11_PIN 12 // sets input pin for temp humidity sensor
#define SOUNDSENSOR_PIN 0 // sets input for sound sensor

int val = 0;

LiquidCrystal LCD(10, 9, 5, 4, 3, 2); // sets input pins for LCD

RTC_DS3231 RTC; // sets name for temp humidity sensor

dht DHT; // renames dht

void setup() {
  // put your setup code here, to run once:

  
  LCD.begin(16, 2); // sets up LCD for use
  RTC.begin(); // starts real time clock
  Wire.begin(); 
  Serial.begin(9600);

  pinMode(DHT11_PIN, INPUT); // declares DHT11_PIN as input
  pinMode(SOUNDSENSOR_PIN, INPUT); // declares SOUNDSENSOR_PIN as input
  
  pinMode(GREENLED_PIN, OUTPUT); // sets GREENLED_PIN as output
  pinMode(REDLED_PIN, OUTPUT); // sets REDLED_PIN as output
  pinMode(BLUELED_PIN, OUTPUT); // sets BlueLED_PIN as output
  
  DateTime now = RTC.now();
  RTC.adjust(DateTime(2018, 02, 04, 15, 14, 0)); // sets date and time 
  RTC.setAlarm1Simple(19, 30); // sets alarm 
  RTC.turnOnAlarm(1); // turns on alarm
  if (RTC.checkAlarmEnabled(1)) {
    Serial.println("Alarm Enabled");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  int chk = DHT.read11(DHT11_PIN);

  DateTime now = RTC.now();

  val = digitalRead(SOUNDSENSOR_PIN);// digital interface will be assigned a value of pin 0 to read val
  if (val == HIGH) // When the sound detection module detects a signal, LED flashes
  
    digitalWrite (BLUELED_PIN, HIGH); // turns on blue led when it detects sound
  
  else
  
    digitalWrite (BLUELED_PIN, LOW); // turns off blue led when there is no sound


  LCD.setCursor(0, 0); // start postion of Humidity text on LCD
  LCD.print(DHT.humidity, 0); // 0 creates whole number, 1 two decimal
  LCD.print("% Humidity ");
  LCD.setCursor(0, 1); // start postion of temperature text on LCD
  LCD.print(DHT.temperature, 0);
  LCD.print(" C");
  LCD.setCursor(6, 1); // start postion of time text on LCD
  LCD.print(now.hour(), DEC); // shows the hour on LCD
  LCD.print(':');
  LCD.print(now.minute(), DEC); // shows the minute on LCD
  LCD.print('.');
  LCD.print(now.second(), DEC); // shows seconds on LCD
  
      
      if (DHT.temperature >= 20 )digitalWrite(GREENLED_PIN, (HIGH)); // turns on green led when temperature is above 20 C
      delay(1000); // wait one second
      digitalWrite(GREENLED_PIN, (LOW)); // turns green led off
      delay(1000); // wait one second

      if (DHT.humidity >= 30 )digitalWrite(REDLED_PIN, (HIGH)); // turns on red led when humidity is over 30 %
      delay(1000); // wait one second
      digitalWrite(REDLED_PIN, (LOW)); // turns red led off 
      delay(1000); // wait one second
  


  delay(250);

}
