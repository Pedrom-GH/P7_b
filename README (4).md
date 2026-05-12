# Lectura de Micrófono INMP441 con ESP32 via I2S

Práctica de adquisición de audio digital usando el micrófono MEMS **INMP441** conectado a un **ESP32** mediante el protocolo **I2S**. Los datos de audio se leen en tiempo real y se envían por puerto serie para su visualización en el Serial Plotter de Arduino IDE.

## 🔧 Hardware necesario

- ESP32 (cualquier variante con soporte I2S)
- Micrófono MEMS INMP441
- Cables de conexión

## 🔌 Conexiones

| INMP441 | ESP32 |
|---------|-------|
| WS (L/R) | GPIO 15 |
| SD (Data) | GPIO 32 |
| SCK (Clock) | GPIO 14 |
| VDD | 3.3V |
| GND | GND |
| L/R | GND (canal izquierdo) |

## ⚙️ Configuración I2S

| Parámetro | Valor |
|-----------|-------|
| Sample Rate | 44100 Hz |
| Bits por muestra | 32 bits (datos a 24 bits) |
| Canal | Solo izquierdo |
| Puerto I2S | I2S_NUM_0 |
| Buffers DMA | 8 × 64 muestras |

## 📁 Estructura del proyecto

```
.
└── main.cpp   # Código principal (setup + loop de lectura I2S)
```

## 🚀 Cómo usarlo

1. Conecta el INMP441 al ESP32 según la tabla de conexiones.
2. Abre el proyecto en **PlatformIO** o **Arduino IDE** con soporte para ESP32.
3. Compila y sube el código al ESP32.
4. Abre **Herramientas > Plotter de Serie** a **115200 baudios**.
5. Observa la forma de onda del audio en tiempo real.

## 🧠 Funcionamiento

El ESP32 actúa como **maestro I2S** en modo recepción (`RX`). En cada iteración del loop principal:

1. Se lee una muestra de 32 bits del micrófono con `i2s_read()`.
2. Se desplaza el valor 14 bits a la derecha (`>> 14`) para adaptarlo a un rango visualizable de 16 bits.
3. Se imprime por `Serial` para mostrarse en el Plotter.

> El INMP441 usa tramas de 32 bits pero los datos son de 24 bits con justificación izquierda, de ahí el desplazamiento necesario para normalizar la señal.

## 🛠️ Dependencias

- [Arduino ESP32 Core](https://github.com/espressif/arduino-esp32)
- Librería `driver/i2s.h` (incluida en el core de ESP32, no requiere instalación adicional)

## 📋 Requisitos

- **Framework:** Arduino (PlatformIO o Arduino IDE)
- **Placa:** ESP32
- **Baudios monitor serie:** 115200
