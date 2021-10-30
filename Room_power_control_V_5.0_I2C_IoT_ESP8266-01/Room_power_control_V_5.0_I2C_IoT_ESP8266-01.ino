#include <ESP8266WiFi.h>

const char* ssid = "HomeADSL";//type your ssid
const char* password = "almirall";//type your password+

//const char* ssid = "Dino-j2core";//type your ssid
//const char* password = "";//type your password

WiFiServer server(80);//Service Port
String collectD = "";
String Return = "empty";
void setup() {
  Serial.begin(9600);
  delay(10);
    
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  //Serial.println("connected");
  Serial.println(200);
  server.begin();
  String ip = WiFi.localIP().toString();
  delay(10);
  Serial.println("IP="+ ip);
}

void loop() {
WiFiClient client = server.available();
if (!client) {return;}

while(!client.available()){
  delay(1);
}
  if(Serial.available() > 0){
    Return = "";
    while(Serial.available() > 0){
      char data = Serial.read();
      Return += data;
    }
  }
String request = client.readStringUntil('\r');
client.flush();

String input = request;
input.remove(0, 5);
input.remove(input.length() - 9, 9);
Serial.print(input);

  // Return the response
  /*
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<div id='data'>"+Return+"</div>");
client.println("<a href='/shelf=ON'>shelf=ON</a><br>");
client.println("<a href='/shelf=OFF'>shelf=OFF</a><hr>");

client.println("<a href='/main=8%'>main=ON</a><br>");
client.println("<a href='/main=OFF'>main=OFF</a><hr>");

client.println("<a href='/bed=15%'>bed=ON</a><br>");
client.println("<a href='/bed=OFF'>bed=OFF</a><hr>");

client.println("<a href='/closet=20%'>closet=ON</a><br>");
client.println("<a href='/closet=OFF'>closet=OFF</a><hr>");

client.println("<a href='/sleep=ON'>sleep=ON</a><br>");
client.println("<a href='/sleep=OFF'>sleep=OFF</a><hr>");

client.println("<a href='/overRide=ON'>overRide=ON</a><br>");
client.println("<a href='/overRide=OFF'>overRideOFF</a><hr>");
client.println("</html>");*/
client.println("HTTP/1.1 200 OKContent-Type: text/html\n\n<!DOCTYPE HTML>\n<html>\n<div id='data'>"+Return+"</div>\n<a href='/shelf=ON'>shelf=ON</a><br><a href='/shelf=OFF'>shelf=OFF</a><hr>\n<a href='/main=8%'>main=ON</a><br><a href='/main=OFF'>main=OFF</a><hr>\n<a href='/bed=15%'>bed=ON</a><br><a href='/bed=OFF'>bed=OFF</a><hr>\n<a href='/closet=20%'>closet=ON</a><br><a href='/closet=OFF'>closet=OFF</a><hr>\n<a href='/sleep=ON'>sleep=ON</a><br><a href='/sleep=OFF'>sleep=OFF</a><hr>\n<a href='/overRide=ON'>overRide=ON</a><br><a href='/overRide=OFF'>overRideOFF</a><hr>\n</html>");
delay(1);
}
