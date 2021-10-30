#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); // RS, E , D4 , D5 , D6 , D7
bool inRange(int val, int minimum, int maximum){return ((minimum <= val) && (val <= maximum));}

#include <IRremote.h>
int RECV_PIN = A3;
IRrecv irrecv(RECV_PIN);
decode_results results;
long unsigned int irCode;
long unsigned int irCodeOld;

int SL = 0;
int ML = 0;
int Cs = 0;
int BL = 0;
int OL = 0;
int Check;

void setup() {
  lcd.begin(20, 4);
  Serial.begin(9600);
  pinMode(2, OUTPUT);//shelf
  pinMode(3, OUTPUT);//5V light
  pinMode(4, OUTPUT);//Cooler
  pinMode(5, OUTPUT);//Bed light
  pinMode(7, OUTPUT);//Out Light
  irrecv.enableIRIn();
  int C = analogRead(A0);
  if(inRange(C, 250, 258)){Cs = 1;}
  if(inRange(C, 220, 230)){Cs = 0;}
  if(C > 258){Cs = 1;}
}

void loop() {
  remoteControl();
  int C = analogRead(A0);
  int A = analogRead(A1);
  int B = analogRead(A2);
 Check++;
 if(C > 246){Cs = 1;}
 
 if(Check > 2000.00 && Cs == 1){
  Cs = 0;digitalWrite(4, Cs);
  delay(2000);
  int C = analogRead(A0);
  lcd.setCursor(15, 0);
  lcd.print(C);
  delay(1000);
  Cs = 1;digitalWrite(4, Cs);
  if(C < 220){Cs = 0;}
  Check = 0;
  Serial.print("test: ");Serial.print(C);Serial.print(" > ");
  }
  if(Check > 2200){Check = 0;}
  
  if(inRange(B, 1020, 1024)){SL = !SL;}
  if(inRange(A, 928, 932)){BL = 200;ML = 250;SL = 1;}
  if(inRange(A, 836, 840)){BL = 0;ML = 0;SL = 0;}
  if(inRange(A, 1020, 1024)){BL++; if(BL > 255){BL--;}}
  if(inRange(A, 740, 748)){BL--; if(BL < 0){BL++;}}
  if(inRange(A, 910, 914)){ML++; if(ML > 255){ML--;}}
  if(inRange(A, 804, 808)){ML--; if(ML < 0){ML++;}}

/*  if(irCodeOld == irCode){
    if(irCode == 0xA32AB931){delay(200);irCode = 0;}
    if(irCode == 0x371A3C86){delay(200);irCode = 0;}
    if(irCode == 0x39D41DC6){delay(200);}
    
  }
*/
  //if(irCode == 0x1D2FEFF6){ML = ML + 10; if(ML > 255){ML = 255;}}
  if(irCode == 0x1D2FEFF6){BL = BL + 10; if(BL > 255){BL = 255;}}
  if(irCode == 0xE0984BB6){BL++; if(BL > 255){BL = 255;}}
  if(irCode == 0x143226DB){ML = 0;BL = 0;SL = 0;OL = 0;}
  if(irCode == 0xA32AB931){Check = 8980;Cs = !Cs;}
  if(irCode == 0x371A3C86){SL = !SL;}
  if(irCode == 0x39D41DC6){OL = !OL;}

  analogWrite(3, ML);
  analogWrite(5, BL);
  digitalWrite(2, SL);
  digitalWrite(4, Cs);
  digitalWrite(7, OL);

  lcd. clear();
  lcd.print (C);
  lcd.print (" ; ");
  lcd.print (Check);
  lcd.setCursor(0, 1);
  lcd.print("Main Light: ");
  lcd.print(ML / 255.00 * 100.00);
  lcd.print("%");
  lcd.setCursor(0, 2);
  lcd.print("Bed Light: ");
  lcd.print(BL / 255.00 * 100.00);
  lcd.print("%");
  lcd.setCursor(0, 3);
  lcd.print("Cs");
  lcd.print(digitalRead(4));
  lcd.print(" ; ");
  lcd.print(irCode, HEX);
  lcd.setCursor(19, 3);
  lcd.print(OL);


delay(100);

Serial.print("A:");
Serial.print(A);
Serial.print(" : ");
Serial.print("B:");
Serial.print(B);
Serial.print(" : ");
Serial.print("C:");
Serial.print(C);
Serial.print(" : ");
Serial.print("SL:");
Serial.print(SL);
Serial.print(" : ");
Serial.print("ML:");
Serial.print(ML);
Serial.print(" : ");
Serial.print("Cs:");
Serial.print(Cs);
Serial.print(" : ");
Serial.print("BL:");
Serial.print(BL);
Serial.print(" : ");
Serial.print("OL:");
Serial.print(OL);
Serial.print(" : ");
Serial.print("Check:");
Serial.print(Check);
Serial.print(" : ");
Serial.print("IR:");
Serial.println(irCode, HEX);
irCodeOld = irCode;
irCode = 0;
}
void remoteControl(){
  if (irrecv.decode(&results)){
    irCode = results.value;
    delay(50);
    irrecv.resume(); // Receive the next value
  }
}
