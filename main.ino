#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

// ======== Inicialización WiFi y MQTT ========
WiFiClient espClient;
PubSubClient client(espClient);

// ======== Conectar WiFi ========
void conectarWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.println(WiFi.localIP());
}

// ======== Conectar MQTT ========
void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando al broker MQTT...");
    if (client.connect(MQTT_CLIENT_ID)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" Intentando de nuevo en 5s");
      delay(5000);
    }
  }
}

// ======== Lectura simulada o real del sensor ========
float leerDistancia() {
  // Opción 1: Simulada (para pruebas)
  // return random(5, 100) / 1.0;

  // Opción 2: Física (usar divisor de voltaje para ECHO)
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracion = pulseIn(ECHO, HIGH);
  float distancia = duracion * 0.034 / 2;  // en cm
  return distancia;
}

// ======== Setup ========
void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  conectarWiFi();
  client.setServer(MQTT_BROKER, MQTT_PORT);
  conectarMQTT();
}

// ======== Loop principal ========
void loop() {
  if (!client.connected()) conectarMQTT();
  client.loop();

  float distancia = leerDistancia();
  Serial.printf("Distancia medida: %.2f cm\n", distancia);

  // Publicar al tema MQTT del sensor
  char mensaje[20];
  dtostrf(distancia, 6, 2, mensaje);
  client.publish(MQTT_TOPIC_SENSOR, mensaje);

  delay(2000); // cada 2 segundos
}
