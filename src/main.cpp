#include <main.h>

short colors[2]={TFT_BLACK,TFT_GREEN};  //first colour is color of background , second is color of digit


// int boxSize=20;   //size of each box
// byte space=8; // space between boxes
// int fromTop=8;  //positon x
// int fromLeft=10;  //position y
// int Round=1;

int boxSize=10;   //size of each box
byte space=4; // space between boxes
int fromTop=8;  //positon x
int fromLeft=10;  //position y
int Round=1;
// short number=0;
int digits=0;


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
  
  // delay(1000);
  numberStuff();
  // printTime();
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
void printTime() {
  timeClient.update();

  //instead of fillScreen 
  //crawl the entire screen with fill rect in a loop
  tft.fillScreen(TFT_BLACK); // Clear the screen with black color
  //2/3 screen width
  int x = (tft.width()/3*2) -80;
  //middle of screen
  int y = tft.height()/2;
  tft.setCursor(x,y);
  tft.setFreeFont(&Orbitron_Light_32);

  Serial.println(timeClient.getFormattedTime());
  String mins = timeClient.getMinutes() < 10 ? "0" + String(timeClient.getMinutes()) : String(timeClient.getMinutes());
  String hours = timeClient.getHours() < 10 ? "0" + String(timeClient.getHours()) : String(timeClient.getHours());

  tft.println(hours + ":" + mins);
}

void numberStuff() {
  timeClient.update();
  String numberString = timeClient.getHours() < 10 ? "0" + String(timeClient.getHours()) : String(timeClient.getHours());
  numberString += ":";
  //concate mins
  numberString += timeClient.getMinutes() < 10 ? "0" + String(timeClient.getMinutes()) : String(timeClient.getMinutes());

  // String numberString = String(number);
  // Serial.print("numberString: ");
  // Serial.println(numberString);

  //numbers are the lenght of the string
  //e.g. 0 length is 1; 10 lenght is 2 etc.
  //this is how we move to the right to create space for 2 and 3 digit numbers
  for(int numbers=0; numbers < numberString.length();numbers++)
   for(int column=0;column < NUMBER_OF_COLUMNS;column++)
    for(int row=0; row < NUMBER_OF_ROWS; row++) {
        String substring = numberString.substring(numbers, numbers+1);
        // Serial.print("substring: ");
        // Serial.println(substring);
        if (substring == ":") {
          // Serial.println("found :");
          substring = "10";
        }
        int intSubString = substring.toInt();
        // int intSubString = timeClient.getHours();
        Serial.print("substring: ");
        Serial.println(intSubString);
        // Serial.print("numbers: ");
        // Serial.println(numbers);

        // int x = (numbers*(sizee*4))+fromLeft+(row*sizee)+(row*space);
        int x = (numbers*(boxSize*4))+fromLeft+(row*boxSize)+(row*space);
        int y = fromTop+(column*boxSize)+(column*space);
        int w = boxSize;
        int h = Round;
        int color = colors[digit[intSubString][column][row]];
        //serial output digit 
        Serial.print("digit: ");
        Serial.println(digit[intSubString][column][row]); 

        //TODO IF numberString > 0 add space between numbers

        //serial print for x,y,sizee,w,h,color
        // Serial.print("x: ");
        // Serial.println(x);
        // Serial.print("y: ");
        // Serial.println(y);
        // //add row and column
        // Serial.print("row: ");
        // Serial.println(row);
        // Serial.print("column: ");
        // Serial.println(column);

        // Serial.print("sizee: ");
        // Serial.println(sizee);
        // Serial.print("w: ");
        // Serial.println(w);
        // Serial.print("h: ");
        // Serial.println(h);
        // Serial.print("color: ");
        // Serial.println(color);
        // Serial.println("===================");

        tft.fillRoundRect(x,y,boxSize,w,h,color);
        // tft.fillRoundRect(10,10,10,10,10,TFT_RED);
        //delay(20);
  }


  // for(int numbers=0; numbers < 1;numbers++) {
  //  for(int column=0;column < NUMBER_OF_COLUMNS;column++) {
  //   for(int row=0; row < NUMBER_OF_ROWS; row++) {
  //       //160 is just trial and error
  //       //can we calculate this from the above loop?
  //       //where did x leave off?
  //       int x = 160 + fromLeft+(row*boxSize)+(row*space);
  //       int y = fromTop+(column*boxSize)+(column*space);
  //       int w = boxSize;
  //       int h = Round;
  //       int color = colors[colon[0][column][row]]; 
  //       // int color = colors[colon[column][row]]; 
  //       // Serial.println("+++++++++++");
  //       // Serial.println(colon[0][1][1]);
  //       // // Serial.println(colon[1][1]);
  //       // Serial.println("+++++++++++");


  //       // Serial.print("x: ");
  //       // Serial.println(x);
  //       // Serial.print("y: ");
  //       // Serial.println(y);
  //       // //add row and column
  //       // Serial.print("row: ");
  //       // Serial.println(row);
  //       // Serial.print("column: ");
  //       // Serial.println(column);

  //       // Serial.print("sizee: ");
  //       // Serial.println(boxSize);
  //       // Serial.print("w: ");
  //       // Serial.println(w);
  //       // Serial.print("h: ");
  //       // Serial.println(h);
  //       // Serial.print("color: ");
  //       // Serial.println(color);
  //       // Serial.print("colon: ");
  //       // Serial.println(colon[1][column][row]);
  //       // Serial.println("===================");

  //       tft.fillRoundRect(x,y,10,10,10,color);
  //   }
  //  }
  // }
  delay(400);
  // number++;

  // if(number==30)
  // number=0;
}
