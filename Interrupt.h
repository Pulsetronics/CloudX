Timer0Calculator(double timerrss){
    TMR0 = 268 - (int)((timerrss*5000000)/256);
}


void TimerZeroEnable(){
          INTCONbits.GIE  =1;
          INTCONbits.T0IE =1;
          OPTION_REG=0x07;
          TMR0 = 0;
}

void TimerZeroDisable(){
          INTCONbits.GIE  =0;
          INTCONbits.T0IE =0;
          OPTION_REG=0x07;
          TMR0 = 0;
}

