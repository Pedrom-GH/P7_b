#include <Arduino.h>
#include <driver/i2s.h>

// Definición de pines según el esquema anterior
#define I2S_WS 15
#define I2S_SD 32
#define I2S_SCK 14
#define I2S_PORT I2S_NUM_0

void setup() {
  Serial.begin(115200);
  
  // Configuración del driver I2S para entrada (Micrófono)
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), // RX para recibir
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // El INMP441 usa 24 bits en tramas de 32
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1, // No se usa salida
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_start(I2S_PORT);
}

void loop() {
  int32_t sample = 0;
  size_t bytes_read;
  
  // Leer un dato del micrófono
  esp_err_t result = i2s_read(I2S_PORT, &sample, sizeof(sample), &bytes_read, portMAX_DELAY);
  
  if (result == ESP_OK && bytes_read > 0) {
    // El INMP441 devuelve valores muy altos, los desplazamos para visualizar mejor
    int16_t sample16 = sample >> 14; 
    Serial.println(sample16); // Ver en el Serial Plotter (Herramientas > Plotter de serie)
  }
}