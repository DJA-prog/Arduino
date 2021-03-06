#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "HomeADSL";
const char* password = "almirall";

const char* serverName = "http://192.168.178.59:80/post/index.php";
unsigned long lastTime = 0;
unsigned long timerDelay = 2000; //milli second

int mux_s1 = 14; // A
int mux_s2 = 12; // B
int mux_s3 = 13; // C
int mux_z[8];

int latchPin = 5; // st_cp  RCLK    
int clockPin = 16; // sh_cp SRCLK   
int dataPin = 4; // ds  SER         
bool shiftd[8] = {0,0,1,1,0,0,1,1};
byte shiftD = 0;

#include "DHT.h"
DHT dht(10, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(mux_s1, OUTPUT);
  pinMode(mux_s2, OUTPUT);
  pinMode(mux_s3, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(2, OUTPUT);
  analogWrite(2, 250); // built in LED to indicate power, Note some boards are GPIO1 other GPIO2, and may be inverted or not

  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "h="+String(h)+"&t="+String(t);        
      Serial.println(httpRequestData);
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  
  muxGet();
  for(int i = 0; i < 8; i++){ //update shitout byte from array
    if(shiftd[i] == 1){bitSet(shiftD, i);}
    if(shiftd[i] == 0){bitClear(shiftD, i);}
  }
  updateShiftRegister(); 
  
  for(int x=0;x<8;x++){
    Serial.print("Mux("+String(x)+")="+String(mux_z[x])+ "  ");
  }
  Serial.print(String(shiftD)+"  "+String(h)+"   "+String(t));
  Serial.println();
  
  delay(2000);
  
}

void muxGet(){
  digitalWrite(mux_s1, LOW); digitalWrite(mux_s2, LOW); digitalWrite(mux_s3, LOW); delay(1); mux_z[0] = analogRead(A0);
  digitalWrite(mux_s1, HIGH); digitalWrite(mux_s2, LOW); digitalWrite(mux_s3, LOW); delay(1); mux_z[4] = analogRead(A0);
  digitalWrite(mux_s1, LOW); digitalWrite(mux_s2, HIGH); digitalWrite(mux_s3, LOW); delay(1); mux_z[2] = analogRead(A0);
  digitalWrite(mux_s1, HIGH); digitalWrite(mux_s2, HIGH); digitalWrite(mux_s3, LOW); delay(1); mux_z[6] = analogRead(A0);
  digitalWrite(mux_s1, LOW); digitalWrite(mux_s2, LOW); digitalWrite(mux_s3, HIGH); delay(1); mux_z[1] = analogRead(A0);
  digitalWrite(mux_s1, HIGH); digitalWrite(mux_s2, LOW); digitalWrite(mux_s3, HIGH); delay(1); mux_z[5] = analogRead(A0);
  digitalWrite(mux_s1, LOW); digitalWrite(mux_s2, HIGH); digitalWrite(mux_s3, HIGH); delay(1); mux_z[3] = analogRead(A0);
  digitalWrite(mux_s1, HIGH); digitalWrite(mux_s2, HIGH); digitalWrite(mux_s3, HIGH); delay(1); mux_z[7] = analogRead(A0);
}

void updateShiftRegister(){
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, shiftD);
//   shiftOut(dataPin, clockPin, MSBFIRST, shiftD);
   digitalWrite(latchPin, HIGH);
}
