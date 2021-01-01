// Board ESP32

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "JK-HOME";
const char *password = "f33dm3mor3";

int LDR_PIN = 33;

WebServer server(80);

void setup(void) {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to ssid");
  Serial.println(ssid);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println(WiFi.status());
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/plain", "hello from esp32!");
  });

  server.on("/light",[]() {
    int ldr_value = analogRead(LDR_PIN);
    Serial.println("LDR value requested");
    Serial.println(ldr_value);
    String ldr_string = String(ldr_value);
    server.send(200,"text/plain",ldr_string);
  });

  server.on("/users/{}", []() {
    String user = server.pathArg(0);
    server.send(200, "text/plain", "User: '" + user + "'");
  });
  
  server.on("/users/{}/devices/{}", []() {
    String user = server.pathArg(0);
    String device = server.pathArg(1);
    server.send(200, "text/plain", "User: '" + user + "' and Device: '" + device + "'");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();

  //ldr_read();
  
}

void ldr_read () {
  Serial.println("Automated LDR read");
  Serial.println(analogRead(LDR_PIN));
  delay(1000);
}
