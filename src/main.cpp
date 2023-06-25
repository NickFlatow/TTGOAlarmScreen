//TTGO
#include <Arduino.h>
#include <TFT_eSPI.h>

//clock
#include <ctime>

//web server
#include <WiFi.h>
#include <WebServer.h>
#include <flarg.h>


#define BUTTON1PIN 35
#define BUTTON2PIN 0

TFT_eSPI tft = TFT_eSPI();

WiFiClient espClient;
WebServer server(80);


long lastDebounceButton1 = 0; 
long lastDebounceButton2 = 0;
long debounceDelay = 200;

void wifiSetup();
void handleRoot();
void screenSetup();
void buttonSetup();
void updateTime();
String formatDigits(int digits);

// interrupt service routines
void IRAM_ATTR toggleButton1() {
  if ( (millis() - lastDebounceButton1) > debounceDelay) {
    Serial.println(F("Button 1 pressed"));
    lastDebounceButton1 = millis();
  }
  
}
void IRAM_ATTR toggleButton2() {
  if ( (millis() - lastDebounceButton1) > debounceDelay) {
    Serial.println(F("Button 2 pressed"));
    lastDebounceButton1 = millis();
  }
}



void setup() { 
  // put your setup code here, to run once: 
  Serial.begin(9600);
  Serial.println("");
  Serial.println(F("Hello World!"));

  tft.init();
  wifiSetup();
  screenSetup();
  buttonSetup();
}

void loop() {
  server.handleClient();
  delay(1000);
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color
  int xPos = 0;
  int yPos = 30;
  //uppper left line (eg weather icon)
  tft.setCursor(xPos,yPos);
  tft.println("wIcon");
  
  //lower left line (eg alarm set)
  tft.setCursor(0,120);
  tft.println("aIcon");

  // // //2/3 screen width
  // int x = (tft.width()/3*2) - 20;
  // // //middle of screen
  // int y = tft.height()/2;
  // tft.setTextSize(3);
  // tft.setCursor(x,y);

  // time_t currentTime = time(0);
  // String tString = ctime(&currentTime);
  // Serial.println(tString);
}
void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".");
  Serial.println("Wifi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.begin();
}
void handleRoot() {
  String s = "<html><head><title>ESP32 Clock</title></head><body><h1>ESP32 Clock</h1></body></html>";
  server.send(200, "text/html", s);
}
void screenSetup() { 
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setFreeFont(&Orbitron_Light_24);
}
void buttonSetup() {
  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT_PULLUP); //button 2 only works with pullup ???
  attachInterrupt(BUTTON1PIN, toggleButton1, FALLING);
  attachInterrupt(BUTTON2PIN, toggleButton2, FALLING);
}
void updateTime() {
  // Get current time
  unsigned long currentTime = millis();
  unsigned long seconds = currentTime / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  // Format time as a string
  String timeString = String(hours % 12) + ":" + formatDigits(minutes % 60) + ":" + formatDigits(seconds % 60);

  // Clear the previous time
  tft.fillRect(0, 0, tft.width(), 30, TFT_BLACK);

  // Print the updated time
  tft.setCursor((tft.width() - (timeString.length() * 18)) / 2, 0); // Adjust the positioning if needed
  tft.println(timeString);
}
String formatDigits(int digits) {
  if (digits < 10) {
    return "0" + String(digits);
  }
  return String(digits);
}
