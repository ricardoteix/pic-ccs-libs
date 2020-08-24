#include <16F628A.h>
#fuses INTRC_IO, NOMCLR, NOPUT, NOWDT
#use delay(clock=4Mhz)

#define TM1637_DIO PIN_A0
#define TM1637_CLK PIN_A1

#include "TM1637Display.c"

int16 seconds = 9000;

void main() {
   
   while(true) {
      output_toggle(PIN_A2);
      showNumber(seconds++);
      delay_ms(50);
   }
   
}


