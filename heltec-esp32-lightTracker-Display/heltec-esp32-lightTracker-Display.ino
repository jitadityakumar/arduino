#include                              "WiFi.h"
#include                              <U8g2lib.h>
#include                              <HTTPClient.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C   u8g2(U8G2_R0, 16, 15, 4);
const char *ssid = "JK-HOME";
const char *password = "f33dm3mor3";

const char* serverNameLight = "http://192.168.1.128/light";
String lightVal;
int lightCounter = 0;


void setup() {
  // Initialize the graphics library.
  
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  // Clear Buffer
  u8g2.clearBuffer();
  
  // Set up WiFi
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to ssid");
  Serial.println(ssid);

  u8g2.drawStr(0,0,"Connecting to");
  u8g2.drawStr(0,8,ssid);
  u8g2.sendBuffer();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println(WiFi.status());
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  IPAddress ip = WiFi.localIP();
  char bufIP[64];
  sprintf(bufIP, "%d.%d.%d.%d", ip[0],ip[1],ip[2],ip[3]);

  u8g2.drawStr(0,24,"Connected");
  u8g2.drawStr(0,34,bufIP);
  u8g2.sendBuffer();
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  lightCounter++;

  if (WiFi.status() == WL_CONNECTED) {
    lightVal = httpGetRequest(serverNameLight);
    Serial.println("LightVal : "+lightVal);

    u8g2.clearBuffer();
    u8g2.drawStr(0,0,"Light Tracker");
    char bufVal[64];
    sprintf(bufVal,"Value: %s",lightVal);
    u8g2.drawStr(0,16,bufVal);
    char bufCount[64];
    sprintf(bufCount,"Counter: %d",lightCounter);
    u8g2.drawStr(0,32,bufCount);
    u8g2.sendBuffer();
  } else {
    Serial.println("WiFi Disconnected");
    u8g2.clearBuffer();
    u8g2.drawStr(0,0,"WiFi Disconnected");
    u8g2.sendBuffer();
  }
  
  // Delay before trying again
  delay(15000);

}

String httpGetRequest(const char* serverName) {

  HTTPClient http;
  http.begin(serverName);

  int httpResponseCode = http.GET();

  String payload = "--";

  if (httpResponseCode>0) {
    payload = http.getString();
  } else {
    Serial.println("Error Code");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}
