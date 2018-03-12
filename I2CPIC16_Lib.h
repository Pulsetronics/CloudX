
MSSPWait(){
    while(!PIR1bits.SSPIF);
           PIR1bits.SSPIF=0;
}

void I2C_Start(){
    SSPCON2bits.SEN=1;
    while(SSPSTATbits.S==0);
    MSSPWait();
}

void I2C_Stop(){
    SSPCON2bits.PEN=1;
    while(SSPSTATbits.P==0);
    MSSPWait();
}

void I2C_Wr(unsigned char addressbyte){
           SSPBUF = addressbyte;
           MSSPWait();
           while(SSPCON2bits.ACKSTAT);
}

I2C_INIT(unsigned long I2C_BAUD){
    SSPCONbits.WCOL=0;
    SSPCONbits.SSPEN=1;
    SSPCONbits.SSPM3=1;
    SSPCONbits.SSPM2=0;
    SSPCONbits.SSPM1=0;
    SSPCONbits.SSPM0=0;
    SSPSTATbits.SMP=1;
    SSPADD = (_XTAL_FREQ / (4 * I2C_BAUD)) - 1;
	}