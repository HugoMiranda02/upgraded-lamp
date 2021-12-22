#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#define PIN 12
#define NUM_PIXELS 8
#define EEPROM_SIZE 24
#include <EEPROM.h>
const char* ssid     = "Vivas_F_Miranda";
const char* password = "KKHG0715";
WiFiServer server(8088);
IPAddress local_IP(192, 168, 1, 111);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

bool gira = false;
bool rgb = false;
bool statico = false;

int r;
int g;
int b;

int colors[5][3];

String quantidade;


Adafruit_NeoPixel pixels(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

String split(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void clearPixels() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
}

void setup()
{
  pixels.begin();
  EEPROM.begin(EEPROM_SIZE);
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);
  /* connecting to WiFi */
  WiFi.begin(ssid, password);
  /*wait until ESP32 connect to WiFi*/
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\r\nWiFi connected with IP address: ");
  Serial.println(WiFi.localIP());
  /* start Server */
  byte primeiroByte = EEPROM.read(1);
  byte segundoByte = EEPROM.read(2);
  int r_ = (segundoByte << 8) + primeiroByte;

  primeiroByte = EEPROM.read(3);
  segundoByte = EEPROM.read(4);
  int g_ = (segundoByte << 8) + primeiroByte;

  primeiroByte = EEPROM.read(5);
  segundoByte = EEPROM.read(6);
  int b_ = (segundoByte << 8) + primeiroByte;
  Serial.println(r_);
  Serial.println(g_);
  Serial.println(b_);
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r_, g_, b_));
    pixels.show();
  }
  server.begin();
}
void loop() {

  /* listen for client */
  WiFiClient client = server.available();
  uint8_t data[30];
  if (client) {
    Serial.println("new client");
    /* check client is connected */
    while (client.connected()) {
      if (client.available()) {
        int len = client.read(data, 30);
        if (len < 30) {
          data[len] = '\0';
        } else {
          data[30] = '\0';
        }
        Serial.print("client sent: ");
        Serial.println((char *)data);
        String mystring((char*)data);
        String r = split(mystring, ',', 0);
        String g = split(mystring, ',', 1);
        String b = split(mystring, ',', 2);
        for (int i = 0; i < NUM_PIXELS; i++) {
          pixels.setPixelColor(i, pixels.Color(r.toInt(), g.toInt(), b.toInt()));
          pixels.show();
        }

        byte r1 = r.toInt() & 0xff;
        byte r2 = (r.toInt() >> 8) & 0xff;
        byte g1 = g.toInt() & 0xff;
        byte g2 = (g.toInt() >> 8) & 0xff;
        byte b1 = b.toInt() & 0xff;
        byte b2 = (b.toInt() >> 8) & 0xff;

        EEPROM.write(1, r1);
        EEPROM.write(2, r2);
        EEPROM.write(3, b1);
        EEPROM.write(4, b2);
        EEPROM.write(5, g1);
        EEPROM.write(6, g2);


      }
    }
  }
}