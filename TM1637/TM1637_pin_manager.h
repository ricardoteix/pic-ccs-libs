// DIO
#define pinDIO_SetDigitalOutput();   output_low(TM1637_DIO);
#define pinDIO_SetDigitalInput();    output_high(TM1637_DIO);
#define pinDIO_GetValue();           input(TM1637_DIO);

// CLOCK
#define pinClk_SetDigitalInput();    output_high(TM1637_CLK);
#define pinClk_SetDigitalOutput();   output_low(TM1637_CLK);
