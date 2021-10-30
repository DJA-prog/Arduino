#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

#include <DS3231.h>
DS3231  rtc;
bool century = false;
bool h12Flag;
bool pmFlag;

int DC; //Display count
int brightness, pwm1, pwm2;
int pwm3 = 0;
bool sleep = true;
bool overRide = false;
bool shelf = false;
String IP;
String Return;

#include <SoftwareSerial.h>
#define rxPin 12
#define txPin 13
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
char data;
String input, device, value;
int val;

void lcdDisplay();

void setup() {
  lcd.init();
  lcd.backlight();
//  rtc.setHour(20);
//  rtc.setMinute(31);
//  rtc.setSecONd(0);
//  rtc.setYear(21);
//  rtc.setMONth(10);
//  rtc.setDate(12);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT); 
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  
}

void loop() {
  DC++;
  if(DC > 500){lcdDisplay();DC = 0;}

  brightness = round(analogRead(A1) / 1024.0 * 255.0);
  while(mySerial.available() > 0){
    char dataRecieve = mySerial.read();
    input += dataRecieve;
  }
  
  if(input != ""){
    device = input.substring(0, input.indexOf("="));
    Serial.print("Device: ");Serial.println(device);
    if(input.substring(input.length()-1, input.length()) == "%"){
      value = input.substring(input.indexOf("=") + 1, input.length()-1);
      val = value.toInt();
      Serial.print("Val: ");Serial.println(val);
      delay(10);
      value = "ON";
      Serial.print("iValue: ");Serial.println(value);
    }else{
      value = input.substring(input.indexOf("=") + 1, input.length());
      Serial.print("Value: ");Serial.println(value);
    }
  }
  if(device == "IP"){
    value.remove(0, value.indexOf(".", value.indexOf(".", 0) + 1));
    IP = value;
  }
  if(device == "shelf" && value == "OFF"){
    shelf = false;
  }
  if(device == "shelf" && value == "ON"){
    shelf = true;
  }
  
  if(device == "main" && value == "OFF"){
    pwm1 = 0;
  }
  if(device == "main" && value == "ON"){
    if(val != 0){pwm1 = val;}else{pwm1 = 255;}
  }
  if(device == "bed" && value == "OFF"){
    pwm2 = 0;
  }
  if(device == "bed" && value == "ON"){
    if(val != 0){pwm2 = val;}else{pwm2 = 255;}
  }
  if(device == "closet" && value == "OFF"){
    pwm3 = 0;
  }
  if(device == "closet" && value == "ON"){
    if(val != 0){pwm3 = val;}else{pwm3 = 255;}
  }
  if(device == "sleep" && value == "OFF"){
    sleep = false;
  }
  if(device == "sleep" && value == "ON"){
    sleep = true;
  }
  if(device == "overRide" && value == "OFF"){
    overRide = false;
  }
  if(device == "overRide" && value == "ON"){
    overRide = true;
  }  
  
  if(rtc.getHour(h12Flag, pmFlag) > 20 || rtc.getHour(h12Flag, pmFlag) < 6){
    if(sleep == true && analogRead(A2) > 900){
      brightness = 0;
    }
  }

  if(rtc.getHour(h12Flag, pmFlag) == 20 && rtc.getMinute() == 0){
    pwm1 = 10;
    pwm2 = 10;
    pwm3 = 10;
  }
  
  if(rtc.getHour(h12Flag, pmFlag) < 19 || rtc.getHour(h12Flag, pmFlag) > 7){
    if(overRide == false && analogRead(A3) < 800){
      pwm1 = 0;
      pwm2 = 0;
      pwm3 = 0;
      shelf = false;
    }
  }
  //mySerial.print(pwm1 + ',' + pwm2 + ',' + pwm3 + ',' + shelf);
  analogWrite(5, brightness);
  if(shelf == true){digitalWrite(8, HIGH);}else{digitalWrite(8, LOW);}
  analogWrite(9, pwm1); //main Light
  analogWrite(10, pwm2);//bed Light
  analogWrite(6, pwm3); //closet Light
  //Return = ;
  if(input != ""){
    mySerial.print(String(pwm1, DEC) + ',' + String(pwm2, DEC) + ',' + String(pwm3, DEC)  + ',' + shelf + ',' + sleep + ',' + overRide);
  }
  input = "";
  device = "";
  value = "";
  val = 0;
}
//#######################################################################
void lcdDisplay()
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("SP: ");
if(sleep == true){
  lcd.print("ON");
}else{
  lcd.print("OF");
}
lcd.setCursor(7, 0);
lcd.print("OR: ");
if(overRide == true){
  lcd.print("ON");
}else{
  lcd.print("OF");
}
lcd.setCursor(14, 0);
lcd.print("SL:");
if(shelf == true){
  lcd.print("ON");
}else{
  lcd.print("OF");
}
lcd.setCursor(0, 1);
lcd.print(IP);
lcd.setCursor(10, 1);
lcd.print(rtc.getHour(h12Flag, pmFlag), DEC);
lcd.print(':');
lcd.print(rtc.getMinute(), DEC);
lcd.print(':');
lcd.print(rtc.getSecond(), DEC);
lcd.setCursor(0, 2);
lcd.print(analogRead(A0));
lcd.setCursor(5, 2);
lcd.print(analogRead(A1));
lcd.setCursor(10, 2);
lcd.print(analogRead(A2));
lcd.setCursor(15, 2);
lcd.print(analogRead(A3));
lcd.setCursor(0, 3);
lcd.print(pwm1);
lcd.setCursor(5, 3);
lcd.print(pwm2);
lcd.setCursor(10, 3);
lcd.print(pwm3);

delay(100);

}
