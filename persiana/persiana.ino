
#include "./config.h" // colocar la contraseña de tu WiFi en config.h

#include <WiFi.h>
#include "time.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -5 * 3600;  // (Lima, Perú) Ajusta según tu zona horaria en segundos
const int   daylightOffset_sec = 0;  // Ajusta si tienes horario de verano (no necesario para Lima)


void setup() {
    Serial.begin(115200);
    
    // Conectarse a WiFi
    Serial.println("Conectando WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado ! ");

    // Configurar hora
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Esperar hasta que la hora esté configurada
    while (!time(nullptr)) {
        Serial.println("Esperando...");
        delay(1000);
    }
}

void loop() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    
    Serial.printf("Fecha y Hora: %02d/%02d/%04d %02d:%02d:%02d\n", 
                  timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900, 
                  timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    
    delay(10000);  // Imprimir cada 10 segundos
}
