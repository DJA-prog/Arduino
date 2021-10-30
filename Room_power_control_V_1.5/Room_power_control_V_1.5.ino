#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E , D4 , D5 , D6 , D7

const unsigned long lcdTimeInterval = 1000;
unsigned long previousTime = 0;

#include <IRremote.h>
int RECV_PIN = A2;
IRrecv irrecv(RECV_PIN);
decode_results results;
long unsigned int irCode;
float celsiustemp;
float voltage;
int Screen = 1;
int ScreenState = 1;
int screenPwm = 50;
int portAPwm = 50;
int portAState = 0;
int portBPwm = 2;
int portBState = 0;

int backlightScreen = 6;
int mux3multiplier = 4;
int mux3state = 0;
int mux3set = 0;
int mux3delay = 1024;
int mux3pin = 0;
float mux3OUT = 0;
int Mux1_State[8] = {0};
int Mux1reading1 = 0;
int Mux1reading2 = 0;
int Mux1reading3 = 0;
int Mux1reading4 = 0;
int Mux1reading5 = 0;
int Mux1reading6 = 0;
int Mux1reading7 = 0;
int Mux1reading8 = 0;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void setup() {
  lcd.begin(20, 4);
  lcd.clear();
  irrecv.enableIRIn();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, HIGH); //A
  digitalWrite(13, LOW); //B
  digitalWrite(8, HIGH);
  delay(2);
  digitalWrite(8, LOW);
  digitalWrite(12, HIGH); //A
  digitalWrite(13, HIGH); //B
  digitalWrite(8, HIGH);
  delay(2);
  digitalWrite(8, LOW);
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void loop() {
  unsigned long currentTime = millis();
  if((currentTime - previousTime) >= lcdTimeInterval){
    previousTime = currentTime;
    lcdscreen();
    temprature();
  }
  mux2();
  mux3();
  remoteControl();
  if(irCode == 0x1D2FEFF6){
    Screen = Screen + 1;
    if(Screen == backlightScreen + 1){Screen = Screen - 1;}
  }
  if(irCode == 0xE0984BB6){
    Screen = Screen - 1;
    if(Screen < 1){Screen = Screen + 1;}
  }
  if (Mux1reading5 > 1000 && Mux1reading6 == 0){
    Screen = 1;
  }
  if (Mux1reading5 == 0 && Mux1reading6 > 1000){
    Screen = 2;
  }
  if (Mux1reading5 > 1000 && Mux1reading6 > 1000){
    Screen = 3;
  }
  if (Mux1reading7 > 1000 && Mux1reading8 == 0){
    Screen = 4;
  }
  if (Mux1reading7 == 0 && Mux1reading8 > 1000){
    Screen = 5;
  }
  if (Mux1reading7 > 1000 && Mux1reading8 > 1000){
    Screen = 6;
  }
////////////////////////////////////////////////portA PWM
  if(Screen == 1){
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
///////////////////////////////////////////portB PWM
  if(Screen == 2){
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
///////////////////////////////////////////////MUX3 Screen 5
if (Screen == 5){
  if(irCode == 0x39D41DC6){
     mux3state = !mux3state;
    }
  if(mux3state == 1){
    if(irCode == 0x143226DB){
      mux3set = mux3set + 1;
      if (mux3set > 3){mux3set = mux3set - 1;}
    }if(irCode == 0xA32AB931){
      mux3set = mux3set - 1;
      if (mux3set < 0){mux3set = mux3set + 1;}
    }
    if (mux3set == 0){
      if(irCode == 0x371A3C86){
        if(mux3OUT < 100.00){
          mux3OUT = mux3OUT + 1024.00;
        }else{
          mux3OUT = 0.00;
        }
      }
    }if (mux3set == 1){
      mux3delay = Mux1reading4;
      if(Mux1reading8 > 1000 && 0x143226DB){
        mux3multiplier = mux3multiplier + 1;
        if(mux3multiplier > 10){mux3multiplier = mux3multiplier -1;}
      }if(Mux1reading8 > 1000 && 0xA32AB931){
        mux3multiplier = mux3multiplier - 1;
        if(mux3multiplier < 1){mux3multiplier = mux3multiplier + 1;}
      }
    }if (mux3set == 2){
      mux3OUT = Mux1reading4;
    
      if(Mux1reading8 > 1000 && 0x143226DB){
        mux3pin = mux3pin + 1;
        if(mux3pin > 7){mux3pin = mux3pin -1;}
      }if(Mux1reading8 > 1000 && 0xA32AB931){
        mux3pin = mux3pin - 1;
        if(mux3pin < 0){mux3pin = mux3pin + 1;}
      } 
    }
  }
}
///////////////////////////////////////////////Back Light State
  if(Screen == backlightScreen || irCode == 0x371A3C86){
    if(irCode == 0x39D41DC6 || irCode == 0x371A3C86){
     ScreenState = !ScreenState;
    }
    if(ScreenState == 1){
    digitalWrite(0, HIGH);
    }else if(ScreenState == 0){
    digitalWrite(0, LOW);
    }
  } 
  irCode = 0; 
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void lcdscreen(){

  //////////////////////////////////////////////////Screen 1 (Port A)
  if(Screen == 1){
    
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
    lcd.print(" OFF");
    }else if(portBState == 1){
    lcd.print(" ON");
    }
    lcd.setCursor(0, 3);
    lcd.print("Strength: ");
    lcd.print(portBPwm);
    lcd.print("/255");
    lcd.setCursor(19, 3);
    lcd.print(Screen);
  }
//////////////////////////////////////////////////////Screen 2 (Port B)
  if(Screen == 2){
    
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
    lcd.print(" OFF");
    }else if(portBState == 1){
    lcd.print(" ON");
    }
    lcd.setCursor(0, 3);
    lcd.print("Strength: ");
    lcd.print(portBPwm);
    lcd.print("/255");
    lcd.setCursor(18, 2);
    lcd.print("<-");
    lcd.setCursor(19, 3);
    lcd.print(Screen);
  }
  //////////////////////////////////////////////////Screen 3 (Temp & Voltage)
  if(Screen == 3){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(celsiustemp);
    lcd.setCursor(9, 0);
    lcd.print(" 'C");
    lcd.setCursor(0, 1);
    lcd.print("Sys-Voltage:");
    lcd.print((Mux1reading2/1022.00)*5.00*4.00 + 0.97);
    lcd.print("V");
    lcd.setCursor(0, 2);
    lcd.print("Ard-Voltage:");
    lcd.print((Mux1reading2/1022.00)*5.00*4.00 + 0.23);
    lcd.print("V");
    lcd.setCursor(19, 3);
    lcd.print(Screen);
  }
///////////////////////////////////////////////////Screen 4
  if(Screen == 4){
      lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1: ");lcd.print(Mux1reading1);
  lcd.setCursor(0,1);
  lcd.print("2: ");lcd.print(Mux1reading2);
  lcd.setCursor(0,2);
  lcd.print("3: ");lcd.print(Mux1reading3);
  lcd.setCursor(0,3);
  lcd.print("4: ");lcd.print(Mux1reading4);
  lcd.setCursor(10,0);
  lcd.print("5: ");lcd.print(Mux1reading5);
  lcd.setCursor(10,1);
  lcd.print("6: ");lcd.print(Mux1reading6);
  lcd.setCursor(10,2);
  lcd.print("7: ");lcd.print(Mux1reading7);
  lcd.setCursor(10,3);
  lcd.print("8: ");lcd.print(Mux1reading8);
  lcd.setCursor(19, 3);
  lcd.print(Screen);
  }
//////////////////////////////////////////////
if(Screen == 5){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MUX3 OUT: ");
  if(mux3state == 1){
    lcd.print("ON ");
    lcd.print("PIN: ");
    lcd.print(mux3pin);
    lcd.setCursor(0, 1);
  lcd.print("Setting: ");
  if (mux3set == 0){
    lcd.print("SetState");
    lcd.setCursor(0, 2);
    lcd.print("Set: ");
    lcd.print(mux3OUT);
  }if (mux3set == 1){
    lcd.print("Pulsing");
    lcd.setCursor(0, 2);
    lcd.print("Delay Interval: ");
    lcd.print(mux3delay);
    lcd.setCursor(0, 3);
    lcd.print("Multiplier: ");
    lcd.print(mux3multiplier);
  }if (mux3set == 2){
    lcd.print("PWM:");
    lcd.setCursor(0, 2);
    lcd.print("PWM: ");
    lcd.print(mux3OUT);
  }if (mux3set == 3){
    lcd.print("PIN");
    lcd.setCursor(0, 2);
    lcd.print("Pin: ");
    lcd.print(mux3pin);
  }
  }else{
    lcd.print("OFF");
  }
  
  lcd.setCursor(19, 3);
  lcd.print(Screen);
  }
//////////////////////////////////////////////Screen backlightScreen (Backlight)
  if(Screen == backlightScreen){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Back Light:");
    lcd.setCursor(0, 1);
    lcd.print("State: ");
    if(ScreenState == 0){
    lcd.print("OFF");
    }else if(ScreenState == 1){
    lcd.print("ON");
    }
    lcd.setCursor(19, 3);
    lcd.print(Screen);
}

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void mux2() {
  digitalWrite(12, HIGH); //A
  digitalWrite(13, LOW); //B
  digitalWrite(8, HIGH);
  delay(2);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW); //A
  digitalWrite(13, LOW); //B

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
    digitalWrite(8,HIGH); //Mux2 C
    delay(1);             //Mux2 C
    digitalWrite(8,LOW);  //Mux2 C
    delay(1);
  }
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void mux3() {
  digitalWrite(12, HIGH); //A
  digitalWrite(13, HIGH); //B
  digitalWrite(8, HIGH);
  delay(1);
  digitalWrite(8, LOW);
  delay(1);
  digitalWrite(12, LOW);
  if(mux3pin > 0){
    for (int i = 0; i < mux3pin; i++){
    digitalWrite(8, HIGH);
    delay(2);
    digitalWrite(8, LOW);
   }
  }
  if(mux3state == 1){
    if (mux3set == 0){
      digitalWrite(11, mux3OUT);
    }
    if (mux3set == 1){
      digitalWrite(11, HIGH);
      delay(mux3delay);
      digitalWrite(11, LOW);
      delay(mux3delay);
    }
    if (mux3set == 2){
    analogWrite(11, mux3OUT);
    }
  }
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void remoteControl(){
  if (irrecv.decode(&results)){
    irCode = results.value;
    delay(50);
    irrecv.resume(); // Receive the next value
  }
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void temprature(){
  voltage = Mux1reading1;
  float volts = voltage/205.0;
  celsiustemp = 100.0 * volts - 50;
}
