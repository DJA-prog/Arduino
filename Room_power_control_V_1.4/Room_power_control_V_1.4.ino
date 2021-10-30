#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 4, 3, 2, 1, 0); // RS, E , D4 , D5 , D6 , D7

#include <IRremote.h>
int RECV_PIN = A2;
IRrecv irrecv(RECV_PIN);
decode_results results;
long unsigned int irCode;

float celsiustemp;
float voltage;

int screen = 1;
int screenPwm = 50;
int screenState = 1;
int backlightscreen = 8;

int portAPwm = 50;
int portAState = 0;

int portBPwm = 2;
int portBState = 0;

int portCPwm = 1;
int portCState = 0;

int Mux1_State[8] = {0};
int Mux1reading1 = 0;
int Mux1reading2 = 0;
int Mux1reading3 = 0;
int Mux1reading4 = 0;
int Mux1reading5 = 0;
int Mux1reading6 = 0;
int Mux1reading7 = 0;
int Mux1reading8 = 0;

int Pin = 0;
int MuxPWM = false;
float MuxSend = 0;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void setup() {
  lcd.begin(20, 4);
  lcd.clear();
  lcd.print("Room Power Control");
  lcd.setCursor(0, 1);
  lcd.print("Done By:");
  lcd.setCursor(0, 2);
  lcd.print("Jose' Almirall");
  irrecv.enableIRIn();

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(13,LOW);
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  delay(1000);
  lcd.clear();
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void loop() {
  updateMux1();
  updateMux2();
//  serialprint();
  irCode = 0;
  remoteControl();
  temprature();

///////////////////////////////////////////////////////////////////////////////Screen
  if(irCode == 0x1D2FEFF6){
    screen = screen + 1;
    if(screen == backlightscreen + 1){screen = screen - 1;}
  }
  if(irCode == 0xE0984BB6){
    screen =screen - 1;
    if(screen < 1){screen = screen + 1;}
  }
////////////////////////////////////////////////////////////////////////////////portA PWM

  if(screen == 1){
    if(irCode == 0x143226DB){
      if(portAPwm < 10){
        portAPwm =portAPwm + 1;
      }else if(portAPwm >= 10 && portAPwm < 70){
        portAPwm =portAPwm + 10;
      }else if(portAPwm >= 70){
        portAPwm =portAPwm + 30;
      }
      if(portAPwm > 255){
        portAPwm = 255;
      }
      }
    
    if(irCode == 0xA32AB931){
      if(portAPwm < 10){
        portAPwm =portAPwm - 1;
      }else if(portAPwm >= 10){
        portAPwm =portAPwm - 10;
      }
      if(portAPwm < 0){
          portAPwm = portAPwm + 1;
      }
    }
    if(irCode == 0x39D41DC6){
     portAState = !portAState;
    }
    if(portAState == 1){
    analogWrite(9, portAPwm);
    }else if(portAState == 0){
    analogWrite(9, 0);
    }
  }
////////////////////////////////////////////////////////////////////////////////portB PWM
  if(screen == 2){
    if(irCode == 0x143226DB){
      if(portBPwm < 10){
        portBPwm =portBPwm + 1;
      }else if(portBPwm >= 10 && portBPwm < 70){
        portBPwm =portBPwm + 10;
      }else if(portBPwm >= 70){
        portBPwm =portBPwm + 30;
      }
      if(portBPwm > 255){
        portBPwm = 255;
      }
    }
    if(irCode == 0xA32AB931){
      if(portBPwm < 10){
        portBPwm =portBPwm - 1;
      }else if(portBPwm >= 10){
        portBPwm =portBPwm - 10;
      }
      if(portBPwm < 0){
          portBPwm = portBPwm + 1;
      }
    }
    if(irCode == 0x39D41DC6){
     portBState = !portBState;
    }
    if(portBState == 1){
    analogWrite(10, portBPwm);
    }else if(portBState == 0){
    analogWrite(10, 0);
    }
  }
////////////////////////////////////////////////////////////////////////////////Mux2
if(screen == 4){
  
}
////////////////////////////////////////////////////////////////////////////////Back Light State
  if(screen == backlightscreen || irCode == 0x371A3C86){
    if(irCode == 0x39D41DC6 || irCode == 0x371A3C86){
     screenState = !screenState;
    }
    if(screenState == 1){
    digitalWrite(6, HIGH);
    }else if(screenState == 0){
    digitalWrite(6, LOW);
    }
  }
////////////////////////////////////////////////////////////////////////////////Screen 1 (Port A)
  if(screen == 1){
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Port A:");
    if(portAState == 0){
    lcd.print(" OFF");
    }else if(portAState == 1){
    lcd.print(" ON");
    }
    lcd.setCursor(0, 1);
    lcd.print("Strength: ");
    lcd.print(portAPwm);
    lcd.print("/255");
    lcd.setCursor(18, 0);
    lcd.print("<-");
    
    lcd.setCursor(0, 2);
    lcd.print("Port B:");
    if(portBState == 0){
    lcd.print("OFF");
    }else if(portBState == 1){
    lcd.print("ON");
    }
    lcd.setCursor(0, 3);
    lcd.print("Strength: ");
    lcd.print(portBPwm);
    lcd.print("/255");
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 2 (Port B)
  if(screen == 2){
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Port A:");
    if(portAState == 0){
    lcd.print(" OFF");
    }else if(portAState == 1){
    lcd.print(" ON");
    }
    lcd.setCursor(0, 1);
    lcd.print("Strength: ");
    lcd.print(portAPwm);
    lcd.print("/255");
    
    lcd.setCursor(0, 2);
    lcd.print("Port B:");
    if(portBState == 0){
    lcd.print("OFF");
    }else if(portBState == 1){
    lcd.print("ON");
    }
    lcd.setCursor(0, 3);
    lcd.print("Strength: ");
    lcd.print(portBPwm);
    lcd.print("/255");
    lcd.setCursor(18, 2);
    lcd.print("<-");
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
  ///////////////////////////////////////////////////////////////////////////////Screen 3 (Temp & Voltage)
  if(screen == 3){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(celsiustemp);
    lcd.setCursor(9, 0);
    lcd.print(" 'C");
    lcd.setCursor(0, 1);
    lcd.print("Sys-Voltage:");
    lcd.print((Mux1reading2/1023.00)*5.00*4.00 + 0.97);
    lcd.print("V");
    lcd.setCursor(0, 2);
    lcd.print("Ard-Voltage:");
    lcd.print((Mux1reading2/1023.00)*5.00*4.00 + 0.23);
    lcd.print("V");
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 4
  if(screen == 4){
    lcd.clear();
    lcd.setCursor(0, 0);
    for (int i = 0; i < 8; i++){
     if (i = 0){lcd.setCursor(0, 0);lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading1);lcd.print("   ");}
     if (i = 1){lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading2);}
     if (i = 2){lcd.setCursor(0, 1);lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading3);lcd.print("   ");}
     if (i = 3){lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading4);}
     if (i = 4){lcd.setCursor(0, 2);lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading5);lcd.print("   ");}
     if (i = 5){lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading6);}
     if (i = 6){lcd.setCursor(0, 3);lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading7);lcd.print("   ");}
     if (i = 7){lcd.print(i + 1);lcd.print(": ");lcd.print(Mux1reading8);}
    lcd.setCursor(19, 3);
    lcd.print(screen);
    }
  }
///////////////////////////////////////////////////////////////////////////////Screen backlightscreen (Backlight)
  if(screen == backlightscreen){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Back Light:");
    lcd.setCursor(0, 1);
    lcd.print("State: ");
    if(screenState == 0){
    lcd.print("OFF");
    }else if(screenState == 1){
    lcd.print("ON");
    }
    lcd.setCursor(19, 3);
    lcd.print(screen);
}
  delay(60);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void updateMux1() {
  digitalWrite(8, HIGH);  //Mux1 R
  delay(2);               //Mux1 R
  digitalWrite(8, LOW);   //Mux1 R
  delay(2);               //Mux1 R
  for (int i = 0; i < 8; i++){
    Mux1_State[i] = analogRead(A0);
    if (i == 0){
      Mux1reading1 = Mux1_State[i];
    }if (i == 1){
      Mux1reading2 = Mux1_State[i];
    }if (i == 2){
      Mux1reading3 = Mux1_State[i];
    }if (i == 3){
      Mux1reading4 = Mux1_State[i];
    }if (i == 4){
      Mux1reading5 = Mux1_State[i];
    }if (i == 5){
      Mux1reading6 = Mux1_State[i];
    }if (i == 6){
      Mux1reading7 = Mux1_State[i];
    }if (i == 7){
      Mux1reading8 = Mux1_State[i];
    }
    digitalWrite(7,HIGH); //Mux1 C
    delay(1);             //Mux1 C
    digitalWrite(7,LOW);  //Mux1 C
    delay(1);
  }
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void updateMux2() {
  digitalWrite(13, HIGH);  //Mux2 R
  delay(2);                //Mux2 R
  digitalWrite(13, LOW);   //Mux2 R
  delay(2);                //Mux2 R
  for (int i = 0; i < Pin; i++){
    digitalWrite(12,HIGH);  //Mux2 C
    delay(1);               //Mux2 C
    digitalWrite(12,LOW);   //Mux2 C
    delay(1);               //Mux2 C
  }
  if(MuxPWM == true){
    analogWrite(11, MuxSend);
  }else{
   digitalWrite(11, MuxSend); 
  }
  
}
/*//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void serialprint() {
  Serial.print("MUX1: ");
  Serial.print(Mux1reading1);Serial.print(" , ");
  Serial.print(Mux1reading2);Serial.print(" , ");
  Serial.print(Mux1reading3);Serial.print(" , ");
  Serial.print(Mux1reading4);Serial.print(" , ");
  Serial.print(Mux1reading5);Serial.print(" , ");
  Serial.print(Mux1reading6);Serial.print(" , ");
  Serial.print(Mux1reading7);Serial.print(" , ");
  Serial.print(Mux1reading8);Serial.println(" ");
  Serial.print("MUX2: ");
  Serial.print(Mux2reading1);Serial.print(" , ");
  Serial.print(Mux2reading2);Serial.print(" , ");
  Serial.print(Mux2reading3);Serial.print(" , ");
  Serial.print(Mux2reading4);Serial.print(" , ");
  Serial.print(Mux2reading5);Serial.print(" , ");
  Serial.print(Mux2reading6);Serial.print(" , ");
  Serial.print(Mux2reading7);Serial.print(" , ");
  Serial.print(Mux2reading8);Serial.println(" ");
  Serial.print("Tempreture: ");Serial.println(celsiustemp);
  
}
*/
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void remoteControl(){
  if (irrecv.decode(&results)){
    irCode = results.value;
    delay(50);
    irrecv.resume(); // Receive the next value
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void temprature(){
  voltage = Mux1reading1;
  float volts = voltage/205.0;
  celsiustemp = 100.0 * volts - 50;
}

