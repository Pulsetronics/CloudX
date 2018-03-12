readMemory(unsigned char RIM){
    EEADR = RIM;
    EECON1bits.EEPGD =0;
    EECON1bits.RD =1;
    return EEDATA ;
}

writeMemory(unsigned char WIMADDR, unsigned char WIMDATA){
    while(EECON1bits.WR==1);
    EEADR = WIMADDR;
    EEDATA = WIMDATA;
    EECON1bits.EEPGD =0;
    EECON1bits.WREN =1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR =1;
    EECON1bits.WREN =0;
}