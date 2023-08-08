
#include "./config.h" // colocar la contraseña de tu WiFi en config.h

#include <WiFi.h>
#include "time.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -5 * 3600;  // (Lima, Perú) Ajusta según tu zona horaria en segundos
const int   daylightOffset_sec = 0;  // Ajusta si tienes horario de verano (no necesario para Lima)

// pin de salida para el motor
const int Abrir = 11;
const int Cerrar = 10;

// botones para abrir y cerrar la persiana
const int BotonAbrir = 48;
const int BotonCerrar = 45;

void setup() {
    Serial.begin(115200);

    // Configurar pin de salida para el motor
    pinMode(Abrir, OUTPUT);
    pinMode(Cerrar, OUTPUT);
        digitalWrite(Abrir, LOW);
        digitalWrite(Cerrar, LOW);

    // Configurar botones
    pinMode(BotonAbrir, INPUT);
    pinMode(BotonCerrar, INPUT);
    
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

    // Imprimir solo la hora
    struct tm timeinfo = getLocalTime();
    Serial.println(&timeinfo, "%H:%M:%S");
}

struct tm getLocalTime() {
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    return timeinfo;
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

void procesoAbrirPersiana(struct tm timeinfo, int &segundosAcumulados) {
    if (timeinfo.tm_hour >= 6 && timeinfo.tm_hour < 8) {
        if (segundosAcumulados >= 12) {
            //Serial.println("Detenido desde abrir");
        } else {
            abrirPersiana();
            delay(2000);
            segundosAcumulados += 2;
            Serial.printf("Abriendo, segundos acumulados: %d\n", segundosAcumulados);
        }
    }
}

void procesoCerrarPersiana(struct tm timeinfo, int &segundosAcumulados) {
    if (timeinfo.tm_hour >= 20 && timeinfo.tm_hour < 23) {
        if (segundosAcumulados <= 0) {
            //Serial.println("Detenido desde cerrar");
        } else {
            cerrarPersiana();
            delay(2000);
            segundosAcumulados -= 2;
            Serial.printf("Cerrando, segundos acumulados: %d\n", segundosAcumulados);
        }
    }
}

void accionBotonAbrir() {
    while (digitalRead(BotonAbrir) == HIGH) {
        abrirPersiana();
        Serial.println("Boton abrir");
    }
}

void accionBotonCerrar() {
    while (digitalRead(BotonCerrar) == HIGH) {
        cerrarPersiana();
        Serial.println("Boton cerrar");
    }
}

void loop() {
    
    struct tm timeinfo = getLocalTime();  
    
    // Serial.printf("\nHora: %02d:%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    
    static int segundosAcumulados = 6; // punto medio para que se abra o cierre la persiana
    procesoAbrirPersiana(timeinfo, segundosAcumulados);
    procesoCerrarPersiana(timeinfo, segundosAcumulados);
  
    // si no se presiona ningún botón, se detiene la persiana
    digitalWrite(BotonAbrir, LOW);
    digitalWrite(BotonCerrar, LOW);

    accionBotonAbrir();
    accionBotonCerrar();

    detenerPersiana(); // detener la persiana
    delay(200);
}
