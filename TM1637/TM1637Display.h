/*
*  Adaptado para CCS por Ricardo Teixeira
*  www.ricardoteix.com
*  Status: em andamento
*  
*  Exemplo e uso:
*  1. Definir constantes dos pinos DIO e CLK
*  2. Incluir biblioteca.
*  3. Usar fução para exibit número entre 0 e 9999.
*  
*  #define TM1637_DIO PIN_A0
*  #define TM1637_CLK PIN_A1
*  
*  #include "TM1637Display.c"
*  
*  int16 numero = 1234;
*  showNumber(numero);
*/

/* 
* ADAPTADO DE: 
* 
* Project Name: tm1637
* File: TM1637Display.h 
* Description: header file library TM1637  4 digit seven segment module 3462BS
* Author: Gavin Lyons.
* Complier: xc8 v2.05 compiler
* PIC: PIC16F1619 
* IDE:  MPLAB X v5.05
* Development board: Microchip Curiosity Board, PIC16F1619
* Created May 2019
*/

#ifdef TM1637_DIO
#ifdef TM1637_CLK

#ifndef __TM1637DISPLAY__
#define __TM1637DISPLAY__

#include "TM1637_pin_manager.h"

#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000


#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000

unsigned int8 m_brightness;

void setBrightness(unsigned int8 brightness, int1 on );

void setSegments(unsigned int8 segments[], unsigned int8 length , unsigned int8 pos );

void showNumberDec(int num, int1 leading_zero, unsigned int8 length , unsigned int8 pos );

void showNumberDecEx(int num, unsigned int8 dots , int1 leading_zero, unsigned int8 length , unsigned int8 pos );

void showNumber(int16 num);

unsigned int8 encodeDigit(unsigned int8 digit);

void bitDelay(void);
void start(void);
void stop(void);
int1 writeByte(unsigned int8 b);

#endif // __TM1637DISPLAY__
#endif // TM1637_CLK
#endif // TM1637_DIO
