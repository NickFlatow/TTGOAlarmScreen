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

// read from seraial
#include <HardwareSerial.h>
#include <iostream>

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
// const int NUMBER_OF_DIGITS = 10;
const int NUMBER_OF_DIGITS = 11;
const int NUMBER_OF_COLUMNS = 5;
const int NUMBER_OF_ROWS = 3;

void wifiSetup();
// void handleRoot();
void screenSetup();
void buttonSetup();
void printTime();
void socket();
void printMiddle(String text);
std::string waitForSerialInput();

// interrupt service routines
void IRAM_ATTR toggleButton1() {
  if ( (millis() - lastDebounceButton1) > debounceDelay) {
    Serial.println(F("Button 1 pressed"));
    lastDebounceButton1 = millis();
  }
}
void IRAM_ATTR toggleButton2() {
  if ( (millis() - lastDebounceButton2) > debounceDelay) {
    Serial.println(F("Button 2 pressed"));
    lastDebounceButton1 = millis();
  }
}

void numberStuff();


//ADD PRECEDING AND TRAILING 0s FOR SPACE IN EACH OBJECT
byte digit[NUMBER_OF_DIGITS][NUMBER_OF_COLUMNS][NUMBER_OF_ROWS] = {
  {
    {1,1,1}, //0
    {1,0,1},
    {1,0,1},
    {1,0,1},
    {1,1,1}

  },
  {
    {0,1,0}, //1
    {0,1,0},
    {0,1,0},
    {0,1,0},
    {0,1,0}

  },
  {
    {1,1,1}, //2
    {0,0,1},
    {1,1,1},
    {1,0,0},
    {1,1,1}

  },
  {
    {1,1,1}, //3
    {0,0,1},
    {1,1,1},
    {0,0,1},
    {1,1,1}

  },
  {
    {1,0,1}, //4
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {0,0,1}

  },
  {
    {1,1,1}, //5
    {1,0,0},
    {1,1,1},
    {0,0,1},
    {1,1,1}

  },
  {
    {1,1,1}, //6
    {1,0,0},
    {1,1,1},
    {1,0,1},
    {1,1,1}

  },
  {
    {1,1,1}, //7
    {0,0,1},
    {0,0,1},
    {0,0,1},
    {0,0,1}

  },
  {
    {1,1,1}, //8
    {1,0,1},
    {1,1,1},
    {1,0,1},
    {1,1,1}

  },
  {
    {1,1,1}, //9
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {1,1,1}

  },
  {
    {0,0,0}, //:
    {0,1,0},
    {0,0,0},
    {0,1,0},
    {0,0,0}
  }     
};
        
byte colon[1][NUMBER_OF_COLUMNS][NUMBER_OF_ROWS]=  {
      {
      // {0,1,0}, //:
      // {0,1,0},
      // {0,0,0},
      // {0,1,0},
      // {0,1,0}

      {0,0,0}, //:
      {0,1,0},
      {0,0,0},
      {0,1,0},
      {0,0,0}
      
      }
  };