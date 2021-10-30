#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

#include <IRremote.h>
int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
int irCode;

int DC; //Display count
int screen = 1;
int ML;  //main light
int PWM; //PWM out
bool HV;  //HV light
bool SL;  //Shelf light
void remoteControl();
void lcdDisplay();
int intColorLevel = 0;
//#######################################################################
void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(6, OUTPUT); // Main light
  pinMode(4, INPUT);  // IR in
  pinMode(5, OUTPUT); //PWM out
  pinMode(7, OUTPUT); //HV light
  pinMode(8, OUTPUT); // Shelf light
  pinMode(9, OUTPUT); // RGB
  pinMode(10, OUTPUT); // RGB
  pinMode(11, OUTPUT); // RGB
  pinMode(12, INPUT); // Sense Door
}
//#######################################################################
void loop()
{
  DC++;
  if (DC > 100)
  {
    remoteControl();
    lcdDisplay();
    DC = 0;
  }
  switch (irCode) {
    case 0xE10: // Work
      Serial.print("Code: ");
      Serial.println("V+");
        ML++;
        if (ML > 255)
        {
          ML--;
        }
        break;
    case 0xE11: // Work
      Serial.print("Code: ");
      Serial.println("V-");
        ML--;
        if (ML < 0)
        {
          ML++;
        }
        break;
    case 0xE20: // Work
      Serial.print("Code: ");
      Serial.println("P+");
        PWM++;
        if (PWM > 255)
        {
          PWM--;
        }
        break;
    case 0xE21: // Work
      Serial.print("Code: ");
      Serial.println("P-");
        PWM--;
        if (PWM < 0)
        {
          PWM++;
        }
        break;
    case 0xE35: // Work
      Serial.print("Code: ");
      Serial.println("TV GUIDE");
        ML = 0;
        break;
    case 0xE1C: // Work
      Serial.print("Code: ");
      Serial.println("MENU");
        PWM = 0;
        break;
    case 0xE31: // Work
      Serial.print("Code: ");
      Serial.println("EXIT");
        PWM = 0;
        ML = 0;
        break;
    case 0xE00:
      Serial.print("Code: ");
      Serial.println("0");
        if (HV == true)
        {
          HV = false;
        }
        if (SL == true)
        {
          SL = false;
        }
        break;
    case 0xE2F:
      Serial.print("Code: ");
      Serial.println("TV");
        HV = !HV;
        Serial.print("HV: ");
        Serial.println(HV);
    case 0xE24:
      Serial.print("Code: ");
      Serial.println("_");
        SL = !SL;
        Serial.print("SL: ");
        Serial.println(SL);
    case 0xE12:
      Serial.print("Code: ");
      Serial.println("UP");
        intColorLevel++;
        if(intColorLevel > 255){intColorLevel=255;}
        break;
    case 0xE13:
      Serial.print("Code: ");
      Serial.println("Down");
        intColorLevel--;
        if(intColorLevel < 0){intColorLevel=0;}
        break;
    case 0xE22:
      Serial.print("Code: ");
      Serial.println("OK");
        analogWrite(9, 50);
        analogWrite(10, 50);
        analogWrite(11, 50);
        Serial.print("RGB: ");
        Serial.println(intColorLevel);
        break;
    case 0xE0C:
      Serial.print("Code: ");
      Serial.println("POWER");
      PWM = 0;
      ML = 0;
      SL = false;
      HV = false;
      analogWrite(9, 0);
      analogWrite(10, 0);
      analogWrite(11, 0);
      break;
  }

  analogWrite(6, ML);
  analogWrite(5, PWM);
  digitalWrite(7, HV);
  digitalWrite(8, SL);
  irCode = 0;
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
  if (screen == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAIN LIGHT:");
    lcd.setCursor(0, 1);
    lcd.print("BRIGHTNESS: ");
    lcd.print(ML / 255.0 * 100.0);
    lcd.print("%");
    lcd.setCursor(0, 2);
    lcd.print("BED LIGHT:");
    lcd.setCursor(0, 3);
    lcd.print("BRIGHTNESS: ");
    lcd.print("%");
    lcd.setCursor(19, 3);
    lcd.print(screen);
    delay(50);
  }
  if (screen == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAIN LIGHT: ");
    lcd.print(ML / 255.0 * 100.0);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("PWM: ");
    lcd.print(PWM / 255.0 * 100.0);
    lcd.print("%");
    lcd.setCursor(0, 2);
    lcd.print(irCode, HEX);
    lcd.setCursor(5, 2);
    lcd.print("RGB: ");
    lcd.print(intColorLevel);
    lcd.setCursor(19, 3);
    lcd.print(screen);
    delay(50);
  }
  // if (screen == 2)
  // {
  //   lcd.clear();
  //   lcd.setCursor(2, 1);
  //   lcd.print("TIME: ");
  //   lcd.print(":");
  //   lcd.print(":");
  //   lcd.setCursor(2, 2);
  //   lcd.print("COOLER: ");
  //   lcd.setCursor(0, 3);
  //   lcd.print("Cycles/Sec:");
  //   lcd.setCursor(19, 3);
  //   lcd.print(screen);
  // }

}
