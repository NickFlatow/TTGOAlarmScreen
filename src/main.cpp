#include <main.h>

void setup() { 
  // put your setup code here, to run once: 
  Serial.begin(9600);
  Serial.println("");
  // Serial.println(F("Hello World!"));

  tft.init();
  wifiSetup();
  screenSetup();
  buttonSetup();
  //init ntp
  timeClient.begin();
}

void loop() {
  // server.handleClient();
  timeClient.update();
  delay(1000);
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color

  // int xPos = 0;
  // int yPos = 30;
  // //uppper left line (eg weather icon)
  // tft.setCursor(xPos,yPos);
  // tft.println("wIcon");
  
  // //lower left line (eg alarm set)
  // tft.setCursor(0,120);
  // tft.println("aIcon");

  // // //2/3 screen width
  int x = (tft.width()/3*2) -80;
  // // //middle of screen
  int y = tft.height()/2;
  // tft.setTextSize(3);
  tft.setCursor(x,y);

  tft.setFreeFont(&Orbitron_Light_32);
  // tft.setTextDatum(MC_DATUM);
  // tft.setTextSize(2);
  Serial.println(timeClient.getFormattedTime());
  String mins = timeClient.getMinutes() < 10 ? "0" + String(timeClient.getMinutes()) : String(timeClient.getMinutes());
  String hours = timeClient.getHours() < 10 ? "0" + String(timeClient.getHours()) : String(timeClient.getHours());
  tft.println(hours + ":" + mins);
  // tft.println(timeClient.getFormattedTime());

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
  // server.on("/",handleRoot);
  // server.begin();
}

// void handleRoot() {
//   String s = "<html><head><title>ESP32 Clock</title></head><body><h1>ESP32 Clock</h1></body></html>";
//   server.send(200, "text/html", s);
// }

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
