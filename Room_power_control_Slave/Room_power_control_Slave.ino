//Father Arduino COM 4 Slave
#include <Wire.h>

long unsigned int i2cCode;

void setup() {
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  if(i2cCode > 0){
Serial.print(i2cCode);
  }
  if(i2cCode == 1){
    digitalWrite(2, LOW);
  }
  if(i2cCode == 2){
    digitalWrite(2, HIGH);
  }
  if(i2cCode == 3){
    digitalWrite(3, LOW);
  }
  if(i2cCode == 4){
    digitalWrite(3, HIGH);
  }
  if(i2cCode == 5){
    digitalWrite(4, LOW);
  }
  if(i2cCode == 6){
    digitalWrite(4, HIGH);
  }
  if(i2cCode == 7){
    digitalWrite(5, LOW);
  }
  if(i2cCode == 8){
    digitalWrite(5, HIGH);
  }
  if(i2cCode == 9){
    digitalWrite(6, LOW);
  }
  if(i2cCode == 10){
    digitalWrite(6, HIGH);
  }
  if(i2cCode == 11){
    digitalWrite(7, LOW);
  }
  if(i2cCode == 12){
    digitalWrite(7, HIGH);
  }
  if(i2cCode == 13){
    digitalWrite(8, LOW);
  }
  if(i2cCode == 14){
    digitalWrite(8, HIGH);
  }
  if(i2cCode == 15){
    digitalWrite(9, LOW);
  }
  if(i2cCode == 16){
    digitalWrite(9, HIGH);
  }

  
i2cCode = 0;
delay(50);
}

void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    i2cCode = Wire.read();
    Serial.println(i2cCode);
  }
}
