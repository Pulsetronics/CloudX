
#define lcd_clear            0x01
#define return_home      0x02
#define move_cursor_right   0x14
#define move_cursor_left    0x10
#define shift_display_right 0x1C
#define shift_display_left  0x18
#define cursor_blink        0x0F
#define cursor_off          0x0C
#define cursor_on           0x0E
#define Function_set_4bit   0x28
#define Function_set_8bit   0x38
#define Entry_mode          0x06
#define Function_8_bit      0x32

char ENN, RSS, D44, D55, D66, D77;

void lcdSettings(char RSS1,char ENN1,char D441,char D551,char D661,char D771)
{
    PortMode(RSS1,OUTPUT); PortMode(ENN1,OUTPUT); PortMode(D441,OUTPUT); PortMode(D551,OUTPUT); PortMode(D661,OUTPUT); PortMode(D771,OUTPUT);
    PORT1=0;
   RSS = RSS1; ENN= ENN1;  D44= D441; D55=D551; D66=D661; D77=D771;
    
   }
#define RS RSS
#define EN ENN
#define D4 D44
#define D5 D55
#define D6 D66
#define D7 D77



LCD_DISP(unsigned char MSB1,unsigned char LSB1){

                           PinSelect(D4, (MSB1 & 1));
                           MSB1 = MSB1 >> 1;  PinSelect(D5, (MSB1 & 1));
                           MSB1 = MSB1 >> 1; PinSelect(D6, (MSB1 & 1));
                           MSB1 = MSB1 >> 1; PinSelect(D7, (MSB1 & 1));
                           PinSelect(EN, 1); __delay_ms(2);  PinSelect(EN, 0);


                           PinSelect(D4, (LSB1 & 1));
                           LSB1 = LSB1 >> 1;  PinSelect(D5, (LSB1 & 1));
                           LSB1 = LSB1 >> 1; PinSelect(D6, (LSB1 & 1));
                           LSB1 = LSB1 >> 1; PinSelect(D7, (LSB1 & 1));
                           PinSelect(EN, 1); __delay_ms(2);  PinSelect(EN, 0);

                           }

lcdCmd(unsigned char comd){
                unsigned char MSB2 , LSB2 ;
                          PinSelect(RS, 0);
                           MSB2 = (comd & 0xF0) >> 4; LSB2 = comd & 0x0F ;
                           LCD_DISP(MSB2,LSB2);
                    }

lcdWriteCP(unsigned char chr){
                         unsigned char MSB,LSB;
                        PinSelect(RS, 1);
                         MSB = (chr & 0xF0) >> 4; LSB = chr& 0x0F ;
                          LCD_DISP(MSB,LSB);
                          }

lcdWrite(unsigned char row,unsigned char col,unsigned char chr){
                   unsigned char MSB , LSB ;
                  if(row==1) lcdCmd(0x80 + (col-1));
                  if(row==2) lcdCmd(0xC0 + (col-1));
                    if(row==3) lcdCmd(0x94 + (col-1));
                  if(row==4) lcdCmd(0xD4 + (col-1));
                  lcdWriteCP(chr);

                     }
lcdWriteTextCP(unsigned char *s){
                           unsigned char pnt=0;

                              while(s[pnt] != '\0'){
                                  lcdWriteCP(s[pnt]);
                                  pnt++;
                                 __delay_ms(2);
                                  }
                     }


lcdWriteText(unsigned char row, unsigned char col, char *s){
                        unsigned char MSB , LSB ,chr;  char pnt;
                          if(row==1) lcdCmd(0x80 + (col-1));
                          if(row==2) lcdCmd(0xC0 + (col-1));
                          if(row==3) lcdCmd(0x94 +(col-1));
                          if(row==4) lcdCmd(0xD4 + (col-1));
                                      pnt =0;
                            while(s[pnt] != '\0'){
                                  lcdWriteCP(s[pnt]);
                                  pnt++;
                          __delay_ms(2);
                                  }

}

Start_cmd(){
            lcdCmd(0x33);
            __delay_ms(1);
             lcdCmd(0x32);
            __delay_ms(1);
             lcdCmd(0x28);
            __delay_ms(1);
             lcdCmd(0x08);
            __delay_ms(1);
            lcdCmd(0x0C);
            __delay_ms(1);
            lcdCmd(0x06);
            __delay_ms(1);
}



void lcdSetting(char RSS1,char ENN1,char D441,char D551,char D661,char D771){
    lcdSettings(RSS1,ENN1,D441,D551,D661,D771);
    Start_cmd();
     }



