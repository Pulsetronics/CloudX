#define   OK 0



void serialBegin(unsigned long baudd){
    SPBRG = (_XTAL_FREQ - (baudd*16)) / (baudd*16);
    TXSTA = 0x24;
    RCSTA = 0x90;
   
}

void serialWrite(unsigned char SerTx)
{
    TXSTAbits.TXEN =1;
    TXREG = SerTx;
    delayMs(5);
}

void serialWriteText(unsigned char *Sertxxt){
    unsigned char pnttter=0;
    while(Sertxxt[pnttter] != 0)
        serialWrite(Sertxxt[pnttter++]);
}

unsigned char serialRead(){
     RCSTAbits.CREN =1;
     PIR1bits.RCIF=0;
    return RCREG;
}


unsigned char serialAvailable(){
    RCSTAbits.CREN =1;
   /*
    *  if(PIR1bits.RCIF) return OK;
    else return 1;
    */
    return PIR1bits.RCIF;
}