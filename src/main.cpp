#include <Arduino.h>
#include <BLEDevice.h>
#include <M5Stack.h>

#include "BLEManager.h"

#define LCD_WIDTH 320
#define LCD_LINE_HEIGHT 20
#define SENSOR_PIN 36

BLEManager *ble;

void setup() {
  M5.begin();
  pinMode(SENSOR_PIN, INPUT_PULLDOWN);
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

  M5.Lcd.setCursor(0, 26 * 2);
  M5.Lcd.println(ble->deviceConnected ? "OK" : "NG");
  M5.Lcd.printf("%04d", value);

  auto data = (int32_t)((value / 4096.0) * LCD_WIDTH);
  M5.Lcd.fillRect(0, 26 * 4, data, LCD_LINE_HEIGHT, GREEN);
  M5.Lcd.fillRect(data, 26 * 4, LCD_WIDTH - data, LCD_LINE_HEIGHT, BLACK);
  vTaskDelay(10);
}
