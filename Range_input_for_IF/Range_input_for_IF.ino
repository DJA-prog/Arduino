
bool inRange(int val, int minimum, int maximum){return ((minimum <= val) && (val <= maximum));}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  
  int x = analogRead(A0);
  if ( inRange(x, 0, 200) ){
    
  }

}
