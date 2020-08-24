#include "TM1637Display.h"

#define TM1637_I2C_COMM1    0x40  // automatic data incrementing
#define TM1637_I2C_COMM2    0xC0 // Data Data1~N: Transfer display data
#define TM1637_I2C_COMM3    0x80 // display intensity

unsigned int8 digitToSegment[] = {
   // XGFEDCBA
   0b00111111, // 0
   0b00000110, // 1
   0b01011011, // 2
   0b01001111, // 3
   0b01100110, // 4
   0b01101101, // 5
   0b01111101, // 6
   0b00000111, // 7
   0b01111111, // 8
   0b01101111, // 9
   0b01110111, // A
   0b01111100, // b
   0b00111001, // C
   0b01011110, // d
   0b01111001, // E
   0b01110001 // F
};

void setBrightness(unsigned int8 brightness, int1 on) {
   m_brightness = (brightness&0x7)| (on ? 0x08 : 0x00);
}

void setSegments(unsigned int8 segments[], unsigned int8 length, unsigned int8 pos){
   // Write COMM1
   start () ;
   writeByte (TM1637_I2C_COMM1) ;
   stop () ;

   // Write COMM2 + first digit address
   start () ;
   writeByte (TM1637_I2C_COMM2 + (pos&0x03));

   // Write the data bytes
   for (unsigned int8 k = 0; k < length; k++) {
      writeByte (segments[k]);
   }

   stop () ;

   // Write COMM3 + brightness
   start () ;
   writeByte (TM1637_I2C_COMM3 + (m_brightness & 0x0f));
   stop () ;
}

void showNumberDec(int16 num,  int1 leading_zero , unsigned int8 length, unsigned int8 pos){
   showNumberDecEx (num, 0, leading_zero, length, pos);
}

void showNumberDecEx(int16 num, unsigned int8 dots,  int1 leading_zero ,unsigned int8 length, unsigned int8 pos){
   unsigned int8 digits[4];
   static int16 divisors[] = { 1, 10, 100, 1000 };
   int1 leading = true;
   for (int8 k = 0; k < 4; k++){
      int16 divisor = divisors[4 - 1 - k];
      int16 d = num / divisor;
      unsigned int8 digit = 0;
      if (d == 0){
         if (leading_zero|| ! leading|| (k == 3)) {
            digit = encodeDigit (d);
         } else {
            digit = 0;
         }
      } else {
         digit = encodeDigit (d);
         num -= d * divisor;
         leading = false;
      }

    
    // Add the decimal point / colon to the digit
    digit |= (dots&0x80); 
    dots <<= 1;
    
    digits[k] = digit;
   }

   setSegments (digits + (4 - length), length, pos) ;
}

void showNumber(int16 num) {
   if (num <= 9999) {
       showNumberDecEx(num, 0, 1, 4, 0);
   }   
}

void bitDelay(){
   delay_us (75) ;
}

void start(){
   pinDIO_SetDigitalOutput ();
   bitDelay () ;
}

void stop(){
   pinDIO_SetDigitalOutput () ;
   bitDelay () ;
   pinClk_SetDigitalInput ();
   bitDelay () ;
   pinDIO_SetDigitalInput ();
   bitDelay () ;
}

int1 writeByte(unsigned int8 b){
   unsigned int8 data = b;

   // 8 Data Bits
   for (unsigned int8 i = 0; i < 8; i++){
      // CLK low
      pinClk_SetDigitalOutput () ;
      bitDelay () ;

      // Set data bit
      if (data&0x01) {
         pinDIO_SetDigitalInput () ;
      } else {
         pinDIO_SetDigitalOutput () ;
      }
      
      bitDelay () ;

      // CLK high
      pinClk_SetDigitalInput () ;
      bitDelay () ;
      data = data >> 1;
   }

   // Wait FOR acknowledge
   // CLK to zero
   pinClk_SetDigitalOutput () ;
   pinDIO_SetDigitalInput () ;
   bitDelay () ;

   // CLK to high
   pinClk_SetDigitalInput () ;
   bitDelay () ;
   unsigned int8 ack = input(TM1637_DIO);

   if (ack == 0) {
      pinDIO_SetDigitalOutput ();
   }
   
   bitDelay () ;
   pinClk_SetDigitalOutput () ;
   bitDelay () ;
   return ack;
}

unsigned int8 encodeDigit(unsigned int8 digit){
   return digitToSegment[digit & 0x0f];
}

