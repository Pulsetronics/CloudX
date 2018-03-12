
// CloudX Configuration Bit Settings

// 'C' source line config statements

////////////////////////////////////////////////////////////
//Processor operting Frequency defined
///////////////////////////////////////////////////////////
#define _XTAL_FREQ 20000000




// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)





////////////////////////////////////////////////////////////
//Logic state Configuration defined libary
///////////////////////////////////////////////////////////
#define HIGH 1
#define LOW  0
#define INPUT 1
#define OUTPUT 0
#define ON_ALL 0xFF
#define OFF_ALL 0x00




////////////////////////////////////////////////////////////
//Delay loop defined library
////////////////////////////////////////////////////////////
#define delayMs __delay_ms
#define delayUs __delay_us
#define DelayMs __delay_ms
#define DelayUs __delay_us

////////////////////////////////////////////////////////////
//Program Configuration loops defined libary
///////////////////////////////////////////////////////////
#define loop()   while(1)
#define setup()     main()


////////////////////////////////////////////////////////////
//ANSI C defined libary
///////////////////////////////////////////////////////////
#define  inttostr itoa
#define  floattostr ftoa


////////////////////////////////////////////////////////////
//Operator library
///////////////////////////////////////////////////////////
#define is  ==
#define invert ~

////////////////////////////////////////////////////////////
//Logic library
///////////////////////////////////////////////////////////

#define true 1
#define false 0

#define integer int

////////////////////////////////////////////////////////////
//Pin Configuration defined libary
///////////////////////////////////////////////////////////
#define pin1 RB0
#define pin2 RB1
#define pin3 RB2
#define pin4 RB3
#define pin5 RB4
#define pin6 RB5
#define pin7 RB6
#define pin8 RB7
#define pin9 RD0
#define pin10 RD1
#define pin11 RD2
#define pin12 RD3
#define pin13 RD4
#define pin14 RD5
#define pin15 RD6
#define pin16 RD7



////////////////////////////////////////////////////////////
//PinMode Configuration defined libary
///////////////////////////////////////////////////////////
#define pin1Mode  TRISB0
#define pin2Mode  TRISB1
#define pin3Mode  TRISB2
#define pin4Mode  TRISB3
#define pin5Mode  TRISB4
#define pin6Mode  TRISB5
#define pin7Mode  TRISB6
#define pin8Mode  TRISB7
#define pin9Mode  TRISD0
#define pin10Mode  TRISD1
#define pin11Mode  TRISD2
#define pin12Mode  TRISD3
#define pin13Mode  TRISD4
#define pin14Mode  TRISD5
#define pin15Mode  TRISD6
#define pin16Mode  TRISD7



typedef union{
    struct{
        unsigned pin1   :1;
        unsigned pin2   :1;
        unsigned pin3   :1;
        unsigned pin4   :1;
        unsigned pin5   :1;
        unsigned pin6   :1;
        unsigned pin7   :1;
        unsigned pin8   :1;
    };
}Port_t;

extern volatile Port_t port1 @  0x006;

typedef union{
    struct {
        unsigned pin1   :1;
        unsigned pin2   :1;
        unsigned pin3   :1;
        unsigned pin4   :1;
        unsigned pin5   :1;
        unsigned pin6   :1;
        unsigned pin7   :1;
        unsigned pin8   :1;

    };
} pinModer_t;
extern volatile pinModer_t port1Mode @  0x086;

typedef union{
    struct {
        unsigned pin9   :1;
        unsigned pin10   :1;
        unsigned pin11  :1;
        unsigned pin12  :1;
        unsigned pin13   :1;
        unsigned pin14   :1;
        unsigned pin15   :1;
	unsigned pin16   :1;

    };
} pinModeAr_t;
extern volatile pinModeAr_t port2Mode @ 0x088;



void text(unsigned char *lcdtext);


typedef union{
    struct {
       unsigned pinA   :1;
        unsigned pin10   :1;
        unsigned pin11  :1;
        unsigned pin12  :1;
        unsigned pin13   :1;
        unsigned pin14   :1;
        unsigned pin15   :1;
	unsigned pin16   :1;

    };
} pinModeBr_t;
extern volatile pinModeBr_t port2 @ 0x008;

extern volatile unsigned char           PORT1               @ 0x006;
extern volatile unsigned char           PORT2               @ 0x008;

extern volatile unsigned char           PORT1MODE               @ 0x086;
extern volatile unsigned char           PORT2MODE               @ 0x088;



//Examples
//  port1Mode.port1Pin1=OUTPUT  // pin setup as input or output for Port1
//  port2Mode.port2Pin1=OUTPUT  // pin setup as input or output for Port2
//  pin1 = HIGH ;
//  pin5Mode = OUTPUT;
//  port1Pins.port1Pin7 = HIGH;
//  delayMs(1000);
//  delayUs(100);

PinSelect(char selPins, char segState){
    switch(selPins){
        case 1:     if (segState) pin1=HIGH; else pin1=LOW; break;
        case 2:     if (segState) pin2=HIGH; else pin2=LOW; break;
        case 3:     if (segState) pin3=HIGH; else pin3=LOW; break;
        case 4:     if (segState) pin4=HIGH; else pin4=LOW; break;
        case 5:     if (segState) pin5=HIGH; else pin5=LOW; break;
        case 6:     if (segState) pin6=HIGH; else pin6=LOW; break;
        case 7:     if (segState) pin7=HIGH; else pin7=LOW; break;
        case 8:     if (segState) pin8=HIGH; else pin8=LOW; break;
        case 9:     if (segState) pin9=HIGH; else pin9=LOW; break;

        case 10:     if (segState) pin10=HIGH; else pin10=LOW; break;
        case 11:     if (segState) pin11=HIGH; else pin11=LOW; break;
        case 12:     if (segState) pin12=HIGH; else pin12=LOW; break;
        case 13:     if (segState) pin13=HIGH; else pin13=LOW; break;
        case 14:     if (segState) pin14=HIGH; else pin14=LOW; break;
        case 15:     if (segState) pin15=HIGH; else pin15=LOW; break;
        case 16:     if (segState) pin16=HIGH; else pin16=LOW; break;
        default: break;
    }

}


void PortMode(char segPortSel){
    switch(segPortSel){
        case 1:     pin1Mode=OUTPUT; pin1=LOW;break;
        case 2:     pin2Mode=OUTPUT; pin2=LOW;break;
        case 3:     pin3Mode=OUTPUT; pin3=LOW;break;
        case 4:     pin4Mode=OUTPUT; pin4=LOW;break;
        case 5:     pin5Mode=OUTPUT; pin5=LOW;break;
        case 6:     pin6Mode=OUTPUT; pin6=LOW;break;
        case 7:     pin7Mode=OUTPUT; pin7=LOW;break;
        case 8:     pin8Mode=OUTPUT; pin8=LOW;break;
        case 9:     pin9Mode=OUTPUT; pin9=LOW;break;
        case 10:     pin10Mode=OUTPUT; pin10=LOW;break;
        case 11:     pin11Mode=OUTPUT; pin11=LOW;break;
        case 12:     pin12Mode=OUTPUT; pin12=LOW;break;
        case 13:     pin13Mode=OUTPUT; pin13=LOW;break;
        case 14:     pin14Mode=OUTPUT; pin14=LOW;break;
        case 15:     pin15Mode=OUTPUT; pin15=LOW;break;
        case 16:     pin16Mode=OUTPUT; pin16=LOW;break;
        default: break;
    }
}

//#include<stdlib.h>
