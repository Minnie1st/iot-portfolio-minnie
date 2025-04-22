#include <Wire.h>
#include <VL53L0X.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// VL53L0X 设置
VL53L0X sensor;
const int CONTAINER_HEIGHT_MM = 159;  // 实际容器高度（单位：mm）

// WiFi 设置
const char* ssid = "router12";
const char* password = "iot123456789";

// MQTT 设置
const char* mqtt_server = "192.168.14.1";
const int mqtt_port = 1883;
const char* mqtt_topic = "liquid/laser";

WiFiClient espClient;
PubSubClient client(espClient);

// 连接 WiFi
void setup_wifi() {
  Serial.print("🔌 正在连接 WiFi: ");
  WiFi.begin(ssid, password);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries++ < 20) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi 已连接");
    Serial.print("IP 地址: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi 连接失败！");
  }
}

// 连接 MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("正在连接 MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("已连接");
    } else {
      Serial.print("失败（状态码: ");
      Serial.print(client.state());
      Serial.println("），2秒后重试...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);  // SDA, SCL
  delay(100);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  Serial.println("启动 VL53L0X...");
  if (!sensor.init()) {
    Serial.println("❌ 传感器初始化失败！");
    while (1);
  }

  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int distance = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) {
    Serial.println("读取超时");
    return;
  }

  int level = CONTAINER_HEIGHT_MM - distance;
  if (level < 0) level = 0;

  Serial.print("📏 液位高度: ");
  Serial.print(level);
  Serial.println(" mm");

  // 发送 MQTT 消息
  char payload[16];
  snprintf(payload, sizeof(payload), "%d", level);
  client.publish(mqtt_topic, payload);
  Serial.println("📤 已发送 MQTT");

  delay(2000);
}
