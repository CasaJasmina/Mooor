#include <SD.h>
#include <AudioZero.h>
#include <WiFi101.h>
#include <ArduinoCloud.h>
#include <WiFiSSLClient.h>

int relayPin = 4;
int DoorbellCloud;
const char* ssid = "****";
const char* pass = "****";

const char userName[]   = "****";
const char thingName[] = "****";
const char thingId[]   = "****";
const char thingPsw[]  = "****";

WiFiSSLClient sslClient;
ArduinoCloudThing MoooreSlave;

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.begin(9600);
  Serial.print("Connecting Wifi: ");
  WiFi.begin(ssid, pass);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Initializing SD card...");
  if (!SD.begin(6)) {
    Serial.println(" failed!");
    while (true);
  }
  Serial.println(" done.");

  MoooreSlave.begin(thingName, userName, thingId, thingPsw, sslClient);
  MoooreSlave.enableDebug();
  MoooreSlave.addExternalProperty("MoooreMaster", "StartRing", CHARSTRING);
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    delay(1000);
    MoooreSlave.begin(thingName, userName, thingId, thingPsw, sslClient);
    MoooreSlave.enableDebug();
    MoooreSlave.addExternalProperty("MoooreMaster", "StartRing", CHARSTRING);
  }

  MoooreSlave.poll();
  DoorbellCloud = MoooreSlave.readProperty("MoooreMaster", "StartRing").toInt();
  Serial.println(DoorbellCloud);
  if (DoorbellCloud == 1) {
    digitalWrite(relayPin, HIGH);
    playSound();
  }

}

void playSound() {

  AudioZero.begin(44100); // 44100kHz stereo => 88200 sample rate
  File myFile = SD.open("ring.wav"); // open wave file from sdcard
  if (!myFile) {
    Serial.println("error opening ring.wav");
    while (true);
  }
  Serial.print("Playing");
  AudioZero.play(myFile);
  Serial.println("End");
  AudioZero.end();
  digitalWrite(relayPin, LOW);

}

