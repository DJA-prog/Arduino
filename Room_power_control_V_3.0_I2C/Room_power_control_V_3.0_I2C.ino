#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
bool inRange(int val, int minimum, int maximum){return ((minimum <= val) && (val <= maximum));}

#include <IRremote.h>
int RECV_PIN = A3;
IRrecv irrecv (RECV_PIN);
decode_results results;
long unsigned int irCode;

unsigned long time;
unsigned long old;
unsigned long oldt;

int def = 0;
int SL = 0; // SHELF LIGHT
int ML = 0; // MAIN LIGHT
int CS = 1; //COOLER STATE PERMINANT SW
int CF = 0; // COOLER STATE
int BL = 0; // BED LIGHT
int CK = 0; // CHECK
int CKI = 59.0; // CHECK INTERVAL
int CT = 0; // COOLER TEMP
int CTO = 0; // COOLER TEMP OLD
int MIN = 220; //COOLER MIN 220
int MAX = 246; //COOLER MAX 246
int DEF = 26; //COOLER DEF
int A = 0;
int B = 0;
int C = 0; //COOLER READING 21'C @ 266; 20.5'C @ 263 
int H = 0; //HOUR
int M = 0; //MIN
int S = 0; //SECONDS
int screen = 1; //SCREEN COUNT 7
int power = 0; /*0=MAINS 1=SOLAR 2=BOTH*/
int SC = 0; //SCELECT
int DC = 0; //DISPLAY COUNT
int door = 0; /*0 = open; 1 = close;*/
int alarm = 0;
const int buzzer = 6; //buzzer to arduino pin 6
float cycleRate = 0;
float CC = 0; //CYCLE CHECK
//#######################################################################
void setup(){
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(2, OUTPUT);//SHELF LIGHT
  pinMode(3, OUTPUT);//MAIN LIGHT
  pinMode(4, OUTPUT);//COOLER
  pinMode(5, OUTPUT);//BED LIGHT
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 6 as an output
  pinMode(7, OUTPUT);//
  S = EEPROM.read(0);
  M = EEPROM.read(1);
  H = EEPROM.read(2);
  CS = EEPROM.read(3);
  if(CS > 1 || CS < 0){
    CS = 1;
    EEPROM.write(3, CS);
  }
  
}
//#######################################################################
void loop(){
  DC++;
  if(DC > 100){
    lcdDisplay();
    DC = 0;
    Serial.println("analogRead(A4)");
  }
  // serialDisplay();
  C = analogRead(A0); //cooler reading
  A = analogRead(A1);
  B = analogRead(A2);
  if(analogRead(A0) > 50){
    door = 1;
  }else{
    door = 0;
  }
  if(alarm == 1 && door == 0){
    analogWrite(buzzer, 1000);
  }else{
    analogWrite(buzzer, 0);
  }
  EEPROM.write(3, CS);

  time = millis();
  if((time - oldt) > 499){
    oldt = oldt + 500;
    remoteControl();
    
    if(inRange(B, 1020, 1024)){
      SL = !SL;
    }
    if(inRange(A, 928, 932)){
      BL = 200;
      ML = 200;
      SL = 1;
    }
    if(inRange(A, 836, 840)){
      BL = 0;
      ML = 0;
      SL = 0;
    }
    if(inRange(A, 1020, 1024)){
    if(BL < 11){BL++;
    }else{BL = BL + 10;}
      if(BL > 255){BL = 255;}
    }
    if(inRange(A, 740, 748)){
    if(BL < 9){BL--;
    }else{BL = BL - 10;}
      if(BL < 0){BL = 0;}
    }
    if(inRange(A, 910, 914)){
      if(ML < 11){ML++;
      }else{ML = ML + 10;}
      if(ML > 255){ML = 255;}
    }
    if(inRange(A, 804, 808)){
      if(ML < 9){ML--;
      }else{ML = ML - 10;}
      if(ML < 0){ML = 0;}
    }
  }
  
  if(time == 0){
    S = 0;
    old = 0;
  }
  if((time - old) > 999.00){
    cycleRate = CC;
    old = old + 1000.00;
    def = time - old;
    if(def > 999){
      def = def - 1000;
      S++;
    }
    CK++;
    S++;
    if(S > 59){
      M++; S = 0;
    }
    if(M > 59){
      H++; M = 0;
    }
    if(H > 23){
      H = 0;
    }
      EEPROM.write(0, S);
      EEPROM.write(1, M);
      EEPROM.write(2, H);
      CC = 0.00;
  }
  CC++;
 
  if(CS == 1){
    if(CK > CKI && CF == 1){
      CK = 0;
      CF = 0;
    }
    if(CK > 2 && CF == 0){
      CK = 0;
      C = analogRead(A0);
      CT = C;
      CTO = C;
      if(C > MAX){
        CF = 1;
      }else if(C < MIN){
        CF = 0;
      }
    }
  }else{
    CK = 0;
  }
  if(CK > (CKI+(CK/5.0))){CK = 0;}

  
  
  if(screen == 3 && irCode == 0x39D41DC6){screen = 5;irCode = 0;} //screen 3(4) to screen 5(6)
  if(screen == 2 && irCode == 0x39D41DC6){screen = 6;irCode = 0;} //screen 2 to screen 6(7)
  if(screen == 5){                        //screen 5(6)
    if(irCode == 0x371A3C86){screen = 3; irCode = 0;}//back to screen 3(4)
    if(irCode == 0x39D41DC6){CS = !CS;}
    if(irCode == 0xE0984BB6){SC--;if(SC < 0){SC = 0;}}
    if(irCode == 0x1D2FEFF6){SC++;if(SC > 2){SC = 2;}}
    if(SC == 0){
      if(irCode == 0x143226DB){CKI = CKI + 50;}
      if(irCode == 0xA32AB931){CKI = CKI - 50;if(CKI < 0){CKI = 0;}}
    }
    if(SC == 1){
      if(irCode == 0x143226DB){MIN++;}
      if(irCode == 0xA32AB931){MIN--;}
    }
    if(SC == 2){
      if(irCode == 0x143226DB){DEF++;}
      if(irCode == 0xA32AB931){DEF--;}
    }
    
  }else
  
  if(screen == 6){                        //screen 6(7)
    if(irCode == 0x371A3C86){screen = 2;irCode = 0;} //back to screen 2
    if(irCode == 0xE0984BB6){SC--;if(SC < 0){SC = 0;}}
    if(irCode == 0x1D2FEFF6){SC++;if(SC > 2){SC = 2;}}
    if(SC == 0){
      if(irCode == 0x143226DB){S++;}
      if(irCode == 0xA32AB931){S--;}
    }
    if(SC == 1){
      if(irCode == 0x143226DB){M++;}
      if(irCode == 0xA32AB931){M--;}
    }
    if(SC == 2){
      if(irCode == 0x143226DB){H++;}
      if(irCode == 0xA32AB931){H--;}
    }
    
  }
  else{
    if(irCode == 0x1D2FEFF6){
      screen++; if(screen > 4){screen--;}
    }
    if(irCode == 0xE0984BB6){
      screen--; if(screen < 1){screen++;}
    }
  }
  if(screen == 3){                        //screen 3(4)
    if(irCode == 0x371A3C86){alarm = !alarm;}
  }
  if(screen == 1){                        //screen 1
    if(irCode == 0x143226DB){if(ML < 11){ML++;}else{ML = ML + 10;}if(ML > 255){ML = 255;}}
    if(irCode == 0xA32AB931){if(ML < 11){ML--;}else{ML = ML - 10;}if(ML < 0){ML = 0;}}
    if(irCode == 0x371A3C86){if(BL < 11){BL++;}else{BL = BL + 10;}if(BL > 255){BL = 255;}}
    if(irCode == 0x39D41DC6){if(BL < 11){BL--;}else{BL = BL - 10;}if(BL < 0){BL = 0;}}
  }
  MAX = MIN + DEF;
  if(CS == 0){CF = 0;}
  analogWrite(3, ML);
  analogWrite(5, BL);
  digitalWrite(2, SL);
  digitalWrite(4, CF);
  
  irCode = 0;
}
//#######################################################################
void remoteControl(){
  if(irrecv.decode(&results)){
    irCode = results.value;
    irrecv.resume();
  }
}
//#######################################################################
void lcdDisplay(){
  if(screen == 1){
    lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MAIN LIGHT: ");
    lcd.print(ML/255.0*100.0);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("BED LIGHT: ");
    lcd.print(BL/255.0*100.0);
    lcd.print("%");
    lcd.setCursor(0, 2);
    lcd.print("Alarm: ");
    if(alarm == 0){lcd.print("OFF");}else{lcd.print("ON");}
    lcd.setCursor(0, 3);
    lcd.print("COOLER: ");
    if(CF == 0){lcd.print("OFF");}else{lcd.print("ON");}
    lcd.setCursor(13, 3);
    if(power == 0){lcd.print("MAINS");}
    if(power == 1){lcd.print("SOLAR");}
    if(power == 2){lcd.print("BOTH");}
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
  if(screen == 2){
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("TIME: ");
    lcd.print(H);
    lcd.print(":");
    lcd.print(M);
    lcd.print(":");
    lcd.print(S);
    lcd.setCursor(2, 2);
    lcd.print("COOLER: ");
    lcd.print(C);
    lcd.setCursor(0, 3);
    lcd.print("Cycles/Sec:");
    lcd.print(cycleRate);
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
  if(screen == 0){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAIN LIGHT:");
    lcd.setCursor(0, 1);
    lcd.print("BRIGHTNESS: ");
    lcd.print(ML/255.0*100.0);
    lcd.print("%");
    lcd.setCursor(0, 2);
    lcd.print("BED LIGHT:");
    lcd.setCursor(0, 3);
    lcd.print("BRIGHTNESS: ");
    lcd.print(BL/255.0*100.0);
    lcd.print("%");
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
  if(screen == 3){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alarm: ");
    if(alarm == 0){lcd.print("OFF");}else{lcd.print("ON");}
    lcd.setCursor(0, 1);
    lcd.print("COOLER: ");
    if(CS == 0){lcd.print("OFF");}
    else{lcd.print("ON");}
    lcd.setCursor(0, 2);
    lcd.print("COOLER FAN: ");
    if(CF == 0){lcd.print("OFF");}
    else{lcd.print("ON");}
    lcd.setCursor(0, 3);
    lcd.print("TEMP: ");
    lcd.print(C);
    lcd.setCursor(10, 3);
    if(CF == 1){
    lcd.print("CTO: ");
    lcd.print(CTO);
    }
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
  if(screen == 5){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("COOLER: ");
    if(CS == 0){lcd.print("OFF");}else{lcd.print("ON");}
    lcd.setCursor(0, 1);
    lcd.print("CKI: ");
    lcd.print(CKI);
    if(SC == 0){lcd.print("<");}
    lcd.setCursor(0, 2);
    lcd.print("MIN: ");
    lcd.print(MIN);
    if(SC == 1){lcd.print("<");}
    lcd.setCursor(0, 3);
    lcd.print("MAX: ");
    lcd.print(MAX);
    lcd.setCursor(10, 2);
    lcd.print("DEF: ");
    lcd.print(DEF);
    if(SC == 2){lcd.print("<");}
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
  if(screen == 6){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TIME: ");
    lcd.setCursor(0, 1);
    lcd.print("SCCONDS: ");
    lcd.print(S);
    if(SC == 0){lcd.print("<");}
    lcd.setCursor(0, 2);
    lcd.print("MINUTES: ");
    lcd.print(M);
    if(SC == 1){lcd.print("<");}
    lcd.setCursor(0, 3);
    lcd.print("HOURS: ");
    lcd.print(H);
    if(SC == 2){lcd.print("<");}
  }
  if(screen == 4){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DEBUG: CT: ");
    lcd.print(CTO);
    lcd.setCursor(11, 0);
    lcd.print(CTO);
    lcd.print(" ");
    lcd.print(CK);
    lcd.print(" ");
    lcd.print(CS);
    lcd.setCursor(0, 1);
    lcd.print("ML: ");
    lcd.print(ML);
    lcd.setCursor(10, 1);
    lcd.print("BL: ");
    lcd.print(BL);
    lcd.setCursor(0, 2);
    lcd.print("SL: ");
    lcd.print(SL);
    lcd.setCursor(10, 2);
    lcd.print("CF: ");
    lcd.print(CF);
    lcd.setCursor(0, 3);
    lcd.print("Alarm: ");
    lcd.print(alarm);
    lcd.print(":");
    lcd.print(door);
    lcd.setCursor(10, 3);
    if(power == 0){lcd.print("MAINS");}
    if(power == 1){lcd.print("SOLAR");}
    if(power == 2){lcd.print("BOTH");}
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
}
