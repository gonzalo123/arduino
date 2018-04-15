#include <M5Stack.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* topic = "/m5stack/+";

const char* ssid = "ssid";
const char* password = "password";
const char* server = "192.168.1.111";
const char* clientName = "com.gonzalo123.m5stack";

int i = 0;
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void wifiConnect() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  Serial.print("WiFi connected: ");
  Serial.println(WiFi.localIP());
}

void mqttReConnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientName)) {
      Serial.println("connected");
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);

  String data;
  for (int i = 0; i < length; i++) {
    data += (char)payload[i];
  }

  if (strcmp(topic, "/m5stack/1") == 0) {
    M5.Lcd.drawJpgFile(SD, "/batman.jpg");
    M5.Lcd.setCursor(35, 100);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print(data);
  }

  Serial.print("] value:");
  Serial.println(data);
}


void setup() {

  Serial.begin(115200);
  M5.begin();
  wifiConnect();
  client.setServer(server, 1883);
  client.setCallback(callback);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 100);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(5);
  M5.Lcd.print("Connecting");

  delay(1500);

}

// the loop routine runs over and over again forever
void loop() {
  if (!client.connected()) {
    mqttReConnect();
  }
  client.loop();
  delay(200);
}