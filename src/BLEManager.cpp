#include "BLEManager.h"

MyServerCallbacks::MyServerCallbacks(BLEManager *manager) {
  this->manager = manager;
}

void MyServerCallbacks::onConnect(BLEServer *pServer) {
  manager->deviceConnected = true;
}

void MyServerCallbacks::onDisconnect(BLEServer *pServer) {
  manager->deviceConnected = false;
}

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
  std::string rxValue = pCharacteristic->getValue();
  if (rxValue.length() > 0) {
    auto cmd = rxValue.c_str();
    Serial.print("Received Value: ");
    Serial.println(cmd);
  }
}

BLEManager::BLEManager() {
  // Create the BLE Device
  BLEDevice::init("Contactile Sensor M5");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks(this));

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  chSensorValue = pService->createCharacteristic(
      CH_UUID_SENSOR_VALUE, BLECharacteristic::PROPERTY_READ);
  double val = 0;
  chSensorValue->setValue(val);

  // Start the service
  pService->start();

  // Start advertising
  auto adv = pServer->getAdvertising();
  adv->start();
}

void BLEManager::writeSensorValue(int32_t value) {
  if (chSensorValue != NULL) {
    chSensorValue->setValue(value);
  }
}
