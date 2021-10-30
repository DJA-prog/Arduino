#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 4, 3, 2, 1, 0); // RS, E , D4 , D5 , D6 , D7

#include <IRremote.h>
int RECV_PIN = A2;
IRrecv irrecv(RECV_PIN);
decode_results results;
long unsigned int irCode;

float celsiustemp;
float voltage;

int Mux1_State[8] = {0};
int Mux1reading1 = 0;
int Mux1reading2 = 0;
int Mux1reading3 = 0;
int Mux1reading4 = 0;
int Mux1reading5 = 0;
int Mux1reading6 = 0;
int Mux1reading7 = 0;
int Mux1reading8 = 0;
int Mux2_State[8] = {0};
int Mux2reading1 = 0;
int Mux2reading2 = 0;
int Mux2reading3 = 0;
int Mux2reading4 = 0;
int Mux2reading5 = 0;
int Mux2reading6 = 0;
int Mux2reading7 = 0;
int Mux2reading8 = 0;
void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  delay(10);
}

void loop() {
  updateMux1();
  updateMux2();
  remoteControl();
  temprature();
  Serial.println(celsiustemp);
  delay(1000);
  Serial.flush();
}
void updateMux1() {
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  delay(10);
  for (int i = 0; i < 8; i++){
    digitalWrite(13,HIGH);
    delay(1);
    digitalWrite(13,LOW);
    delay(1);
    Mux1_State[i] = analogRead(A0);
    
    if (i == 0){
      Serial.print("Mux1:  ");
      Mux1reading1 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 1){
      Mux1reading2 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 2){
      Mux1reading3 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 3){
      Mux1reading4 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 4){
      Mux1reading5 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 5){
      Mux1reading6 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 6){
      Mux1reading7 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.print(" , ");
    }if (i == 7){
      Mux1reading8 = Mux1_State[i];Serial.print(Mux1_State[i]);Serial.println(" , ");
    }
    
  }
}
void updateMux2() {
  digitalWrite(12, HIGH);
  delay(10);
  digitalWrite(12, LOW);
  delay(10);
  for (int i = 0; i < 8; i++){
    digitalWrite(13, HIGH);
    delay(1);
    digitalWrite(13, LOW);
    delay(1);
    Mux2_State[i] = analogRead(A1);
    
    if (i == 0){
      Serial.print("Mux2:  ");
      Mux2reading1 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.print(" , ");
    }if (i == 1){
      Mux2reading2 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.print(" , ");
    }if (i == 2){
      Mux2reading3 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.print(" , ");
    }if (i == 3){
      Mux2reading4 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.print(" , ");
    }if (i == 4){
      Mux2reading5 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.print(" , ");
    }if (i == 5){
      Mux2reading6 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.print(" , ");
    }if (i == 6){
      Mux2reading7 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.print(" , ");
    }if (i == 7){
      Mux2reading8 = Mux2_State[i];Serial.print(Mux2_State[i]);Serial.println("   ");
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
void temprature(){
  voltage = Mux1reading1;
  float volts = voltage/205.0;
  celsiustemp = 100.0 * volts - 50;
}

