
const int RCLKPin = 8;
// Pin connected to SRCLK -- shift register clock pin -- of 74HC595
const int SRCLKPin = 12;
// Pin connected to SER -- serial data input -- of 74HC595
const int SERPin = 11;

const int nums[10] = {
0b11011110,
0b00000110,
0b11101010,
0b01101110,
0b00110110,
0b01111100,
0b11111100,
0b00001110,
0b11111110,
0b01111110
};

int dig1count;
int dig2count;
int dig3count;
int dig4count;

void setup() {

// set pins to output so you can control the shift register
pinMode(RCLKPin, OUTPUT);
pinMode(SRCLKPin, OUTPUT);
pinMode(SERPin, OUTPUT);

}

void loop() {

  dig1count++;

  if (dig1count >= 10) {
    dig1count = 0;
    dig2count++;
  }

  if (dig2count >= 10) {
    dig2count = 0;
    dig3count++;
  }
  
  if (dig3count >= 10) {
    dig3count = 0;
    dig4count++;
  }
  
  if (dig4count >= 10) {
    dig4count = 0;
  }
    
// set RCLK low; wait till we transmit the byte, and they moving it high will output the data
digitalWrite(RCLKPin, LOW);

// shift out the bits (MSBFIRST = most significant bit first)
shiftOut(SERPin, SRCLKPin, MSBFIRST, nums[dig4count]);
shiftOut(SERPin, SRCLKPin, MSBFIRST, nums[dig3count]);
shiftOut(SERPin, SRCLKPin, MSBFIRST, nums[dig2count]);
shiftOut(SERPin, SRCLKPin, MSBFIRST, nums[dig1count]);
/*

0b00000001 = E
0b00000010 = D
0b00000100 = F
0b00001000 = C
0b00010000 = B
0b00100000 = A
0b01000000 = G
0b10000000 = H

0 = 0b11011110
1 = 0b00000110
2 = 0b11101010
3 = 0b01101110
4 = 0b00110110
5 = 0b01111100
6 = 0b11111100
7 = 0b00001110
8 = 0b11111110
9 = 0b01111110

*/


// send shift register data to the storage register
digitalWrite(RCLKPin, HIGH);

// catch our breath before repeating
delay(100);
}


