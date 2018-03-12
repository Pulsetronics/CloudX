char CLKK1,LATT1,DATT1;
void HC595_Setting(char CLKK, char DATT, char LATT){
          pinMode(CLKK);  pinMode(LATT);  pinMode(DATT);
          PORT1=0;
          CLKK1=CLKK; LATT1=LATT; DATT1=DATT;
}
#define CLK CLKK1
#define LAT LATT1
#define DAT DATT1


void HC595_shiftOut(unsigned char bytes){
    for(short cnterr=0; cnterr<8; cnterr++){
        PinSelect(DAT, (bytes & 0x01));
        PinSelect(CLK,1); __delay_ms(1);  PinSelect(CLK,0);
       bytes = bytes>>1;
    }
     PinSelect(LAT,1); __delay_ms(1);  PinSelect(LAT,0);
    
}
