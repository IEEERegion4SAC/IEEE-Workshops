/*
 * ----------------------------------------------------------------------------------------------
 * NodeMCU_Workshop.ino
 * IEEE Section 4 NodeMCU Workshop
 * 
 * This workshop will use the NodeMCU board to start a simple HTTP server and read to request to
 * turn the built-in or an external LED ON and OFF.
 * 
 * @license This code is in the public domain.
 * 
 * Created 06-DEC-2021
 * by Fernando Leira Cortel
 * Modified 06-DEC-2021
 * by Fernando Leira Cortel
 * ----------------------------------------------------------------------------------------------
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Phantom"
#define STAPSK  "Ford*Detroit2020"
#endif

// SSID and Password variables for WiFi Connection
const char* ssid     = STASSID;
const char* password = STAPSK;

// Define ESP8266 Server
ESP8266WebServer server(80);

// Initial State for LED & Response Message
int led = 0;
String msg;

void setup() {
  // Start serial at a 115200 bits/s
  Serial.begin(115200);

  // Start WiFi connection
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait until connection is completed
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start MDNS
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  // Define server routes
  server.on("/", rootRoute);
  server.on("/led", ledRoute);

  // Start HTTP server
  server.begin();
  Serial.println("HTTP server started");

  // Set LED as output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, led);
}

void loop() {
  // Listen for HTTP requests
  server.handleClient();
}

// Define route for rrot handle
void rootRoute() {
  if (server.method() != HTTP_GET) {
    server.send(405, "text/plain", "HTTP Method not allowed");
  }
  else {
    server.send(200, "text/plain", "IEEE NodeMCU Workshop!!!");
  }
}

// Define route for LED handle
void ledRoute() {
  // Check if request is GET
  if (server.method() == HTTP_GET) {
    msg = "Current LED state: ";
    if (led) msg += "OFF.";
    else msg += "ON.";
    server.send(200, "text/plain", msg);
  }
  // Check if request is POST
  else if (server.method() == HTTP_POST) {
    if (server.args() > 0){
      if (server.arg(0) == "1") led = 0;
      else if (server.arg(0) == "0") led = 1;
      digitalWrite(LED_BUILTIN, led);
    }
    server.send(200, "text/plain", "LED updated!");
  }
  // Other type of request is not valid
  else {
    server.send(405, "text/plain", "HTTP Method not allowed");
  }
}
