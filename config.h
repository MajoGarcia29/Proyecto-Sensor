#ifndef CONFIG_H
#define CONFIG_H

// ======== Pines de motores ========
#define ENA 25
#define IN1 26
#define IN2 27
#define IN3 14
#define IN4 12
#define ENB 13

// ======== Pines del sensor HC-SR04 ========
#define TRIG 5
#define ECHO 18

// ======== Configuración WiFi ========
#define WIFI_SSID "TuWiFi"
#define WIFI_PASS "TuContraseñaWiFi"

// ======== Configuración MQTT ========
#define MQTT_BROKER "test.mosquitto.org"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "ESP32_Majo"
#define MQTT_TOPIC_SENSOR "majo/sensor/distancia"
#define MQTT_TOPIC_MOVIMIENTO "majo/robot/movimiento"

#endif
