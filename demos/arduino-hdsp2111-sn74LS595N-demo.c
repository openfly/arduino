/*
 Demo Code for HDSP 2111 using SN74LS595N 
 Matt Joyce < matt@nycresistor.com >
 Thanks to Mark Tabry for assistance
*/

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;
const int ce = 5;
const int wr = 6;
const int a2 = 4;
const int a1 = 3;
const int a0 = 2;
const int rst = 10;
const int a3 = 9;
int incomingByte = 0;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(rst, OUTPUT);
  pinMode(ce, OUTPUT);
  pinMode(wr, OUTPUT);
  digitalWrite(ce, HIGH);
  digitalWrite(wr, HIGH);
  
  resetDisplay();
}

void resetDisplay() {
  digitalWrite(rst, LOW);
  delayMicroseconds(1);
  digitalWrite(rst,HIGH);
  delayMicroseconds(150);
  digitalWrite(a3, HIGH);
}   

void writeDisplay(char *input) {
//  Serial.println(input);
  for (int i=0; i<8; i++) {    
    digitalWrite(a0, (1&i)!=0?HIGH:LOW);
    digitalWrite(a1, (2&i)!=0?HIGH:LOW);
    digitalWrite(a2, (4&i)!=0?HIGH:LOW);
       
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, input[i] );
    digitalWrite(latchPin, HIGH);
    delay(1);    
    digitalWrite(ce, LOW);
    delay(1);
    digitalWrite(wr, LOW);
    delay(1); 
    digitalWrite(wr, HIGH);
    delay(1);
    digitalWrite(ce, HIGH);
    delay(1);
  }
}

void scrollDisplay(char *words) {
  char buffer[9];
  int i = 0;
  while(words[i] != 0){
    boolean blank = false;
    for (int j = 0; j<8; j++) {
      if ( !blank && words[i+j] == 0 ) {
        blank = true;
      }
      
      if ( blank ) {
        buffer[j] = ' ';
      }
      else {
        buffer[j] = words[i+j];
      }
    }
    buffer[8]=0;
    writeDisplay(buffer);
    delay(200);
    i++;
 }

}

void loop() {
    char intro[] = "        Number 9 ";
    scrollDisplay(intro);
    delay(2000);
}   
