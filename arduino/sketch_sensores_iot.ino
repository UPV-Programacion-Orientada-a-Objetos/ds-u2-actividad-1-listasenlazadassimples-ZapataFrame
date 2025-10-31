/**
 * @file sketch_sensores_iot.ino
 * @brief Sketch de Arduino para simulación de sensores IoT.
 *
 * Este programa simula dos tipos de sensores que envían datos vía Serial:
 * - Sensor de Temperatura (ID: T-001): Valores float entre 20.0°C y 30.0°C
 * - Sensor de Presión (ID: P-105): Valores int entre 1000 y 1020 hPa
 *
 * Protocolo de comunicación:
 * - Baudrate: 9600
 * - Formato: "ID,VALOR\n" (ejemplo: "T-001,25.3")
 * - Mensaje inicial: "ARDUINO_READY" tras 2 segundos de setup
 *
 * @note Este archivo debe renombrarse a "sketch_sensores_iot.ino" para
 *       ser reconocido correctamente por el Arduino IDE.
 *
 * @author ZapataFrame
 * @date 2025-10-30
 * @version 1.0
 */

/**
 * @brief Configuración inicial del Arduino.
 *
 * Inicializa la comunicación serial a 9600 baudios, configura la semilla
 * de números aleatorios usando ruido del pin analógico 0, y envía señal
 * de ready tras 2 segundos para sincronización con el host.
 */
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));  // Semilla basada en ruido analógico
  
  // Esperar a que se establezca la conexión serial
  delay(2000);
  
  // Señal de sincronización para el programa C++
  Serial.println("ARDUINO_READY");
}

/**
 * @brief Bucle principal - Genera y envía lecturas simuladas.
 *
 * Ciclo continuo que:
 * 1. Genera temperatura aleatoria (20.0 - 29.9°C) y la envía como "T-001,XX.X"
 * 2. Espera 1 segundo
 * 3. Genera presión aleatoria (1000 - 1020 hPa) y la envía como "P-105,XXXX"
 * 4. Espera 1 segundo y repite
 *
 * Formato de salida: "SENSOR_ID,VALOR\n"
 */
void loop() {
  // ===== SENSOR DE TEMPERATURA =====
  // Rango: 20.0°C a 29.9°C con un decimal de precisión
  float temp = 20.0 + (random(0, 100) / 10.0);
  Serial.print("T-001,");           // ID del sensor de temperatura
  Serial.println(temp, 1);          // Valor con 1 decimal
  
  delay(1000);  // Pausa de 1 segundo
  
  // ===== SENSOR DE PRESIÓN =====
  // Rango: 1000 a 1020 hPa (hectopascales)
  int presion = 1000 + random(0, 21);
  Serial.print("P-105,");           // ID del sensor de presión
  Serial.println(presion);          // Valor entero
  
  delay(1000);  // Pausa de 1 segundo antes del siguiente ciclo
}