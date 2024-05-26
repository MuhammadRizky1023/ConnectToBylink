
#define BLYNK_TEMPLATE_ID "TMPL3-zIw4drH"
#define BLYNK_TEMPLATE_NAME "ThinkIOT"

#define BLYNK_AUTH_TOKEN "EmyoTZtnQtMdI8O8o_jPO_Ic_E26mFlD"

#include <DHTesp.h>
#include <BlynkSimpleEsp32.h>
#define DHTPIN 15
#define LED_PIN 21

DHTesp dht;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  dht.setup(DHTPIN, DHTesp::DHT22); // Initialize DHT sensor
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendDHTData); // Send DHT data every 2 seconds
}

BLYNK_WRITE(V3) {
  int buttonState = param.asInt();
  if (buttonState == 1) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void sendDHTData() {
  float t = dht.getTemperature();
  float h = dht.getHumidity();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
}

void loop() {
  Blynk.run();
  timer.run();
}
