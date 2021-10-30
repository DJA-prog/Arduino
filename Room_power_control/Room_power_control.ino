//My arduino COM 3 Master
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E , D4 , D5 , D6 , D7

#include <Wire.h>

#include <IRremote.h>
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

long unsigned int irCode;

int button1 = 0;
int button2 = 0;
int button3 = 0;
int button4 = 0;
int button5 = 0;

int screen = 1;
int screenPwm = 50;
int screenState = 1;

int lightPwm = 1;
int lightState = 0;

int fanPwm = 1;
int fanState = 0;

int relay1State = 0;
int relay2State = 0;
int relay3State = 0;
int relay4State = 0;
int relay5State = 0;
int relay6State = 0;
int relay7State = 0;
int relay8State = 0;

int relaySelect = 0;

int relay1Transmit = 0;
int relay2Transmit = 0;
int relay3Transmit = 0;
int relay4Transmit = 0;
int relay5Transmit = 0;
int relay6Transmit = 0;
int relay7Transmit = 0;
int relay8Transmit = 0;

void setup() {
  Wire.begin(1);
  
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
  pinMode(A3, INPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(13, HIGH);
  delay(1000);
}

void loop() {
  irCode = 0;
  if (irrecv.decode(&results)){
    irCode = results.value;
    delay(50);
    irrecv.resume(); // Receive the next value
  }
////////////////////////////////////////////////////////////////////////////Control buttons
  if(analogRead(A0) > 1000){//screen + 1
    button1 = 1;
    while(analogRead(A0) > 1000){delay(1);}
  }
  if(analogRead(A1) > 1000){//screen - 1
    button2 = 1;
    while(analogRead(A1) > 1000){delay(1);}
  }
  if(analogRead(A2) >1000){//Select \/
    button3 = 1;
    while(analogRead(A2) > 1000){delay(1);}
  }
  if(analogRead(A3) > 1000){//Select /
    button4 = 1;
    while(analogRead(A3) > 1000){delay(1);}
  }
  if(digitalRead(8) == HIGH){// ON/OFF
    button5 = 1;
    while(digitalRead(8) == HIGH){delay(1);}
  }
///////////////////////////////////////////////////////////////////////////////Screen
  if(irCode == 0x1D2FEFF6 || button1 == 1){
    screen = screen + 1;
    if(screen == 8){screen = screen - 1;}
  }
  if(irCode == 0xE0984BB6 || button2 == 1){
    screen =screen - 1;
    if(screen < 1){screen = screen + 1;}
  }
////////////////////////////////////////////////////////////////////////////////Light PWM
  if(screen == 1){
    if(irCode == 0x143226DB || button4 == 1){
      if(lightPwm < 10){
        lightPwm =lightPwm + 1;
      }else if(lightPwm >= 10 && lightPwm < 70){
        lightPwm =lightPwm + 10;
      }else if(lightPwm >= 70){
        lightPwm =lightPwm + 30;
      }
      if(lightPwm > 255){
        lightPwm = 255;
      }
    }
    if(irCode == 0xA32AB931 || button3 == 1){
      if(lightPwm < 10){
        lightPwm =lightPwm - 1;
      }else if(lightPwm >= 10){
        lightPwm =lightPwm - 10;
      }
      if(lightPwm < 0){
          lightPwm = lightPwm + 1;
      }
    }
    if(irCode == 0x39D41DC6 || button5 == 1){
     lightState = !lightState;
    }
    if(lightState == 1){
    analogWrite(9, lightPwm);
    }else if(lightState == 0){
    analogWrite(9, 0);
    }
  }
////////////////////////////////////////////////////////////////////////////////Fan PWM

  if(screen == 2){
    if(irCode == 0x143226DB || button4 == 1){
      if(fanPwm < 10){
        fanPwm =fanPwm + 1;
      }else if(fanPwm >= 10 && fanPwm < 70){
        fanPwm =fanPwm + 10;
      }else if(fanPwm >= 70){
        fanPwm =fanPwm + 30;
      }
      if(fanPwm > 255){
        fanPwm = 255;
      }
      }
    
    if(irCode == 0xA32AB931 || button3 == 1){
      if(fanPwm < 10){
        fanPwm =fanPwm - 1;
      }else if(fanPwm >= 10){
        fanPwm =fanPwm - 10;
      }
      if(fanPwm < 0){
          fanPwm = fanPwm + 1;
      }
    }
    if(irCode == 0x39D41DC6 || button5 == 1){
     fanState = !fanState;
    }
    if(fanState == 1){
    analogWrite(10, fanPwm);
    }else if(fanState == 0){
    analogWrite(10, 0);
    }
  }
////////////////////////////////////////////////////////////////////////////////Relay Select
  if(irCode == 0xA32AB931 || button3 == 1){
      relaySelect = relaySelect + 1;
      if(relaySelect == 2){
        relaySelect = relaySelect - 1;
      }
    }
    if(irCode == 0x143226DB || button4 == 1){
      relaySelect = relaySelect - 1;
      if(relaySelect < 0){
        relaySelect = relaySelect + 1;
      }
    }
////////////////////////////////////////////////////////////////////////////////Relay 1-2
  if(screen == 3){
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 0){
     relay1State = !relay1State;
     Wire.beginTransmission(2);
     Wire.write(relay1State + 1);
     Wire.endTransmission();
    }
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 1){
     relay2State = !relay2State;
     Wire.beginTransmission(2);
     Wire.write(relay2State + 3);
     Wire.endTransmission();
    }
  }
////////////////////////////////////////////////////////////////////////////////Relay 3-4
  if(screen == 4){
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 0){
     relay3State = !relay3State;
     Wire.beginTransmission(2);
     Wire.write(relay3State + 5);
     Wire.endTransmission();
    }
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 1){
     relay4State = !relay4State;
     Wire.beginTransmission(2);
     Wire.write(relay4State + 7);
     Wire.endTransmission();
    }
  }
////////////////////////////////////////////////////////////////////////////////Relay 5-6
  if(screen == 5){
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 0){
     relay5State = !relay5State;
     Wire.beginTransmission(2);
     Wire.write(relay5State + 9);
     Wire.endTransmission();
    }
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 1){
     relay6State = !relay6State;
     Wire.beginTransmission(2);
     Wire.write(relay6State + 11);
     Wire.endTransmission();
    }
  }
////////////////////////////////////////////////////////////////////////////////Relay 7-8
  if(screen == 6){
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 0){
     relay7State = !relay7State;
     Wire.beginTransmission(2);
     Wire.write(relay7State + 13);
     Wire.endTransmission();
    }
    if((irCode == 0x39D41DC6 || button5 == 1) && relaySelect == 1){
     relay8State = !relay8State;
     Wire.beginTransmission(2);
     Wire.write(relay8State + 15);
     Wire.endTransmission();
    }
  }
////////////////////////////////////////////////////////////////////////////////Back Light PWM
  if(screen == 7){
    if(irCode == 0x39D41DC6 || button5 == 1){
     screenState = !screenState;
    }
    if(screenState == 1){
    digitalWrite(13, HIGH);
    }else if(screenState == 0){
    digitalWrite(13, LOW);
    }
  }
////////////////////////////////////////////////////////////////////////////////Screen 1
  if(screen == 1){
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Port A:");
    lcd.setCursor(0, 1);
    lcd.print("Strength: ");
    lcd.print(lightPwm);
    lcd.print("/255");
    lcd.setCursor(0, 2);
    lcd.print("State: ");
    if(lightState == 0){
    lcd.print("OFF");
    }else if(lightState == 1){
    lcd.print("ON");
    }
    lcd.setCursor(0, 3);
    lcd.print("Screen: ");
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 2
  if(screen == 2){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Port B:");
    lcd.setCursor(0, 1);
    lcd.print("Strength: ");
    lcd.print(fanPwm);
    lcd.print("/255");
    lcd.setCursor(0, 2);
    lcd.print("State: ");
    if(fanState == 0){
    lcd.print("OFF");
    }else if(fanState == 1){
    lcd.print("ON");
    }
    lcd.setCursor(0, 3);
    lcd.print("Screen: ");
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 3
  if(screen == 3){
    lcd.clear();
    lcd.print("Relay: 1-2");
    lcd.setCursor(0, 1);
    lcd.print("Relay 1: ");
    if(relay1State == 0){
    lcd.print("OFF");
    }else if(relay1State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 0){
      lcd.print("<");
    }
    lcd.setCursor(0, 2);
    lcd.print("Relay 2: ");
    if(relay2State == 0){
    lcd.print("OFF");
    }else if(relay2State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 1){
      lcd.print("<");
    }
    lcd.setCursor(0, 3);
    lcd.print("Screen: ");
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 4
  if(screen == 4){
    lcd.clear();
    lcd.print("Relay: 3-4");
    lcd.setCursor(0, 1);
    lcd.print("Relay 3: ");
    if(relay3State == 0){
    lcd.print("OFF");
    }else if(relay3State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 0){
      lcd.print("<");
    }
    lcd.setCursor(0, 2);
    lcd.print("Relay 4: ");
    if(relay4State == 0){
    lcd.print("OFF");
    }else if(relay4State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 1){
      lcd.print("<");
    }
    lcd.setCursor(0, 3);
    lcd.print("Screen: ");
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 5
  if(screen == 5){
    lcd.clear();
    lcd.print("Relay: 5-6");
    lcd.setCursor(0, 1);
    lcd.print("Relay 5: ");
    if(relay5State == 0){
    lcd.print("OFF");
    }else if(relay5State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 0){
      lcd.print("<");
    }
    lcd.setCursor(0, 2);
    lcd.print("Relay 6: ");
    if(relay6State == 0){
    lcd.print("OFF");
    }else if(relay6State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 1){
      lcd.print("<");
    }
    lcd.setCursor(0, 3);
    lcd.print("Screen: ");
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 6
  if(screen == 6){
    lcd.clear();
    lcd.print("Relay: 7-8");
    lcd.setCursor(0, 1);
    lcd.print("Relay 7: ");
    if(relay7State == 0){
    lcd.print("OFF");
    }else if(relay7State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 0){
      lcd.print("<");
    }
    lcd.setCursor(0, 2);
    lcd.print("Relay 8: ");
    if(relay8State == 0){
    lcd.print("OFF");
    }else if(relay8State == 1){
    lcd.print("ON");
    }
    if(relaySelect == 1){
      lcd.print("<");
    }
    lcd.setCursor(0, 3);
    lcd.print("Screen: ");
    lcd.print(screen);
  }
///////////////////////////////////////////////////////////////////////////////Screen 7
  if(screen == 7){
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
    lcd.setCursor(0, 3);
    lcd.print("Screen: ");
    lcd.print(screen);
  }

button1 = 0;
button2 = 0;
button3 = 0;
button4 = 0;
button5 = 0;
delay(100);
}
