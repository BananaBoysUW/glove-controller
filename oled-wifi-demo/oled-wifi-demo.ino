#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width
#define SCREEN_HEIGHT 64 // OLED display height
#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "BananaBoys"
#define APPSK  "SaraBananaBoys"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
 */
void handleRoot() {
    server.send(200, "text/html", "<h1>You are connected. Hi Sara!</h1>");
}

// change the oled text to the passed string
void oledText(String s) {
    display.clearDisplay();

    display.setCursor(0, 0);
    display.print(s);

    display.display();
}
// reply to oled change content request
// http://192.168.4.1/oled?content=YOURCONTENT
void handleOled() {
    server.send(200, "text/html", "Changing OLED content.");
    oledText(server.arg("content"));
}

void setup() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // Clear the display buffer
    display.clearDisplay();
    display.display();

    display.setTextSize(2);
    display.setTextColor(WHITE);

    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    /* Serial.print("AP IP address: "); */
    /* Serial.println(myIP); */
    server.on("/", handleRoot);
    server.on("/oled", handleOled);
    server.begin();
}

void loop() {
    server.handleClient();
}
