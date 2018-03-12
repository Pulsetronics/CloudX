/***************************************************************************************************
                                   ByteHub Embedded
****************************************************************************************************
 * File:   I2C.h
 * Version: 1.0
 * Author: Ayinde Olayiwola
 * Website: http://www.makeelectronics.ng or http://www.bytehubembedd.com
 * Description: This file contains the program to demonstrate the LED blinking. 

This code has been developed and tested on CloudX microcontroller boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.makeelectronics.ng for awesome tutorials on CloudX,ARM,Robotics,RTOS,IOT.
ByteHub Embedded invests substantial time and effort developing open source HW and SW tools,
to support consider buying the CloudX microcontroller boards.
 
The ByteHub Embedded libraries and examples are licensed under the terms of the new-bsd license
(two-clause bsd license). See also: http://www.opensource.org/licenses/bsd-license.php

BYTEHUB EMEBEDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE 
INFORMATION RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/


MSSPWait(){
    while(!PIR1bits.SSPIF);
           PIR1bits.SSPIF=0;
}

void I2C_Start(){
    SSPCON2bits.SEN=1;
    while(SSPSTATbits.S==0);
    MSSPWait();
}

void I2C_Repeated_Start(){
    SSPCON2bits.RSEN=1;
    while(SSPSTATbits.S==0);
    MSSPWait();
}

void I2C_Stop(){
    SSPCON2bits.PEN=1;
    while(SSPSTATbits.P==0);
    MSSPWait();
}

void I2C_Write(unsigned char addressbyte){
           SSPBUF = addressbyte;
           MSSPWait();
           while(SSPCON2bits.ACKSTAT);
}

I2C_begin(unsigned long I2C_BAUD){
    SSPCONbits.WCOL=0;
    SSPCONbits.SSPEN=1;
    SSPCONbits.SSPM3=1;
    SSPCONbits.SSPM2=0;
    SSPCONbits.SSPM1=0;
    SSPCONbits.SSPM0=0;
    SSPSTATbits.SMP=1;
    SSPADD = (_XTAL_FREQ / (4 * I2C_BAUD)) - 1;
	}