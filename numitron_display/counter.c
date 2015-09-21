//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

void setup() {
  pinMode(latchPin, OUTPUT);

}

void loop() {
  while(1) {
  for (int zu = 0; zu < 10; zu++) { 
    displayNum(zu);
  }
  }
}

void displayNum(int num) {
  /*
      00000001 = decimal
      00000010 = left lower
      00000100 = bottom middle
      00001000 = middle middle
      00010000 = left top
      00100000 = middle top
      01000000 = right bottom
      10000000 = right top

      248 = 9  11111000
      254 = 8  11111110
      224 = 7  11100000
      126 = 6  01111110
      124 = 5  01111100
      216 = 4  11011000
      236 = 3  11101100
      174 = 2  10101110
      18  = 1  00010010
      246 = 0  11110110
      .   = 1  00000001
  */  
  
  int de = 200;
  switch(num){
    case 1 :
      hitshift(18,de);
      break;
    case 2 :
      hitshift(174,de);
      break;
    case 3 :
      hitshift(236,de);
      break;
    case 4 :
      hitshift(216,de);
      break;
    case 5 :
      hitshift(124,de);
      break;
    case 6 :
      hitshift(126,de);
      break;
    case 7 :
      hitshift(224,de);
      break;
    case 8 : 
      hitshift(254,de);
      break;
    case 9 : 
      hitshift(248,de);
      break;
    default:
      hitshift(246,de);
      break;
  }
}

void hitshift(int n, int d) {
  PORTB = B00000001;
  PORTB = B00000000;
  shiftOut(dataPin, clockPin, n);
  PORTB = B00000001;
  delay(d);
  PORTB = B00000000;
  shiftOut(dataPin, clockPin, 0);
  PORTB = B00000001;
  delay(d);
}

