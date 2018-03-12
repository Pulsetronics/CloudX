#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7


void analogSetting(){
    ADCON0 = 0x81;
    ADCON1 = 0x00;
}

unsigned int analogRead(unsigned char channel){
    int aadc,bbdc, ccdc;
    if(channel>7)return 0;
    ADCON0 = ADCON0 & 0xC5;
    ADCON0 = ADCON0 | (channel << 3);
    __delay_ms(2);
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE);
    aadc = ADRESH;
    aadc = aadc<<2;
    bbdc = ADRESL;
    bbdc = bbdc >>6;
    ccdc = aadc|bbdc;
    return ccdc;

}