#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E , D4 , D5 , D6 , D7

#include <IRremote.h>
int RECV_PIN = A1;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

long unsigned int irCode;

int buttonUP = 17;
int buttonDOWN = 101;
int buttonLEFT = 42;
int buttonRIGHT = 172;
int buttonCENTER = 69;

int button1 = 0;
int button2 = 0;
int button3 = 0;
int button4 = 0;
int button5 = 0;

int screen = 1;
int screenPwm = 50;
int screenState = 1;

int portAPwm = 50;
int portAState = 0;

int portBPwm = 2;
int portBState = 0;

int portCPwm = 1;
int portCState = 0;

int pin_Out_A = 8;
int pin_Out_B = 12;
int pin_Out_C = 13;
int pin_In_Mux1 =A5;
int Mux1_State[8] = {0};

int reading1 = 0;
int reading2 = 0;
int reading3 = 0;
int reading4 = 0;
int reading5 = 0;
int reading6 = 0;
int reading7 = 0;
int reading8 = 0;

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
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(pin_Out_A, OUTPUT);
  pinMode(pin_Out_B, OUTPUT);
  pinMode(pin_Out_C, OUTPUT);
  
  digitalWrite(11, HIGH);
  delay(1000);
  Serial.begin(9600);
}

void loop() {
  updateMux1();
  irCode = 0;
  remoteControl();
  
  
////////////////////////////////////////////////////////////////////////////Control buttons
  if(analogRead(A2) == 173){//screen + 1
    button1 = 1;
    while(analogRead(A2) == 173){delay(1);}
  }
  if(analogRead(A2) == 43){//screen - 1
    button2 = 1;
    while(analogRead(A2) == 43){delay(1);}
  }
  if(analogRead(A2) == 102){//Select \/
    button3 = 1;
    while(analogRead(A2) == 102){delay(1);}
  }
  if(analogRead(A2) == 19){//Select /\
    button4 = 1;
    while(analogRead(A2) == 19){delay(1);}
  }
  if(analogRead(A2) == 69){// ON/OFF
    button5 = 1;
    while(analogRead(A2) == 69){delay(1);}
  }
///////////////////////////////////////////////////////////////////////////////Screen
  if(irCode == 0x1D2FEFF6 || button1 == 1){
    screen = screen + 1;
    if(screen == 5){screen = screen - 1;}
  }
  if(irCode == 0xE0984BB6 || button2 == 1){
    screen =screen - 1;
    if(screen < 1){screen = screen + 1;}
  }
////////////////////////////////////////////////////////////////////////////////portA PWM

  if(screen == 1){
    if(irCode == 0x143226DB || button4 == 1){
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
    
    if(irCode == 0xA32AB931 || button3 == 1){
      if(portAPwm < 10){
        portAPwm =portAPwm - 1;
      }else if(portAPwm >= 10){
        portAPwm =portAPwm - 10;
      }
      if(portAPwm < 0){
          portAPwm = portAPwm + 1;
      }
    }
    if(irCode == 0x39D41DC6 || button5 == 1){
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
    if(irCode == 0x143226DB || button4 == 1){
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
    if(irCode == 0xA32AB931 || button3 == 1){
      if(portBPwm < 10){
        portBPwm =portBPwm - 1;
      }else if(portBPwm >= 10){
        portBPwm =portBPwm - 10;
      }
      if(portBPwm < 0){
          portBPwm = portBPwm + 1;
      }
    }
    if(irCode == 0x39D41DC6 || button5 == 1){
     portBState = !portBState;
    }
    if(portBState == 1){
    analogWrite(10, portBPwm);
    }else if(portBState == 0){
    analogWrite(10, 0);
    }
  }
/*////////////////////////////////////////////////////////////////////////////////port8 PWM

  if(screen == 8){
    if(irCode == 0x143226DB || button4 == 1){
      if(portCPwm < 10){
        portCPwm =portCPwm + 1;
      }else if(portCPwm >= 10 && portCPwm < 70){
        portCPwm =portCPwm + 10;
      }else if(portCPwm >= 70){
        portCPwm =portCPwm + 30;
      }
      if(portCPwm > 255){
        portCPwm = 255;
      }
      }
    
    if(irCode == 0xA32AB931 || button3 == 1){
      if(portCPwm < 10){
        portCPwm =portCPwm - 1;
      }else if(portCPwm >= 10){
        portCPwm =portCPwm - 10;
      }
      if(portCPwm < 0){
          portCPwm = portCPwm + 1;
      }
    }
    if(irCode == 0x39D41DC6 || button5 == 1){
     portCState = !portCState;
    }
    if(portCState == 1){
    analogWrite(11, portCPwm);
    }else if(portCState == 0){
    analogWrite(11, 0);
    }
  }
*/
////////////////////////////////////////////////////////////////////////////////Back Light State
  if(screen == 4 || irCode == 0x371A3C86){
    if(irCode == 0x39D41DC6 || button5 == 1 || irCode == 0x371A3C86){
     screenState = !screenState;
    }
    if(screenState == 1){
    digitalWrite(11, HIGH);
    }else if(screenState == 0){
    digitalWrite(11, LOW);
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
/*///////////////////////////////////////////////////////////////////////////////Screen 8
  if(screen == 8){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Port C:");
    lcd.setCursor(0, 1);
    lcd.print("Strength: ");
    lcd.print(portCPwm);
    lcd.print("/255");
    lcd.setCursor(0, 2);
    lcd.print("State: ");
    if(portCState == 0){
    lcd.print("OFF");
    }else if(portCState == 1){
    lcd.print("ON");
    }
    lcd.setCursor(19, 3);
    lcd.print(screen);
  }
*/
///////////////////////////////////////////////////////////////////////////////Screen 3 (Temp & Voltage)
  if(screen == 3){
    lcd.clear();
    int sensorVal = analogRead(A0);
    float voltage = (sensorVal / 1023.0) * 5.0;
    float temperature = (voltage - .5) * 100;
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperature);
    lcd.setCursor(9, 0);
    lcd.print(" 'C");
    lcd.setCursor(0, 1);
    lcd.print("Sys-Voltage:");
    lcd.print((reading1/1023.00)*5.00*4.00 + 0.97);
    lcd.print("V");
    lcd.setCursor(0, 2);
    lcd.print("Ard-Voltage:");
    lcd.print((reading1/1023.00)*5.00*4.00 + 0.23);
    lcd.print("V");
    lcd.setCursor(19, 3);
    lcd.print(screen);
}
///////////////////////////////////////////////////////////////////////////////Screen 4 (Backlight)
  if(screen == 4){
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
if(analogRead(A4) > 1000){
     portCState = !portCState;
     while (analogRead(A4) >1000){delay(1);}
    }

button1 = 0;
button2 = 0;
button3 = 0;
button4 = 0;
button5 = 0;
delay(reading3/2);

Serial.print((reading5/1023.00)*100.00 + 0.00);//Vout
float one = ((reading5/1023.00)*100.00 + 0.00);
Serial.print(" , ");
Serial.print((reading7/1023.00)*100.00 + 0.00);//Vin
float two = ((reading7/1023.00)*100.00 + 0.00);
Serial.print(" , ");
float three = one - two;
Serial.print(three);
Serial.print(" , ");
float four = three / 0.15;
Serial.println(four);

}
void updateMux1 () {
  for (int i = 0; i < 8; i++){
    digitalWrite(pin_Out_A, HIGH && (i & B00000001));
    digitalWrite(pin_Out_B, HIGH && (i & B00000010));
    digitalWrite(pin_Out_C, HIGH && (i & B00000100));
    Mux1_State[i] = analogRead(pin_In_Mux1);
    if (i == 0){
      reading1 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 1){
      reading2 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 2){
      reading3 = Mux1_State[i];Serial.print((Mux1_State[i])/3);Serial.print(" , ");
    }if (i == 3){
      reading4 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 4){
      reading5 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 5){
      reading6 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 6){
      reading7 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 7){
      reading8 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.println("   ");
    }
  }
}
void remoteControl(){
  if (irrecv.decode(&results)){
    irCode = results.value;
    delay(50);
    irrecv.resume(); // Receive the next value
  }
}

