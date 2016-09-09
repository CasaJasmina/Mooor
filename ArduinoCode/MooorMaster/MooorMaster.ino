# include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <Encoder.h>
#include <WiFi101.h>
#include <ArduinoCloud.h>
#include <WiFiSSLClient.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <SD.h>
#include "DHT.h"
RTCZero rtc;
WiFiUDP Udp;
Encoder *myEnc;
int sensorPin = A6;

#define DHTPIN      4     // what digital pin we're connected to  
#define DHTTYPE     DHT22   // DHT 22  (AM2302), AM2321

#define TFT_CS     6
#define TFT_RST    7
#define TFT_DC     11
#define SD_CS      3


// UDP setup
unsigned int localPort = 2390;      // local port to listen for UDP packets
IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
const int GMT = 2; //change this to adapt it to your time zone   hours*minutes*seconds

const int buttonPin = 2;


const char userName[]   = "****";
const char thingName[] = "****";
const char thingId[]   = "****";
const char thingPsw[]  = "****";

const char* ssid = "****";
const char* pass = "****";

int encoderValue = 0;
int Counter = 0;
long oldPosition  = -999;
unsigned long homeTimer;
unsigned long TIMER;
bool tempflag = false;
bool tempSetted = false;
int temp;
int STATE;
int desiredTemp;
int sensorValue = 0;
int DoorbellCloud;
long lastPressed;
bool ring;


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

WiFiSSLClient sslClient;
DHT dht(DHTPIN, DHTTYPE);
ArduinoCloudThing MoooreMaster;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
  homeTimer = millis();
  pinMode(5, INPUT_PULLUP);
  Serial.println("Basic Encoder Test:");
  myEnc = new Encoder(0, 1);
  attachInterrupt(5, ButtonPressed, FALLING);

  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }

  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1); // horizontal display
  tft.fillScreen(ST7735_BLACK);
  tft.drawRect(10, 50, 128, 35, ST7735_WHITE);
  tft.setCursor(50, 60);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.println("HELLO");

  Serial.begin(9600);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  Serial.println("");
  Serial.println("WiFi connected");
  rtc.begin();
  GetCurrentTime();
  temp = GetTemp();
  MoooreMaster.begin(thingName, userName, thingId, thingPsw, sslClient);
  MoooreMaster.enableDebug();
  MoooreMaster.addProperty("StartRing", CHARSTRING, RW);

  delay(1000);
  displayHome();
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    delay(1000);
    MoooreMaster.begin(thingName, userName, thingId, thingPsw, sslClient);
    MoooreMaster.enableDebug();
    MoooreMaster.addProperty("StartRing", CHARSTRING, RW);
  }

  if (digitalRead(buttonPin) == 1) {
    Serial.println("pressed");
    Display_Doorbell();
    ring = true;

  }



  switch  (STATE) {

    case 0:
      if (millis() - TIMER > 200) {
        MoooreMaster.poll();
        TIMER = millis();
        if (ring) {
          MoooreMaster.writeProperty("StartRing", "1");
          STATE = 6;
          ring = false;
        }
        else {
          MoooreMaster.writeProperty("StartRing", "0");
        }
      }

      break;

    case 1:
      // Serial.println("I'm here");
      NavMenu();
      break;

    case 2:
      NavMenuTwo();
      break;

    case 3:
      SetTemp();
      break;

    case 4:
      Display_Confirm();
      break;

    case 5:
      Display_NotImplemented();
      break;

    case 6:
      sensorValue = analogRead(sensorPin);
      if (sensorValue > 300) {
        Serial.println("sensor activated");
        MoooreMaster.poll();
        MoooreMaster.writeProperty("StartRing", "0");
        STATE = 7;
        Display_Phone();
      }
      break;


    case 7:
      if (millis() - TIMER > 500) {
        MoooreMaster.poll();
        MoooreMaster.writeProperty("StartRing", "0");
        TIMER = millis();
      }
      break;

    case 8:
      Display_Gate();
      break;

  }

  //  if (millis() - homeTimer > 20000) {
  //    STATE = 0;
  //    homeTimer = millis();
  //    temp = GetTemp();
  //    displayHome();
  //  }
}







