#pragma once

#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>

#define SERVICE_UUID "4b958953-4ff5-45e6-97f2-629170aec1f3"
#define CH_UUID_SENSOR_VALUE "adad0876-f4d1-4189-8604-53ed049f386c"

class MyServerCallbacks;

class BLEManager {
  friend MyServerCallbacks;

 public:
  BLEManager();
  void writeSensorValue(int32_t val);

 private:
  BLEServer *pServer;
  BLECharacteristic *chSensorValue;
  bool deviceConnected;
};

class MyServerCallbacks : public BLEServerCallbacks {
 public:
  MyServerCallbacks(BLEManager *manager);
  void onConnect(BLEServer *pServer);
  void onDisconnect(BLEServer *pServer);

 private:
  BLEManager *manager;
};

class MyCallbacks : public BLECharacteristicCallbacks {
 public:
  void onWrite(BLECharacteristic *pCharacteristic);
};
