#include <Arduino.h>
#include <WebServer.h>
#include <WiFi.h>


// Wifi Configuration Constants
const char* SSID = "xxx";         // Network name to connect to
const char* PWD = "xxx";               // Network password
const char* HOSTNAME = "xxx";  // Easily identifiable on the network

// Web server running on port 80
WebServer server(80);


void initWiFi() {
  /*
  Connect to the WiFi network and set hostname
  */
  WiFi.setHostname(HOSTNAME);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);
  Serial.println();

  WiFi.begin(SSID, PWD);

  while(WiFi.status() != WL_CONNECTED) {
      delay(300);
      Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void initCallbacks() {
  /*
  Set HTTP server callback functions
  */
  server.on("/", handleOnConnect);
  server.on("/testOne", handleOnTestOne);
  server.on("/testTwo", handleOnTestTwo);
  server.onNotFound(handleNotFound);
}

void handleOnConnect() {
  Serial.println("Client connection handler!!");
  server.send(200, "text/plain", "c");
}

void handleOnTestOne() {
  Serial.println("test one handler!!");
  server.send(200, "text/plain", "1");
}

void handleOnTestTwo() {
  Serial.println("test two handler!!");
  server.send(200, "text/plain", WiFi.getHostname());
}

void handleNotFound() {
  Serial.println("Client not found handler!!");
  server.send(404, "text/plain", "Not found");
}


void setup() {
  Serial.begin(115200);
  
  initWiFi();
  initCallbacks();  
  server.begin();
}


void loop() {
  server.handleClient();
}
