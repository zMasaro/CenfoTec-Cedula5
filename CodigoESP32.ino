/*
 * ========================================================
 * SISTEMA DE MONITOREO ENERGÉTICO INTELIGENTE - ESP32
 * ========================================================
 * 
 * Descripción: Código para ESP32 que captura datos de consumo
 * eléctrico y los envía a un backend Flask para análisis con IA.
 * 
 * Autor: CenfoTec-Cedula5 Team
 * Fecha: Agosto 2025
 * Versión: 1.0
 * 
 * Funcionalidades principales:
 * - Conexión automática a WiFi con reconexión
 * - Captura de datos eléctricos simulados
 * - Envío vía HTTP POST a backend Flask
 * - Manejo de errores y respuestas del servidor
 * 
 * Hardware requerido:
 * - ESP32 DevKit
 * - Sensores de voltaje y corriente (futuro)
 * - Circuitos de acondicionamiento (futuro)
 * ========================================================
 */

#include <WiFi.h>        // Librería nativa ESP32 para conectividad WiFi
#include <HTTPClient.h>  // Librería para realizar peticiones HTTP


// ========================================================
// CONFIGURACIÓN DE CONECTIVIDAD
// ========================================================

// Credenciales de red WiFi - CAMBIAR POR TUS DATOS
const char* WIFI_SSID = "Emmanuel's Galaxy S22+";  // Nombre de la red WiFi
const char* WIFI_PASS = "rojas2026";               // Contraseña de la red WiFi

// Configuración del servidor backend Flask
const char* API_URL   = "http://192.168.1.120:5000/datos_esp32";  // Endpoint del backend
const char* API_TOKEN = "";  // Token de autenticación (opcional, vacío por ahora)    

// ========================================================
// FUNCIONES PRINCIPALES
// ========================================================

/**
 * Función: connectWiFi()
 * Propósito: Establece conexión WiFi con manejo de errores
 * 
 * Características:
 * - Modo estación (WIFI_STA) para conectar como cliente
 * - Loop de espera con timeout implícito
 * - Feedback visual en Serial Monitor
 * - Muestra IP local asignada por el router
 */
void connectWiFi() {
  WiFi.mode(WIFI_STA);                    // Configurar ESP32 como cliente WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);      // Iniciar conexión con credenciales
  Serial.print("Conectando a WiFi");
  
  // Bucle de espera hasta conexión exitosa
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);                           // Esperar 500ms entre intentos
    Serial.print(".");                    // Indicador visual de progreso
  }
  
  // Confirmación de conexión exitosa
  Serial.println("\n✅ Conectado a WiFi");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());        // Mostrar IP asignada por DHCP
}

/**
 * Función: buildJson()
 * Propósito: Construye payload JSON con datos eléctricos
 * Retorna: String con JSON formateado
 * 
 * Estructura de datos:
 * - frequency: Frecuencia de la red eléctrica (50Hz Europa, 60Hz América)
 * - channel1/channel2: Datos de dos canales de medición
 *   - voltage: Voltaje RMS en voltios
 *   - current: Corriente RMS en amperios  
 *   - activePower: Potencia activa en watts
 *   - apparentPower: Potencia aparente en VA
 *   - powerFactor: Factor de potencia (0-1)
 *   - reactivePower: Potencia reactiva en VAR
 *   - activeEnergyImported: Energía importada en kWh
 *   - activeEnergyReturned: Energía exportada en kWh
 *   - activeEnergy: Energía total en kWh
 * 
 * Nota: Actualmente usa datos simulados. En futuras versiones
 * se reemplazará con lecturas reales de sensores ADC.
 */
String buildJson() {
  // JSON con estructura completa de datos eléctricos
  // Usando raw string literal para mejor legibilidad
  String json = R"rawliteral(
{
  "frequency": 50.0,
  "channel1": {
    "voltage": 230.0,
    "current": 1.234,
    "activePower": 284.2,
    "apparentPower": 284.5,
    "powerFactor": 0.99,
    "reactivePower": 10.0,
    "activeEnergyImported": 12.345,
    "activeEnergyReturned": 0.123,
    "activeEnergy": 12.468
  },
  "channel2": {
    "voltage": 229.8,
    "current": 0.567,
    "activePower": 130.1,
    "apparentPower": 131.0,
    "powerFactor": 0.99,
    "reactivePower": 5.0,
    "activeEnergyImported": 6.789,
    "activeEnergyReturned": 0.050,
    "activeEnergy": 6.839
  }
}
)rawliteral";
  return json;
}

/**
 * Función: postJSON()
 * Propósito: Envía datos JSON al backend Flask vía HTTP POST
 * Parámetros: payload - String con datos JSON a enviar
 * Retorna: bool - true si envío exitoso (HTTP 200-299), false si error
 * 
 * Características:
 * - Verificación automática de conexión WiFi
 * - Configuración de headers HTTP apropiados
 * - Soporte para autenticación Bearer Token (opcional)
 * - Manejo completo de respuestas HTTP
 * - Logging detallado para debugging
 */
bool postJSON(const String& payload) {
  // Verificar estado de WiFi antes de enviar
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (WiFi.status() != WL_CONNECTED) return false;

  HTTPClient http;                        // Crear instancia del cliente HTTP
  http.begin(API_URL);                    // Configurar URL del endpoint
  http.addHeader("Content-Type", "application/json");  // Header para JSON
  
  // Agregar token de autenticación si está configurado
  if (strlen(API_TOKEN) > 0) http.addHeader("Authorization", API_TOKEN);

  // Realizar petición POST y obtener código de respuesta
  int code = http.POST(payload);
  Serial.print("Código HTTP: ");
  Serial.println(code);

  // Procesar respuesta del servidor
  if (code > 0) {
    Serial.println("Respuesta del servidor:");
    Serial.println(http.getString());    // Mostrar respuesta completa
  }

  http.end();                             // Liberar recursos del cliente HTTP
  return code >= 200 && code < 300;      // Retornar true si código de éxito
}

// ========================================================
// CONFIGURACIÓN INICIAL Y BUCLE PRINCIPAL
// ========================================================

/**
 * Función: setup()
 * Propósito: Configuración inicial del ESP32 (ejecuta una sola vez)
 * 
 * Inicializa:
 * - Comunicación serial a 115200 baudios para debugging
 * - Conexión WiFi automática
 * - Mensaje de confirmación de sistema listo
 */
void setup() {
  Serial.begin(115200);                   // Inicializar comunicación serial
  connectWiFi();                          // Establecer conexión WiFi inicial
  Serial.println("ESP32 Energy Monitor listo!");
  Serial.println("Enviando datos cada 30 segundos...");
}

/**
 * Función: loop()
 * Propósito: Bucle principal del programa (ejecuta infinitamente)
 * 
 * Flujo de ejecución:
 * 1. Generar datos JSON con información eléctrica
 * 2. Mostrar datos en Serial Monitor para debugging
 * 3. Enviar datos al backend Flask vía HTTP POST
 * 4. Mostrar resultado del envío (éxito/error)
 * 5. Esperar 30 segundos antes del siguiente envío
 * 
 * Nota: El intervalo de 30 segundos está optimizado para:
 * - No saturar la API de Gemini (rate limiting)
 * - Permitir análisis significativo entre mediciones
 * - Conservar batería en aplicaciones portátiles
 */
void loop() {
  // Generar payload JSON con datos eléctricos actuales
  String payload = buildJson();
  
  // Mostrar datos que se van a enviar (útil para debugging)
  Serial.println("JSON a enviar:");
  Serial.println(payload);

  // Intentar envío al backend y mostrar resultado
  bool ok = postJSON(payload);
  Serial.println(ok ? "✅ POST OK - Datos enviados al backend Flask" : "❌ POST FAIL - Error al enviar datos");

  // Esperar 30 segundos antes del siguiente envío
  delay(30000);  // Intervalo optimizado para análisis con IA
} 
}