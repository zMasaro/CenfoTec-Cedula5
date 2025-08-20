# 🔌 Sistema de Monitoreo Energético Inteligente con ESP32

## 📋 Introducción al Proyecto

Este proyecto implementa un **sistema completo de monitoreo energético** que combina hardware (ESP32), inteligencia artificial (Google Gemini) y una interfaz web moderna. El sistema captura datos de consumo eléctrico en tiempo real, los analiza usando IA y presenta recomendaciones inteligentes a través de una interfaz web intuitiva.

### 🎯 Objetivo Principal
Crear una solución IoT que permita a los usuarios monitorear su consumo eléctrico en tiempo real y recibir análisis inteligentes para optimizar el uso de energía en sus hogares o negocios.

## 👥 Participantes del Proyecto

| Nombre | Rol | Responsabilidades |
|--------|-----|------------------|
| **Carlo Gonzalez Obando** | Desarrollador Backend | Backend Flask, Integración Gemini AI|
| **Emmanuel Sanchez Rojas** | Desarrollador IoT | Hardware ESP32, Conectividad WiFi |
| **Joel Mejias** | Desarrollador Full-Stack | Backend Flask, Integración Gemini AI |
| **Ibisay Gutiérrez** | Desarrolladora Front, Desarrolladora Backend |  


## 🏗️ Arquitectura del Sistema

```mermaid
graph TD
    A[ESP32 + Sensores] -->|WiFi| B[Backend Flask]
    B -->|API REST| C[Google Gemini AI]
    C -->|Análisis| B
    B -->|WebServer| D[Frontend Web]
    D -->|Tiempo Real| E[Usuario Final]
```

### 🔄 Flujo de Datos
1. **ESP32** captura mediciones eléctricas (voltaje, corriente, potencia)
2. **Backend Flask** recibe los datos vía HTTP POST
3. **Gemini AI** analiza los datos y genera recomendaciones
4. **Frontend Web** muestra el análisis en tiempo real
5. **Usuario** puede monitorear y tomar decisiones informadas

## 🛠️ Tecnologías Utilizadas

### Hardware
- **ESP32** - Microcontrolador con WiFi integrado
- **JSYMK194G** - Medidor de energia de potencia bidireccional, monofasico
- **PCB male and female jumper 2.54 mm connectors** 
- **Heat shrink tubes**
- **Power cable with plug**   
- **Sensores de corriente y voltaje** - Para medición eléctrica
- **Circuitos de acondicionamiento** - Para protección y precisión

### Software Backend
- **Python 3.13** - Lenguaje principal
- **Flask 3.0** - Framework web ligero
- **Google Generative AI** - Análisis inteligente con Gemini
- **python-dotenv** - Gestión de variables de entorno

### Frontend
- **HTML5/CSS3** - Interfaz responsive
- **JavaScript** - Interactividad y comunicación con API
- **Fetch API** - Comunicación asíncrona

### DevOps & Herramientas
- **Git/GitHub** - Control de versiones
- **Arduino IDE** - Desarrollo ESP32
- **VS Code** - Editor de código

## 📁 Estructura del Proyecto

```
CenfoTec-Cedula5/
├── 📱 CodigoESP32.ino          # Código del microcontrolador ESP32
├── 🔧 app.py                   # Backend Flask con integración Gemini
├── 🌐 index.html               # Frontend web responsivo
├── 📦 requirements.txt         # Dependencias Python
├── 🔐 .env.example            # Plantilla de variables de entorno
├── 📖 README.md               # Documentación del proyecto
├── 🚫 .gitignore              # Archivos excluidos del control de versiones
└── 📄 LICENSE                 # Licencia del proyecto
```

## 🚀 Guía de Instalación y Configuración

### 📋 Prerequisitos
- Python 3.8 o superior
- Arduino IDE
- ESP32 DevKit
- Cuenta de Google Cloud (para Gemini AI)

### 🔧 Configuración del Backend

1. **Clonar el repositorio:**
```bash
git clone https://github.com/zMasaro/CenfoTec-Cedula5.git
cd CenfoTec-Cedula5
```

2. **Crear entorno virtual (Windows):**
```powershell
# ⚠️ IMPORTANTE: En Windows usar 'py' en lugar de 'python'
py -m venv .venv

# Si tienes problemas con PowerShell, habilitar ejecución de scripts:
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

3. **Activar entorno virtual:**
```powershell
# Windows PowerShell
.\.venv\Scripts\Activate

# Windows CMD
.\.venv\Scripts\activate.bat

# Linux/Mac
source .venv/bin/activate
```

4. **Verificar activación del entorno:**
```powershell
# Deberías ver (.venv) al inicio de la línea de comandos:
# (.venv) PS C:\...\CenfoTec-Cedula5>
```

5. **Actualizar pip y instalar dependencias:**
```powershell
# Actualizar pip a la última versión
python -m pip install --upgrade pip

# Opción 1: Instalar desde requirements.txt (RECOMENDADO)
pip install -r requirements.txt

# Opción 2: Instalar manualmente las dependencias principales
pip install Flask google-generativeai python-dotenv
```

6. **Verificar instalación de dependencias:**
```powershell
# Listar paquetes instalados
pip list

# Deberías ver estas dependencias principales:
# Flask (framework web)
# google-generativeai (SDK de Gemini)
# python-dotenv (gestión de variables .env)
```

7. **Configurar variables de entorno:**
```powershell
# Copiar plantilla de variables de entorno
cp .env.example .env

# Editar .env con tu editor favorito y agregar:
# GOOGLE_API_KEY=tu_api_key_real_de_google_gemini
```

8. **Ejecutar el servidor:**
```powershell
# Opción 1: Ejecutar directamente
python app.py

# Opción 2: Usar comando flask
flask run --host=0.0.0.0

# El servidor iniciará en:
# http://127.0.0.1:5000/ (acceso local)
# http://tu-ip:5000/ (acceso desde red)
```

### 🛠️ Solución de Problemas Comunes

#### ❌ "Python was not found"
```powershell
# Solución: Usar 'py' en lugar de 'python'
py -m venv .venv
```

#### ❌ "cannot be loaded because running scripts is disabled"
```powershell
# Solución: Habilitar ejecución de scripts
Set-ExecutionPolicy -Scope CurrentUser RemoteSigned
```

#### ❌ "No module named 'flask'"
```powershell
# Solución: Verificar que el entorno esté activo y reinstalar
.\.venv\Scripts\Activate

# Reinstalar dependencias
pip install -r requirements.txt

# O instalar manualmente si no tienes requirements.txt
pip install Flask google-generativeai python-dotenv
```

### 💡 **¿Cuándo usar cada método de instalación?**
- **`pip install -r requirements.txt`** → Usa esto si clonaste el repositorio (RECOMENDADO)
- **`pip install Flask google-generativeai python-dotenv`** → Usa esto si empiezas desde cero o no tienes el archivo requirements.txt

### 📡 Configuración del ESP32

1. **Abrir Arduino IDE**
2. **Cargar `CodigoESP32.ino`**
3. **Configurar WiFi en el código:**
```cpp
const char* WIFI_SSID = "TU_RED_WIFI";
const char* WIFI_PASS = "TU_PASSWORD";
```
4. **Actualizar IP del servidor:**
```cpp
const char* API_URL = "http://TU_IP:5000/datos_esp32";
```
5. **Cargar código al ESP32**

### 🌐 Acceso a la Interfaz Web
- Abrir navegador en: `http://localhost:5000/`
- Para acceso desde otros dispositivos: `http://TU_IP:5000/`

## 💡 Explicación del Código

### 🔌 ESP32 (CodigoESP32.ino)
```cpp
// Conexión WiFi automática con reconexión
void connectWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    // Manejo de errores y timeouts
}

// Construcción de payload JSON con datos de sensores
String buildJson() {
    // Estructura JSON con datos de 2 canales
    // Incluye: voltaje, corriente, potencias, energía
}

// Envío HTTP POST al backend Flask
bool postJSON(const String& payload) {
    // Configuración de headers y autenticación
    // Manejo de respuestas y errores HTTP
}
```

### 🐍 Backend Flask (app.py)
```python
@app.route('/datos_esp32', methods=['POST'])
def recibir_datos_esp32():
    """Recibe datos del ESP32 y los procesa con Gemini AI"""
    datos = request.json
    # Construcción del prompt para Gemini
    # Análisis inteligente de consumo energético
    # Almacenamiento del análisis

@app.route('/get_analisis', methods=['GET'])  
def obtener_analisis():
    """API para obtener el último análisis generado"""
    return jsonify({"analisis": ultimo_analisis})
```

### 🌐 Frontend (index.html)
```javascript
async function actualizarAnalisis() {
    // Fetch asíncrono al backend
    // Manejo de estados de loading
    // Actualización dinámica del DOM
    // Gestión de errores de red
}
```

## 📚 Librerías y Dependencias

### Python (Backend)
- **Flask** `v3.0+` - Framework web minimalista y potente
- **google-generativeai** `v0.3+` - SDK oficial de Google Gemini
- **python-dotenv** `v1.0+` - Gestión segura de variables de entorno

### Arduino (ESP32)
- **WiFi.h** - Conectividad inalámbrica nativa ESP32
- **HTTPClient.h** - Cliente HTTP para comunicación REST

### Frontend
- **Fetch API** - Nativo del navegador, no requiere librerías externas
- **CSS Grid/Flexbox** - Layout responsivo moderno

## 📄 Licencia

```
MIT License

Copyright (c) 2025 CenfoTec-Cedula5 Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## 🔧 Usos del Sistema

### 🏠 **Hogar Inteligente**
- Monitoreo de consumo por habitaciones
- Detección de electrodomésticos con alta demanda
- Alertas de consumo anómalo
- Recomendaciones de ahorro energético

### 🏢 **Pequeñas Empresas**
- Control de costos energéticos operativos
- Optimización de horarios de operación
- Reporting automático de consumo
- Cumplimiento de normativas energéticas

### 🎓 **Educación**
- Enseñanza de conceptos de IoT
- Prácticas de programación Full-Stack
- Experimentos con IA aplicada
- Proyectos de sostenibilidad

## ⚠️ Problemas Conocidos y Soluciones

### 🔴 **Problema: Pérdida de conexión WiFi del ESP32**
- **Causa:** Señal débil o interferencias
- **Solución:** Implementar reconexión automática cada 30 segundos
- **Código:** Función `connectWiFi()` con timeout y retry logic

### 🔴 **Problema: Sobrecarga de API de Gemini**
- **Causa:** Demasiadas consultas por minuto
- **Solución:** Implementar rate limiting y cache local
- **Mejora futura:** Queue de procesamiento asíncrono

### 🔴 **Problema: Precisión de mediciones eléctricas**
- **Causa:** Ruido en sensores analógicos
- **Solución:** Filtros digitales y calibración periódica
- **Recomendación:** Usar ADC externos de mayor resolución

### 🔴 **Problema: Seguridad de API Keys**
- **Causa:** Exposición accidental de credenciales
- **Solución:** Variables de entorno y .gitignore apropiado
- **Buena práctica:** Rotación periódica de keys

### 🔴 **Problema: Escalabilidad para múltiples dispositivos**
- **Causa:** Arquitectura monolítica actual
- **Solución futura:** Implementar base de datos y microservicios
- **Tecnologías:** PostgreSQL, Docker, Redis para cache

## 🚀 Roadmap de Mejoras

### 📊 **Corto Plazo (1-2 meses)**
- [ ] Base de datos para histórico de mediciones
- [ ] Gráficos interactivos con Chart.js
- [ ] Alertas por email/SMS
- [ ] Modo offline del ESP32

### 🔮 **Mediano Plazo (3-6 meses)**
- [ ] App móvil React Native
- [ ] Dashboard administrativo
- [ ] API REST completa con autenticación
- [ ] Integración con otros sensores (temperatura, humedad)

### 🌟 **Largo Plazo (6+ meses)**
- [ ] Machine Learning para predicción de consumo
- [ ] Integración con smart grid
- [ ] Certificación para uso comercial
- [ ] Marketplace de plugins

---


