#include <WiFi.h>
#include <HTTPClient.h>


const char* WIFI_SSID = "Emmanuel's Galaxy S22+";
const char* WIFI_PASS = "rojas2026";


const char* API_URL   = "http://192.168.1.120:5000/datos_esp32";   
const char* API_TOKEN = "";  // Sin token por ahora    

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Conectado a WiFi");
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());
}

String buildJson() {
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

bool postJSON(const String& payload) {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (WiFi.status() != WL_CONNECTED) return false;

  HTTPClient http;
  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");
  if (strlen(API_TOKEN) > 0) http.addHeader("Authorization", API_TOKEN);

  int code = http.POST(payload);
  Serial.print("Código HTTP: ");
  Serial.println(code);

  if (code > 0) {
    Serial.println("Respuesta del servidor:");
    Serial.println(http.getString());
  }

  http.end();
  return code >= 200 && code < 300;
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
  String payload = buildJson();
  Serial.println("JSON a enviar:");
  Serial.println(payload);

  bool ok = postJSON(payload);
  Serial.println(ok ? "✅ POST OK - Datos enviados al backend Flask" : "❌ POST FAIL - Error al enviar datos");

  delay(30000);  // Enviar cada 30 segundos (optimizado para Gemini) 
}