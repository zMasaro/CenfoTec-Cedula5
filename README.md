# Guía de Integración ESP32 → Flask Backend → Gemini → Frontend

## Resumen del Flujo
```
ESP32 (sensores) → WiFi → Flask Backend → Gemini API → Frontend Web
```

## Pasos para la Integración Completa

### 1. Preparar el Backend Flask
- ✅ Ya tienes `app.py` funcionando
- ✅ Ruta `/datos_esp32` recibe datos del ESP32
- ✅ Ruta `/get_analisis` sirve análisis a la web
- ✅ Ruta `/` sirve `index.html`

### 2. Configurar el ESP32

#### Actualizar la IP del servidor:
En `esp32_energy_monitor.ino`, cambia:
```cpp
const char* API_URL = "http://192.168.1.120:5000/datos_esp32";
```
**Por la IP real de tu PC donde corre Flask.**

#### Para encontrar tu IP:
```powershell
ipconfig
```
Busca "Adaptador de LAN inalámbrica Wi-Fi" → "Dirección IPv4"

### 3. Cargar el código al ESP32
1. Abrir Arduino IDE
2. Seleccionar placa ESP32
3. Cargar `esp32_energy_monitor.ino`
4. Abrir Monitor Serie (115200 baud)

### 4. Iniciar el sistema completo

#### Terminal 1 - Backend Flask:
```powershell
cd "C:\Users\carlo\OneDrive\Escritorio\ESP32"
.\.venv\Scripts\Activate
python app.py
```

#### Terminal 2 - Verificar funcionamiento:
```powershell
# Opcional: simular datos del ESP32
Invoke-RestMethod -Uri http://localhost:5000/datos_esp32 -Method Post -ContentType 'application/json' -Body '{"frequency":50.0,"channel1":{"voltage":230.0,"current":1.234,"activePower":284.2,"apparentPower":284.5,"powerFactor":0.99,"reactivePower":10.0,"activeEnergyImported":12.345,"activeEnergyReturned":0.123,"activeEnergy":12.468},"channel2":{"voltage":229.8,"current":0.567,"activePower":130.1,"apparentPower":131.0,"powerFactor":0.99,"reactivePower":5.0,"activeEnergyImported":6.789,"activeEnergyReturned":0.050,"activeEnergy":6.839}}'
```

### 5. Verificar el flujo completo

1. **ESP32**: Monitor Serie debe mostrar "✅ POST OK"
2. **Backend**: Consola debe mostrar "Datos recibidos del ESP32" y "Análisis de Gemini"
3. **Frontend**: Ir a `http://localhost:5000/` y presionar "Actualizar Análisis"

### 6. Monitoreo y Debugging

#### Logs del ESP32:
```
Conectando a WiFi...
✅ Conectado a WiFi
IP local: 192.168.1.XXX
JSON a enviar:
{...datos...}
Código HTTP: 200
✅ POST OK - Datos enviados correctamente
```

#### Logs del Backend:
```
Datos recibidos del ESP32: {'frequency': 50.0, ...}
Análisis de Gemini: [texto del análisis]
```

### 7. Troubleshooting Común

| Problema | Solución |
|----------|----------|
| ESP32 no conecta WiFi | Verificar SSID/password |
| HTTP 404/500 | Verificar IP del servidor |
| Sin análisis de Gemini | Verificar archivo .env con API_KEY |
| Frontend no actualiza | Verificar que Flask sirva en 0.0.0.0:5000 |

### 8. Próximos pasos (opcional)
- Agregar sensores reales al ESP32
- Implementar calibración de medidas
- Añadir logging a archivos
- Crear dashboard con gráficos históricos
- Implementar alertas por consumo alto

## Archivos del Proyecto
```
ESP32/
├── app.py                     # Backend Flask
├── index.html                 # Frontend web
├── esp32_energy_monitor.ino   # Código ESP32
├── requirements.txt           # Dependencias Python
├── .env                       # API Key de Gemini
└── README.md                  # Esta guía
```
