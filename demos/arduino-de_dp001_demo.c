// DE-DP001 Interface Example for Arduino / ATMEGA168
// matt@nycresistor.com

#define DATAOUT 11//MOSI
#define SPICLOCK 13//sck
#define DIMM 9//DIMM

char spi_transfer(volatile char data)
{
  SPDR = data;
  //
  while (!(SPSR & (1<<SPIF)))
  {
  };
  return SPDR;
}

void setup()
{
  byte i;
  byte clr;
  pinMode (DATAOUT, OUTPUT);
  pinMode (SPICLOCK, OUTPUT);
  pinMode (10, OUTPUT);
 
  pinMode (DIMM, OUTPUT);
  digitalWrite(DIMM, HIGH);
  
  SPCR = 0b01010010;
  clr = SPDR;
  delay(32);
}

byte write_led(int value1 , int value2, int value3, int value4)
{
  digitalWrite(DIMM,LOW);
  //2 byte opcode
 spi_transfer(value1);
 spi_transfer(value2);
 spi_transfer(value3);
 spi_transfer(value4);
  delay(36);
  digitalWrite(DIMM,HIGH); //release chip, signal end transfer

}

void loop() 
{
  // 0x00 = NULL
  // 50 - 9F
  // 0x3F = 0
  // 0x06 = 1
  // 0x5B = 2
  // 0x4F = 3
  // 0x66 = 4  
  // 0x6d = 5
  // 0x7d = 6
  // 0x27 = nice 7
  // 0x07 = 7
  // 0x7f = 8
  // 0x6f = 9         0x76 = H, 0x77 A, 0x79 E 0x38 L

  // 0x86 = 1.
  // 0x87 = 7.
    
  write_led(0x76, 0x4f ,0x07, 0x3f);

// write_led(0x66);
// write_led(0xF2);
// write_led(0x60);
// write_led(0xFC);
delay(100000); // Display refresh  
}
