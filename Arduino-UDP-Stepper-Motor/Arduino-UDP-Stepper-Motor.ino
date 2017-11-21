#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <stdio.h>
#include <string.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE};// randomly choosen MAC Adress
IPAddress ip(192, 168, 2, 10); //Arduino IP Adress. Has to be known of (python) script.

unsigned int localPort = 5000;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
String datReq;
int packetSize;
EthernetUDP Udp;

const int stepPin = 3;
const int dirPin = 4;

void setup() {
  Serial.begin(9600);
  Ethernet.begin( mac, ip);
  Udp.begin(localPort);
  delay(500);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  packetSize = Udp.parsePacket();
  
  if (packetSize > 0) {   //request is received if packetSize > 0
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    String datReq(packetBuffer);
    //Serial.print("Raw Input: "); // debug only
    //Serial.println(packetBuffer);
    String action = getValue(datReq, '-', 0);
    String motor = getValue(datReq, '-', 1); // not implemented yet...
    int steps = getValue(datReq, '-', 2).toInt();
    int speedDelay = getValue(datReq, '-', 3).toInt();
    int dir = getValue(datReq, '-', 4).toInt();

    if (action == "motor") {
      moveMotor(motor, steps, speedDelay, dir);
    }

    if (action == "print") {
      Serial.print("Motor: ");
      Serial.println(motor);  // not implemented yet...
      Serial.print("Steps: ");
      Serial.println(steps);
      Serial.print("SpeedDelay: ");
      Serial.println(speedDelay);
      Serial.print("Dir: ");
      Serial.println(dir);
    }
  }
  memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE);
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void moveMotor(String motor, int steps,int speedDelay, int dir) {
  // motor selector is not implemented yet...
  Serial.println(speedDelay);
  if (dir == 1) {
    digitalWrite(dirPin, HIGH);
    Serial.println("Dir is 1");
  }
  if (dir == 0) {
    digitalWrite(dirPin, LOW);
    Serial.println("Dir is 0");
  }
  Serial.println("Stepping now!");
  for (int x = 0; x < steps; x++) {
    digitalWrite(stepPin, HIGH);
    delay(speedDelay);
    digitalWrite(stepPin, LOW);
    delay(speedDelay);
  }
}

