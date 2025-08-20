import os
import google.generativeai as genai
from flask import Flask, request, jsonify, send_file
from dotenv import load_dotenv

# Carga las variables del archivo .env (tu API Key)
load_dotenv()

# --- Configuración Inicial ---
app = Flask(__name__)

# Configura la API Key de Gemini desde la variable de entorno
try:
    genai.configure(api_key=os.environ["GOOGLE_API_KEY"])
except KeyError:
    print("Error: GOOGLE_API_KEY no encontrada. Asegúrate de tener un archivo .env válido.")
    exit()

# Variable global para almacenar el último análisis
ultimo_analisis = "Aún no se han recibido datos del ESP32."

# --- Creación del Modelo Gemini ---
# --- Creación del Modelo Gemini ---
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

# --- Iniciar el Servidor ---
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)