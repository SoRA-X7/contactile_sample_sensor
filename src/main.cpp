#include <Arduino.h>
#include <BLEDevice.h>
#include <M5Stack.h>

#include "BLEManager.h"

#define SENSOR_PIN 36

BLEManager *ble;

void setup() {
  M5.begin();
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  // ノイズ対策
  M5.Speaker.begin();
  M5.Speaker.mute();

  M5.Lcd.begin();
  M5.Lcd.setTextFont(4);
  M5.Lcd.println("M5 Initialized");

  M5.Lcd.print("Initializing Bluetooth...");
  ble = new BLEManager();
  M5.Lcd.println("OK");
}

void loop() {
  int32_t value = (int32_t)analogRead(SENSOR_PIN);
  //   Serial.println(value);
  ble->writeSensorValue(value);
  auto curY = M5.Lcd.getCursorY();
  M5.Lcd.setCursor(0, curY);
  M5.Lcd.printf("%05d", value);
  vTaskDelay(10);
}
