
#include "./config.h" // colocar la contraseña de tu WiFi en config.h

#include <WiFi.h>
#include "time.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -5 * 3600;  // (Lima, Perú) Ajusta según tu zona horaria en segundos
const int   daylightOffset_sec = 0;  // Ajusta si tienes horario de verano (no necesario para Lima)

// pin de salida para el motor
const int Abrir = 2;
const int Cerrar = 4;

void setup() {
    Serial.begin(115200);

    // Configurar pin de salida para el motor
    pinMode(Abrir, OUTPUT);
    pinMode(Cerrar, OUTPUT);

    digitalWrite(Abrir, LOW);
    digitalWrite(Cerrar, LOW);
    
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

void abrirPersiana() {
    digitalWrite(Cerrar, LOW);
    digitalWrite(Abrir, HIGH);
}

void detenerPersiana() {
    digitalWrite(Abrir, LOW);
    digitalWrite(Cerrar, LOW);
}

void cerrarPersiana() {
    digitalWrite(Abrir, LOW);
    digitalWrite(Cerrar, HIGH);
}

void loop() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    
    Serial.printf("\nHora: %02d:%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    
    static int segundosAcumulados = 6; // punto medio para que se abra o cierre la persiana
    static bool abriendo = false;
    static bool cerrando = false;

    // si la hora actual es mayor a las 6:00 am y menor a las 8:00 am, se abre la persiana
    if (timeinfo.tm_hour >= 6 && timeinfo.tm_hour < 8) {
        if (abriendo) {
            if (segundosAcumulados >= 12) {
                Serial.printf("Detenido desde abrir");
            } else {
                abrirPersiana();
                delay(2000);
                segundosAcumulados+=2;
                Serial.printf("Abriendo, segundos acumulados: %d\n", segundosAcumulados);
            }
        } else {
            abriendo = true;
            cerrando = false;
        }
    }

    // si la hora actual es mayor a las 7:00 pm y menor a las 11:00 pm, se cierra la persiana
    if (timeinfo.tm_hour >= 20 && timeinfo.tm_hour < 23) {
        if (cerrando) {
            if (segundosAcumulados <= 0) {
                Serial.printf("Detenido desde cerrar");
            } else {
                cerrarPersiana();
                delay(2000);              
                segundosAcumulados-=2;
                Serial.printf("Cerrando, segundos acumulados: %d\n", segundosAcumulados);
            }
        } else {
            cerrando = true;
            abriendo = false;
        }
    } 

    detenerPersiana(); // detener la persiana
    delay(3000); 
}
