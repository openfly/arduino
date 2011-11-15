// pin definitions

#define PIN_A 2 // Row A, PORTD, PIN 2
#define PIN_B 3 // Row B, PORTD, PIN 3
#define PIN_C 4 // Row C, PORTD, PIN 4
#define PIN_D 5 // Row D, PORTD, PIN 5

#define PIN_G1 1 // Green top, PORTB, PIN 1
#define PIN_G2 2 // Green bottom, PORTB, PIN 2
#define PIN_R1 3 // Red top, PORTB, PIN 3
#define PIN_R2 4 // Red Bottom, PORTB, PIN 4

#define PIN_CLK 0 // Clock pin, PORTB, PIN 0
#define PIN_LATCH 6 // Latch pin, PORTD, PIN 6
#define PIN_EN 7 // Enable pin, PORTD, PIN 7


unsigned char redBuffer[256] = {
  0};    // 32*64/8 = 256
unsigned char greenBuffer[256] = {
  0};

void setup() {
  // set pins as output
  DDRD |= (1<<PIN_A) | (1<<PIN_B) | (1<<PIN_C) | (1<<PIN_D) | (1<<PIN_EN) | (1<<PIN_LATCH);
  DDRB |= (1<<PIN_CLK) | (1<<PIN_R1) | (1<<PIN_R2) | (1<<PIN_G1) | (1<<PIN_G2);



  // init serial port
  //Serial.begin(19200);
}

// draw a green pixel
void setGreen(unsigned char x, unsigned char y, unsigned char color) {
  setPixel(x, color, &greenBuffer[(y << 3) + (x >> 3)]);
}

// draw a red pixel
void setRed(unsigned char x, unsigned char y, unsigned char color) {
  setPixel(x, color, &redBuffer[(y << 3) + (x >> 3)]);
}

void setPixel(unsigned char x, unsigned char color, unsigned char *buffer) {
  unsigned char bitPos = (7 - x % 8);
  if (color == 0)
    *buffer &= ~(1 << bitPos);
  else 
    *buffer |= color << bitPos;
}

// select correct A,B,C or D lines
void setRow(unsigned char row) {
  // clear all
  PORTD &= ~((1<<PIN_A)|(1<<PIN_B)|(1<<PIN_C)|(1<<PIN_D));
  // set row
  PORTD |= ((row & 0x0F) << 2); 
}

// redraw the screen
void redrawDisplay() {
  unsigned char data, bytecnt,bitcnt, bitmask;
  int pos = 0;

  for (unsigned char row = 0; row < 16; row++) {
    // Disable display
    PORTD &= ~(1<<PIN_EN); 

    for (bytecnt = 0; bytecnt < 8; bytecnt++) {
      for (bitcnt = 0; bitcnt < 8; bitcnt++) {
        bitmask = 1 << (7 - bitcnt);

        PORTB &= ~((1<<PIN_R1)|(1<<PIN_R2)|(1<<PIN_G1)|(1<<PIN_G2)|(1<<PIN_CLK));

        PORTB |= !(redBuffer[pos] & bitmask) ?  (1<<PIN_R1) : 0;
        PORTB |= !(redBuffer[pos + 128] & bitmask) ? (1<<PIN_R2) : 0;
        PORTB |= !(greenBuffer[pos] & bitmask) ?  (1<<PIN_G1) : 0;
        PORTB |= !(greenBuffer[pos + 128] & bitmask) ?  (1<<PIN_G2) : 0;

        // Clock high
        PORTB |=  (1<<PIN_CLK);
      }
      pos++;
    }

    // Enable display
    PORTD |= (1<<PIN_EN);

    // Latch the data
    PORTD &= ~(1<<PIN_LATCH);
    PORTD |= (1<<PIN_LATCH);

    setRow(row);

    delayMicroseconds(1);
  }
}

// draws a frame around the screen
void drawFrame() {

  for (unsigned char x=0;x<=63;x++) {
    setRed(x,0,1);
    //seGreen(x,1,1);
    setRed(x,31,1);
    //setGreen(x,31,1);
  }

  for (unsigned char y=0;y<32; y++) {
    setRed(0,y,1);
    //seGreen(0,y,1);
    setRed(63,y,1);
    //setGreen(63,y,1);
  }
}

// 5 x 7 letters
void lettersG_A(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+2,y,1);
  setGreen(x+1,y+1,1);
  setGreen(x+3,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_B(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
}

void lettersG_C(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_D(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
}

void lettersG_E(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_F(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x,y+6,1);

}

void lettersG_G(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
}

void lettersG_H(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_I(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x+2,y+1,1);
  setGreen(x+2,y+2,1);
  setGreen(x+2,y+3,1);
  setGreen(x+2,y+4,1);
  setGreen(x+2,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_J(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+4,y,1);
  setGreen(x+4,y+1,1);
  setGreen(x+4,y+2,1);
  setGreen(x+4,y+3,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
}

void lettersG_K(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+3,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+2,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+1,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+2,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+3,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_L(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_M(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+1,y+1,1);
  setGreen(x+3,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+2,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_N(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+1,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+3,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_O(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
}

void lettersG_P(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x,y+6,1);
}

void lettersG_Q(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+2,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+3,y+5,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_R(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+2,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+3,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_S(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+1,y+3,1);
  setGreen(x+2,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x+4,y+4,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
}

void lettersG_T(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x+2,y+1,1);
  setGreen(x+2,y+2,1);
  setGreen(x+2,y+3,1);
  setGreen(x+2,y+4,1);
  setGreen(x+2,y+5,1);
  setGreen(x+2,y+6,1);
}

void lettersG_U(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
}

void lettersG_V(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x+1,y+5,1);
  setGreen(x+3,y+5,1);
  setGreen(x+2,y+6,1);
}

void lettersG_W(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x,y+2,1);
  setGreen(x+4,y+2,1);
  setGreen(x,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x,y+4,1);
  setGreen(x+2,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+1,y+5,1);
  setGreen(x+3,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_X(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x+1,y+2,1);
  setGreen(x+3,y+2,1);
  setGreen(x+2,y+3,1);
  setGreen(x+1,y+4,1);
  setGreen(x+3,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+4,y+6,1);
}

void lettersG_Y(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+4,y,1);
  setGreen(x,y+1,1);
  setGreen(x+4,y+1,1);
  setGreen(x+1,y+2,1);
  setGreen(x+3,y+2,1);
  setGreen(x+2,y+3,1);
  setGreen(x+2,y+4,1);
  setGreen(x+2,y+5,1);
  setGreen(x+2,y+6,1);
}

void lettersG_Z(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  setGreen(x,y,1);
  setGreen(x+1,y,1);
  setGreen(x+2,y,1);
  setGreen(x+3,y,1);
  setGreen(x+4,y,1);
  setGreen(x+4,y+1,1);
  setGreen(x+3,y+2,1);
  setGreen(x+2,y+3,1);
  setGreen(x+1,y+4,1);
  setGreen(x,y+5,1);
  setGreen(x,y+6,1);
  setGreen(x+1,y+6,1);
  setGreen(x+2,y+6,1);
  setGreen(x+3,y+6,1);
  setGreen(x+4,y+6,1);
}

// 5 x 7 letters
void lettersR_A(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+2,y,1);
  setRed(x+1,y+1,1);
  setRed(x+3,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_B(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
}

void lettersR_C(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x,y+2,1);
  setRed(x,y+3,1);
  setRed(x,y+4,1);
  setRed(x,y+5,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_D(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
}

void lettersR_E(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x,y+1,1);
  setRed(x,y+2,1);
  setRed(x,y+3,1);
  setRed(x,y+4,1);
  setRed(x,y+5,1);
  setRed(x,y+6,1);
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_F(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x,y+2,1);
  setRed(x,y+3,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x,y+4,1);
  setRed(x,y+5,1);
  setRed(x,y+6,1);

}

void lettersR_G(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x,y+2,1);
  setRed(x,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
}

void lettersR_H(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_I(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x+2,y+1,1);
  setRed(x+2,y+2,1);
  setRed(x+2,y+3,1);
  setRed(x+2,y+4,1);
  setRed(x+2,y+5,1);
  setRed(x,y+6,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_J(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+4,y,1);
  setRed(x+4,y+1,1);
  setRed(x+4,y+2,1);
  setRed(x+4,y+3,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
}

void lettersR_K(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+3,y+1,1);
  setRed(x,y+2,1);
  setRed(x+2,y+2,1);
  setRed(x,y+3,1);
  setRed(x+1,y+3,1);
  setRed(x,y+4,1);
  setRed(x+2,y+4,1);
  setRed(x,y+5,1);
  setRed(x+3,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_L(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x,y+1,1);
  setRed(x,y+2,1);
  setRed(x,y+3,1);
  setRed(x,y+4,1);
  setRed(x,y+5,1);
  setRed(x,y+6,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_M(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+1,y+1,1);
  setRed(x+3,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+2,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_N(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+1,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+3,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_O(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
}

void lettersR_P(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x,y+4,1);
  setRed(x,y+5,1);
  setRed(x,y+6,1);
}

void lettersR_Q(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+2,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+3,y+5,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_R(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x,y+4,1);
  setRed(x+2,y+4,1);
  setRed(x,y+5,1);
  setRed(x+3,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_S(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x,y+2,1);
  setRed(x+1,y+3,1);
  setRed(x+2,y+3,1);
  setRed(x+3,y+3,1);
  setRed(x+4,y+4,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
}

void lettersR_T(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x+2,y+1,1);
  setRed(x+2,y+2,1);
  setRed(x+2,y+3,1);
  setRed(x+2,y+4,1);
  setRed(x+2,y+5,1);
  setRed(x+2,y+6,1);
}

void lettersR_U(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
}

void lettersR_V(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x+1,y+5,1);
  setRed(x+3,y+5,1);
  setRed(x+2,y+6,1);
}

void lettersR_W(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x,y+2,1);
  setRed(x+4,y+2,1);
  setRed(x,y+3,1);
  setRed(x+4,y+3,1);
  setRed(x,y+4,1);
  setRed(x+2,y+4,1);
  setRed(x+4,y+4,1);
  setRed(x,y+5,1);
  setRed(x+1,y+5,1);
  setRed(x+3,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_X(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x+1,y+2,1);
  setRed(x+3,y+2,1);
  setRed(x+2,y+3,1);
  setRed(x+1,y+4,1);
  setRed(x+3,y+4,1);
  setRed(x,y+5,1);
  setRed(x+4,y+5,1);
  setRed(x,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersR_Y(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+4,y,1);
  setRed(x,y+1,1);
  setRed(x+4,y+1,1);
  setRed(x+1,y+2,1);
  setRed(x+3,y+2,1);
  setRed(x+2,y+3,1);
  setRed(x+2,y+4,1);
  setRed(x+2,y+5,1);
  setRed(x+2,y+6,1);
}

void lettersR_Z(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,1);
  setRed(x+1,y,1);
  setRed(x+2,y,1);
  setRed(x+3,y,1);
  setRed(x+4,y,1);
  setRed(x+4,y+1,1);
  setRed(x+3,y+2,1);
  setRed(x+2,y+3,1);
  setRed(x+1,y+4,1);
  setRed(x,y+5,1);
  setRed(x,y+6,1);
  setRed(x+1,y+6,1);
  setRed(x+2,y+6,1);
  setRed(x+3,y+6,1);
  setRed(x+4,y+6,1);
}

void lettersG_PEW(unsigned char x, unsigned char y)
{
  // setGreen(x,y,on/off)
  // setGreen(x,y,1);
  setGreen(x+9,y,1);
  setGreen(x+10,y,1);
  
  setGreen(x+1,y+1,1);
  setGreen(x+8,y+1,1);
  setGreen(x+9,y+1,1);
  
  setGreen(x,y+2,1);
  setGreen(x+2,y+2,1);
  setGreen(x+8,y+2,1);
  setGreen(x+9,y+2,1);
  setGreen(x+12,y+2,1);
  
  setGreen(x,y+3,1);
  setGreen(x+3,y+3,1);
  setGreen(x+4,y+3,1);
  setGreen(x+8,y+3,1);
  setGreen(x+9,y+3,1);
  setGreen(x+10,y+3,1);
  setGreen(x+11,y+3,1);
  setGreen(x+12,y+3,1);
  
  setGreen(x+1,y+4,1);
  setGreen(x+3,y+4,1);
  setGreen(x+4,y+4,1);
  setGreen(x+5,y+4,1);
  setGreen(x+7,y+4,1);
  setGreen(x+8,y+4,1);
  setGreen(x+9,y+4,1);
  setGreen(x+10,y+4,1);
  setGreen(x+11,y+4,1);
  
  setGreen(x,y+5,1);
  setGreen(x+4,y+5,1);
  setGreen(x+5,y+5,1);
  setGreen(x+6,y+5,1);
  setGreen(x+7,y+5,1);
  setGreen(x+8,y+5,1);
  
  setGreen(x+5,y+6,1);
  setGreen(x+6,y+6,1);
  setGreen(x+7,y+6,1);
  
  setGreen(x+4,y+7,1);
  setGreen(x+5,y+7,1);
  setGreen(x+6,y+7,1);
  setGreen(x+7,y+7,1);
  setGreen(x+8,y+7,1);
  setGreen(x+10,y+7,1);
  
  setGreen(x+1,y+8,1);
  setGreen(x+2,y+8,1);
  setGreen(x+3,y+8,1);
  setGreen(x+4,y+8,1);
  setGreen(x+5,y+8,1);
  setGreen(x+7,y+8,1);
  setGreen(x+8,y+8,1);
  setGreen(x+9,y+8,1);
  
  setGreen(x,y+9,1);
  setGreen(x+1,y+9,1);
  setGreen(x+2,y+9,1);
  setGreen(x+3,y+9,1);
  setGreen(x+4,y+9,1);
  setGreen(x+8,y+9,1);
  setGreen(x+9,y+9,1);
  setGreen(x+10,y+9,1);
  
  setGreen(x,y+10,1);
  setGreen(x+3,y+10,1);
  setGreen(x+4,y+10,1);
  setGreen(x+6,y+10,1);
  setGreen(x+10,y+10,1);
  setGreen(x+11,y+10,1);
  
  setGreen(x+3,y+11,1);
  setGreen(x+4,y+11,1);
  setGreen(x+11,y+11,1);
  
  setGreen(x+2,y+12,1);
  setGreen(x+3,y+12,1);
  setGreen(x+12,y+12,1);
  
}

void lettersB_B(unsigned char x, unsigned char y)
{
  // setRed(x,y,on/off)
  setRed(x,y,0);
  
  for (int i = 0; i < 13; i++) {
    for(int j = 0; j < 13; j++) {
      setRed(x + j,y + i,0);
      setGreen(x + j,y + i,0);
    }
  }
}

void clrdisplay()
{
  int x;
  int y;
  
  for (x=0;x=63;x++)
  {
    for(y=0;y=31;y++)
    {
      setRed(x,y,0);
      setGreen(x,y,0);
    }

  }
}

int acount;
int count;
int Xray;
int Yray;
void loop()
{
  int x;
  int y;
  static long refresh = 5;
  redrawDisplay();
  acount++;
  count = acount / 3;
  lettersB_B(Xray, Yray);


  if (Yray >= 19) {
      Yray = 0;  
  }
  if (count > 58) {
    acount = 1;    Yray++;
    
  }
  
  // draw the frame around playground
  drawFrame();
  Xray = 0;
  Xray += count;
  lettersG_PEW(Xray,Yray);
  

  
  lettersR_M(4,8);
  lettersR_A(10,8);
  lettersR_K(16,8);
  lettersR_E(22,8);
  lettersR_R(28,8);
  
  lettersG_F(30,16);
  lettersG_A(36,16);
  lettersG_I(42,16);
  lettersG_R(48,16);
  lettersG_E(54,16);
  
  // delayMicroseconds(10000);
  refresh = millis() + 1000;

}








