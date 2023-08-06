#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Client"); 
  Serial.println("Intentando conectar al servidor...");

  // Espera hasta que se conecte al servidor
  while(!SerialBT.connect("ESP32_Server")) {
    delay(1000);
    Serial.println("Reintentando conexión...");
  }
  Serial.println("Conectado!");
}

void loop() {
  // Envía la palabra al servidor
  SerialBT.println("HolaServidor");
  delay(1000); // Espera un segundo
}
