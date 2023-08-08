# Control de Persiana con ESP32

**Control de Persiana con ESP32**

Este proyecto automatiza y controla persianas de forma inteligente utilizando ESP32. Mediante WiFi y/o Bluetooth, el usuario puede manejar las persianas remotamente y ajustar su posición para optimizar la entrada de luz natural. 

**Características:**
- Control remoto inalámbrico de las persianas.
- Programación de horarios de apertura y cierre.
- Ajuste automático según la luminosidad externa.

**Aplicaciones:**

Ideal para hogares y oficinas que buscan mejorar la eficiencia energética y la comodidad. Maximiza el uso de luz natural reduciendo el consumo de energía.

## Configuración previa

**Conectividad Wi-Fi - Obtén la Hora en Tiempo Real :**

- Antes de compilar el código, asegúrate de configurar el archivo [`config.h`](https://github.com/Leo-Spj/Control-de-Persiana-ESP32/blob/main/config.h) con los datos de la red WiFi a la que deseas conectar. Luego, colócalo dentro de la carpeta `persiana`. 

## Materiales
| Material | Foto |
| --- | --- |
| ESP-32  | [![ESP-32](https://github.com/Leo-Spj/Domotica-Persiana-ESP32/blob/main/imagenes/esp32.png)](https://www.aliexpress.us/item/4000071762309.html?spm=a2g0o.order_list.order_list_main.20.4fce1802WRV2AW&gatewayAdapt=glo2usa) |
| Motor DC 30RPM 3V | [![Motor](https://github.com/Leo-Spj/Domotica-Persiana-ESP32/blob/main/imagenes/motorDC30rpm3v.png)](https://www.aliexpress.us/item/33022320164.html?spm=a2g0o.order_list.order_list_main.5.4fce1802WRV2AW&gatewayAdapt=glo2usa) |
| DRV8833 módulo controlador de motor DC de 2 canales | [![Controlador de motor](https://github.com/Leo-Spj/Domotica-Persiana-ESP32/blob/main/imagenes/controladorMotor.png)](https://www.aliexpress.us/item/4000083406292.html?spm=a2g0o.cart.0.0.582b7a9dyz7UiZ&mp=1&gatewayAdapt=glo2usa) |
| DS1307 Módulo de reloj | [![DS1307](https://github.com/Leo-Spj/Domotica-Persiana-ESP32/blob/main/imagenes/rtc.png)](https://www.aliexpress.us/item/1005003129119650.html?spm=a2g0o.order_list.order_list_main.4.46921802fprNHj&gatewayAdapt=glo2usa) |





