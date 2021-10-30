#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

#include <IRremote.h>
int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
int irCode;
int oldIrCode;

#include <DS3231.h>
DS3231  rtc;
bool century = false;
bool h12Flag;
bool pmFlag;

int DC, RC; //Display count
int brightness, pwm1, pwm2;
int pwm3 = 10;
bool sleep = true;
bool overRide = false;
bool shelf = false;

void remoteControl();
void lcdDisplay();

void setup() {
  lcd.init();
  lcd.backlight();
//  rtc.setHour(20);
//  rtc.setMinute(31);
//  rtc.setSecond(0);
//  rtc.setYear(21);
//  rtc.setMonth(10);
//  rtc.setDate(12);
  irrecv.enableIRIn();
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
  RC++;
  if(RC > 200){remoteControl();}
  brightness = round(analogRead(A1) / 1024.0 * 255.0);
  if(irCode == 0xFFFFFFFF){
    irCode = oldIrCode;
  }
  switch(irCode){
    case 0xFFFFA25D:
      sleep = !sleep;
      if(sleep == true){
        pwm1 = 0;
        pwm2 = 0;
        pwm3 = 0;
      }
      break;
    case 0x622:
      overRide = !overRide;
      break;
    case 0x601:
      if(pwm1 < 11){pwm1++;}else{pwm1 += 10;}
      if(pwm1 > 255){pwm1 = 255;}
      break;
    case 0x604:
      pwm1 = 0;
      break;
    case 0x607:
      if(pwm1 < 11){pwm1--;}else{pwm1 -= 10;}
      if(pwm1 < 0){pwm1 = 0;}
      break;

    case 0x602:
      if(pwm2 < 11){pwm2++;}else{pwm2 += 10;}
      if(pwm2 > 255){pwm2 = 255;}
      break;
    case 0x605:
      pwm2 = 0;
      break;
    case 0x608:
      if(pwm2 < 11){pwm2--;}else{pwm2 -= 10;}
      if(pwm2 < 0){pwm2 = 0;}
      break;

    case 0x603:
      if(pwm3 < 11){pwm3++;}else{pwm3 += 10;}
      if(pwm3 > 255){pwm3 = 255;}
      break;
    case 0x606:
      pwm3 = 0;
      break;
    case 0x609:
      if(pwm3 < 11){pwm3--;}else{pwm3 -= 10;}
      if(pwm3 < 0){pwm3 = 0;}
      break;

    case 0x624:
      shelf = !shelf;
      break;
  }
  if(irCode != 0xFFFFFFFF && irCode != 0){
    oldIrCode = irCode;
  }
  irCode = 0;
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
  analogWrite(5, brightness);
  if(shelf == true){digitalWrite(8, HIGH);}else{digitalWrite(8, LOW);}
  analogWrite(9, pwm1);
  analogWrite(10, pwm2);
  analogWrite(6, pwm3);
}
//#######################################################################
void remoteControl()
{
  if (irrecv.decode(&results))
  {
    irCode = results.value;
    irrecv.resume();
  }
}
//#######################################################################
void lcdDisplay()
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Sleep: ");
if(sleep == true){
  lcd.print("ON");
}else{
  lcd.print("OFF");
}
lcd.setCursor(10, 0);
lcd.print("overR: ");
if(overRide == true){
  lcd.print("ON");
}else{
  lcd.print("OFF");
}
lcd.setCursor(0, 1);
lcd.print(rtc.getDate(), DEC);
lcd.print('/');
lcd.print(rtc.getMonth(century), DEC);
lcd.print('/');
lcd.print(rtc.getYear(), DEC);
lcd.print(' ');
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
lcd.setCursor(15, 3);
lcd.print("SL:");
if(shelf == true){
  lcd.print("ON");
}else{
  lcd.print("OF");
}
delay(100);

}
