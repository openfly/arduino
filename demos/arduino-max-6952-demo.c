// Max 6952 Example Code For Arduino
// Tested on Boarduino
// matt@nycresistor.com

#define DATAOUT 11//MOSI
#define DATAIN 12//MISO - not used, but part of builtin SPI
#define SPICLOCK  13//sck
#define SLAVESELECT 10//ss

char spi_transfer(volatile char data)
{
  SPDR = data;
  // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
  {
  };
  return SPDR;                    // return the received byte
}

void setup()
{
  byte i;
  byte clr;
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  digitalWrite(SLAVESELECT,HIGH); //disable device
  // SPCR = 01010000
  //interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
  //sample on leading edge of clk,system clock/4 (fastest)
  SPCR = 0b01010010;  
  clr=SPDR;
  delay(32);
     // Configure Register
     write_led_twice(0x04,0x01);
     // Intensity Pane 1 and Pane 2
     write_led_twice(0x01,0xFF);
     write_led_twice(0x02,0xFF);
     // Scan Limit
     write_led_twice(0x03,0x01);
     
}

byte write_led(int address, int value)
{
  digitalWrite(SLAVESELECT,LOW);
  //2 byte opcode
  spi_transfer(address);
  spi_transfer(value);
  
  delay(36);
  digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer
}

// Write n times for n chips daisy chained.
byte write_led_twice(int address, int value)
{
  digitalWrite(SLAVESELECT,LOW);
  //2 byte opcode
  spi_transfer(address);
  spi_transfer(value);
  spi_transfer(address);
  spi_transfer(value);
  delay(36);
  digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer
}

void loop()
{
     // Testing ROM Character Set
     write_led_twice(0x20,0x5e);
     write_led_twice(0x21,0x5e);
     write_led_twice(0x22,0x5e);
     write_led_twice(0x23,0x5e);
     delay(4000);
     // Testing Programmable RAM Space
     write_led_twice(0x05,0x80);
     write_led_twice(0x05,0x42);
     write_led_twice(0x05,0x61);
     write_led_twice(0x05,0x51);
     write_led_twice(0x05,0x49);
     write_led_twice(0x05,0x46);
     write_led_twice(0x20,0x80);
     write_led_twice(0x21,0x80);
     write_led_twice(0x22,0x80);
     write_led_twice(0x23,0x80);
     delay(4000);
     // Gred Test Register Call
     write_led_twice(0x07,0x01);
     
     delay(1000);     
     // Turn off Test Register
     write_led_twice(0x07,0x00);
}
