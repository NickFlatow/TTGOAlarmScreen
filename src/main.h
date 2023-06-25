//TTGO
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <stdio.h>

//NTP
#include <NTPClient.h>
#include <WiFiUdp.h>

//clock
#include <ctime>

//web server
#include <WiFi.h>
#include <WebServer.h>
#include <flarg.h>

#define BUTTON1PIN 35
#define BUTTON2PIN 0
#define UTC_OFFEST_IN_SECONDS 3600 * 5 * -1 //UTC -5 hours

TFT_eSPI tft = TFT_eSPI();

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFEST_IN_SECONDS);
WiFiClient espClient;

//TODO NOT NEEDED
WebServer server(80);

long lastDebounceButton1 = 0; 
long lastDebounceButton2 = 0;
long debounceDelay = 200;

void wifiSetup();
void handleRoot();
void screenSetup();
void buttonSetup();

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
