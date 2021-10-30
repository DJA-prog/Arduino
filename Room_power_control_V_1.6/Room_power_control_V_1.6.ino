#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E , D4 , D5 , D6 , D7

const unsigned long lcdTimeInterval = 1000;
unsigned long previousTime = 0;

#include <IRremote.h>
int RECV_PIN = A2;
IRrecv irrecv(RECV_PIN);
decode_results results;
long unsigned int irCode;

int Mux1_State[8] = {0};
int Mux2_State[8] = {0};

int Mux1reading1 = 0;
int Mux1reading2 = 0;
int Mux1reading3 = 0;
int Mux1reading4 = 0;
int Mux1reading5 = 0;
int Mux1reading6 = 0;
int Mux1reading7 = 0;
int Mux1reading8 = 0;

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
  lcd.begin(20, 4);
  lcd.clear();
  irrecv.enableIRIn();
  pinMode(A0, INPUT);//Mux 2 3
  pinMode(A1, INPUT);//Mux 4 5
  pinMode(A2, INPUT);//IR
  pinMode(8, OUTPUT);//Mux 1 OR Output to board
  pinMode(9, OUTPUT);//Large LED
  pinMode(10, OUTPUT);//small LED
  pinMode(11, OUTPUT);//A
  pinMode(12, OUTPUT);//B
  pinMode(13, OUTPUT);//C

  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(8, HIGH); delay(1);
  digitalWrite(8, LOW);
  delay(1);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  digitalWrite(8, HIGH); delay(1);
  digitalWrite(8, LOW);
  delay(1);
  lcd.print("Hello World");
  delay(1000);
  lcd.clear();
  
  
  
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void loop() {
  MUXREAD();
  remoteControl();
  delay(1000);
  lcd.print("Hello World");
  delay(1000);
  lcd.clear();
  Serial.println("MUX: 1");
  Serial.println(Mux1reading1);
  Serial.println(Mux1reading2);
  Serial.println(Mux1reading3);
  Serial.println(Mux1reading4);
  Serial.println(Mux1reading5);
  Serial.println(Mux1reading6);
  Serial.println(Mux1reading7);
  Serial.println(Mux1reading8);
  Serial.println("MUX: 2");
  Serial.println(Mux2reading1);
  Serial.println(Mux2reading2);
  Serial.println(Mux2reading3);
  Serial.println(Mux2reading4);
  Serial.println(Mux2reading5);
  Serial.println(Mux2reading6);
  Serial.println(Mux2reading7);
  Serial.println(Mux2reading8);
  delay(2000);

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void MUXREAD(){ //Mux 2 3 Reading
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);delay(500);
  digitalWrite(8, HIGH);delay(500);
  digitalWrite(8, LOW);
  delay(1);
  
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);delay(500);
  digitalWrite(8, HIGH);delay(500);
  digitalWrite(8, LOW);
  delay(1);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);delay(500);
  
  for (int i = 0; i < 8; i++){
    delay(500);
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
    delay(5);             //Mux2 C
    digitalWrite(8,LOW);  //Mux2 C
    delay(5);
  }
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);delay(500);
  digitalWrite(8, HIGH);delay(500);
  digitalWrite(8, LOW);
  delay(1);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);delay(500);
  digitalWrite(8, HIGH);delay(500);
  digitalWrite(8, LOW);delay(500);
  digitalWrite(8, HIGH);delay(500);
  digitalWrite(8, LOW);
  delay(1);
  
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);delay(500);
  
  for (int i = 0; i < 8; i++){
    delay(500);
    Mux2_State[i] = analogRead(A1);
    if (i == 0){
      Mux2reading1 = Mux2_State[i];
    }if (i == 1){
      Mux2reading2 = Mux2_State[i];
    }if (i == 2){
      Mux2reading3 = Mux2_State[i];
    }if (i == 3){
      Mux2reading4 = Mux2_State[i];
    }if (i == 4){
      Mux2reading5 = Mux2_State[i];
    }if (i == 5){
      Mux2reading6 = Mux2_State[i];
    }if (i == 6){
      Mux2reading7 = Mux2_State[i];
    }if (i == 7){
      Mux2reading8 = Mux2_State[i];
    }
    digitalWrite(8,HIGH); //Mux2 C
    delay(5);             //Mux2 C
    digitalWrite(8,LOW);  //Mux2 C
    delay(5);
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
