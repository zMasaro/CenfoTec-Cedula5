"""
========================================================
BACKEND FLASK - SISTEMA DE MONITOREO ENERGÉTICO
========================================================

Descripción: Servidor web Flask que recibe datos del ESP32,
los procesa con Google Gemini AI y sirve una interfaz web.

Autor: CenfoTec-Cedula5 Team
Fecha: Agosto 2025
Versión: 1.0

Funcionalidades principales:
- API REST para recibir datos del ESP32
- Integración con Google Gemini AI para análisis
- Servidor web para interfaz de usuario
- Gestión de variables de entorno seguras

Endpoints disponibles:
- POST /datos_esp32 - Recibe datos del ESP32
- GET  /get_analisis - Retorna último análisis
- GET  / - Sirve la interfaz web principal

Dependencias requeridas:
- Flask 3.0+
- google-generativeai 0.3+
- python-dotenv 1.0+

========================================================
"""

import os
import google.generativeai as genai
from flask import Flask, request, jsonify, send_file
from dotenv import load_dotenv

# ========================================================
# CONFIGURACIÓN INICIAL DEL SISTEMA
# ========================================================

# Cargar variables de entorno desde archivo .env
# Esto permite mantener las API keys fuera del código fuente
load_dotenv()

# Crear instancia de la aplicación Flask
app = Flask(__name__)

# ========================================================
# CONFIGURACIÓN DE GOOGLE GEMINI AI
# ========================================================

# Configurar la API Key de Gemini desde variables de entorno
# La variable GOOGLE_API_KEY debe estar definida en el archivo .env
try:
    genai.configure(api_key=os.environ["GOOGLE_API_KEY"])
    print("✅ Google Gemini AI configurado correctamente")
except KeyError:
    print("❌ Error: GOOGLE_API_KEY no encontrada en archivo .env")
    print("📝 Crea un archivo .env con: GOOGLE_API_KEY=tu_api_key_aqui")
    exit(1)

# Variable global para almacenar el último análisis generado
# Permite que múltiples usuarios vean el mismo análisis sin re-procesar
ultimo_analisis = "Aún no se han recibido datos del ESP32. Esperando primera medición..."

# ========================================================
# INICIALIZACIÓN DEL MODELO GEMINI
# ========================================================

# Crear instancia del modelo Gemini Flash (versión optimizada)
# gemini-1.5-flash-latest es más rápido y económico que el modelo completo
model = genai.GenerativeModel('gemini-1.5-flash-latest')

# --- Rutas de la API ---
@app.route('/', methods=['GET'])
def servir_index():
    """Sirve la página principal (index.html) desde el mismo directorio del script.

    Evita el error 404 al entrar a http://<host>:5000/ desde otro dispositivo.
    """
    ruta_index = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'index.html')
    return send_file(ruta_index)

@app.route('/index.html', methods=['GET'])
def servir_index_alias():
    return servir_index()

@app.route('/datos_esp32', methods=['POST'])
def recibir_datos_esp32():
    global ultimo_analisis
    datos = request.json
    print(f"Datos recibidos del ESP32: {datos}")

    prompt = f"""
    Eres un experto en análisis de consumo eléctrico para un hogar.
    Analiza los siguientes datos JSON y proporciona un resumen claro y conciso en español.
    
    Datos recibidos:
    ```json
    {datos}
    ```
    
    Tu análisis debe incluir:
    1. Un resumen general del consumo total (suma de ambos canales).
    2. Un comentario sobre el factor de potencia, explicando si es bueno o malo (cercano a 1 es ideal).
    3. Identificar qué canal está consumiendo más energía activa.
    4. Proporciona una recomendación o una observación interesante basada en los datos.
    """

    try:
        response = model.generate_content(prompt)
        ultimo_analisis = response.text
        print(f"Análisis de Gemini: {ultimo_analisis}")
        return jsonify({"status": "éxito", "message": "Datos analizados correctamente."}), 200
    except Exception as e:
        print(f"Error al contactar con Gemini: {e}")
        ultimo_analisis = "Error al procesar los datos. Revisa la consola del servidor."
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/get_analisis', methods=['GET'])
def obtener_analisis():
    return jsonify({"analisis": ultimo_analisis})

# ========================================================
# INICIALIZACIÓN DEL SERVIDOR FLASK
# ========================================================

if __name__ == '__main__':
    """
    Punto de entrada principal del servidor Flask
    
    Configuración:
    - host='0.0.0.0': Permite acceso desde cualquier IP de la red local
    - port=5000: Puerto estándar para desarrollo Flask
    - debug=True: Habilita recarga automática y debugging detallado
    
    Acceso:
    - Local: http://127.0.0.1:5000/ o http://localhost:5000/
    - Red local: http://<IP_DE_TU_PC>:5000/ (desde otros dispositivos)
    
    Nota: En producción cambiar debug=False y usar un servidor WSGI
    como Gunicorn o uWSGI para mejor rendimiento y seguridad.
    """
    print("🚀 Iniciando servidor Flask...")
    print("📡 Endpoints disponibles:")
    print("   - GET  /          -> Interfaz web principal")
    print("   - POST /datos_esp32 -> Recibir datos del ESP32")
    print("   - GET  /get_analisis -> Obtener último análisis")
    print("🌐 Acceso local: http://127.0.0.1:5000/")
    print("📱 Acceso red: http://<tu-ip>:5000/")
    
    app.run(host='0.0.0.0', port=5000, debug=True)