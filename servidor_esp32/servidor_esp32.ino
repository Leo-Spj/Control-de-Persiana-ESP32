#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Server"); // Nombre del dispositivo Bluetooth
  Serial.println("El dispositivo está esperando una conexión...");
}

void loop() {
  if (SerialBT.available()) {
    char received = SerialBT.read();
    Serial.println(received);
  }
}
