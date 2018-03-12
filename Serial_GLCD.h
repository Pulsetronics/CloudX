
#define Ser_CLEAR 0x00
#define Ser_RST  0x01
#define Ser_EN   0x02
#define Ser_RW   0x04
#define Ser_RS  0x08
#define Ser_CS2   0x10
#define Ser_CS1  0x20

#define Clear 0x00
#define Set   0x01

unsigned char PortAx=0, PortBx=0;
void Init_74HC595(){
          Tris_SerDat=0;
          Tris_SerClk=0;
          Tris_SerLat=0;
          SerDat =0;
          SerClk =0;
          SerLat =0;
}
void Serial_Port(){
    unsigned char ShiftCounter,ShiftA =PortAx,ShiftB=PortBx;
    for(ShiftCounter=0; ShiftCounter<8; ShiftCounter++){
         SerDat=  (ShiftA  &0x80)>>7;
         ShiftA = ShiftA <<1;
         SerClk=1;  SerClk=0;
    }
    for(ShiftCounter=0; ShiftCounter<8; ShiftCounter++){
         SerDat=  (ShiftB &0x80)>>7;
         ShiftB = ShiftB<<1;
         SerClk=1;  SerClk=0;
    }
    SerLat=1; SerLat=0;

}

void Serial_GLCD_ENABLE()
{
     PortAx |= Ser_EN;
     Serial_Port();
   // __delay_us(1);
    PortAx &=~Ser_EN;
   // __delay_us(1);
    Serial_Port();
}

void Serial_GLCD_DISPLAY_ON(void){
    PortAx |= Ser_CS1; PortAx |=Ser_CS2;
    PortAx &=~Ser_RS;
    PortAx &=~Ser_RW;
    PortBx =  0x3F;
  //  Serial_Port();
    Serial_GLCD_ENABLE();
    PortBx=0;
   // Serial_Port();
}


void GLCD_START_ROW(unsigned char row){
    PortAx &=~Ser_RS;
    PortAx &=~Ser_RW;
    PortBx= (0xB8 | row);
   // Serial_Port();
    Serial_GLCD_ENABLE();
    PortBx=0x00;
  //  Serial_Port();

}

void Serial_CLEAR_CMD(){
   PortAx &=~Ser_CS1; PortAx &=~Ser_CS2;
     PortAx &=~Ser_RS;
    PortAx &=~Ser_RW;
   PortBx = 0xC0;
  //Serial_Port();
    Serial_GLCD_ENABLE();
    PortBx=0x00;
   // Serial_Port();

}
void GLCD_START_ROW_LINE(unsigned char row){
    PortAx &=~Ser_RS;
    PortAx &=~Ser_RW;
    PortBx = (0xC0 | row);
    Serial_GLCD_ENABLE();
    PortBx=0x00;
 

}



void GLCD_START_COL(unsigned char col){
     PortAx &= ~Ser_RS;
     PortAx &= ~Ser_RW;
    if(col < 64){
        PortAx &= ~Ser_CS1;
        PortAx |= Ser_CS2;
    }
    else {
        PortAx |=  Ser_CS1;
        PortAx &= ~Ser_CS2;
        col = col-64;
    }
    PortBx =(col | 0x40);
    Serial_GLCD_ENABLE();
     PortBx=0x00;
}


void Serial_GLCD_Write(char row1,unsigned char col1,unsigned char chr,char levell){

    if(col1>128);
    else{ GLCD_START_COL(col1);
    switch (levell)
    {
        case 0:  GLCD_START_ROW_LINE(row1); break;
        case 1:  GLCD_START_ROW(row1);      break;
    }

    PortAx |= Ser_RS;
    PortAx &= ~Ser_RW;
    PortBx=  chr;
  //  Serial_Port();
    Serial_GLCD_ENABLE();
    }
    PortBx=0x00;
    //Serial_Port();
}

void Serial_GLCD_FILL_ALL(unsigned char clr){
    unsigned char x=0,y=0;
 //   Serial_CLEAR_CMD();
    for(y=0; y<8; y++){
          Serial_GLCD_Write(y,0,clr,1);
        for(x=0; x<128; x++)
            Serial_GLCD_Write(y,x,clr,1);
    }
}

void Serial_xGLCD_WRITE_CHAR(const unsigned short *table1, unsigned char FontLength, char FontHeight, char roww, char coll, unsigned char chrr, char dispTyper){
     unsigned char pos_x=0, ByteChar=0,TempRow;
     unsigned int YFontHeight, XFontLength,xFont;
     // ByteChar = FONT_5x7[((chrr - 0x20)*width) + pos_x];
    // xFont =  ((FontLength/8)+1);
     xFont = (FontHeight/8)+1;
           FontLength = FontLength * xFont;
           XFontLength = table1[(chrr - 0x20)* (FontLength+1)];  //length of font
            while(pos_x<(XFontLength*xFont)){
                TempRow = roww;
                 YFontHeight = FontHeight/8;  //height of Font
           YFontHeight= YFontHeight+1;
    while (YFontHeight--!=0){
           ByteChar = table1[((chrr - 0x20)* (FontLength+1)) + ++pos_x];
        switch(dispTyper){
            case Clear: ByteChar= ~ByteChar; break;
            case Set:   ByteChar = ByteChar;  break;
        }
        Serial_GLCD_Write(TempRow++,coll, ByteChar,1);
    }
                coll++;
}

}


void Serial_GLCD_WRITE_CHAR(const unsigned short *table1, unsigned char width, char length, char roww, char coll, unsigned char chrr, char dispTyper)
{
     unsigned char pos_x=0, ByteChar=0;
     // ByteChar = FONT_5x7[((chrr - 0x20)*width) + pos_x];
    while(pos_x<width){
      //  ByteChar = table1[chrr - 0x20][pos_x];
         ByteChar = table1[((chrr - 0x20)*width) + pos_x];
        switch(dispTyper){
            case Clear: ByteChar= ~ByteChar; break;
            case Set:   ByteChar = ByteChar;  break;
        }
        Serial_GLCD_Write(roww,coll+pos_x++, ByteChar,1);
    }
}

void Serial_GLCD_FILL(unsigned char clr,unsigned char page,unsigned char FromX, unsigned char toX ){
         Serial_CLEAR_CMD();
          while(FromX<toX)
            Serial_GLCD_Write(page,FromX++,clr,1);

}

void Serial_GLCD_Init(){
           Init_74HC595();
           PortAx |= Ser_RST;
           Serial_Port();
       Serial_GLCD_DISPLAY_ON();
       Serial_GLCD_FILL_ALL(0);
}

void Serial_GLCD_WRITE_TEXT(const unsigned short *table1, unsigned char width, char length, unsigned row, unsigned col,unsigned char *txt, char dispType)
{
    unsigned char pnt=0;
            while (txt[pnt] != '\0') {

               Serial_GLCD_WRITE_CHAR(table1, width, length, row,col,txt[pnt++], dispType);
            col = col + width+1;
            }
}

void Serial_xGLCD_WRITE_TEXT(const unsigned short *table1, unsigned char width, char length, unsigned row, unsigned col,unsigned char *txt, char dispType)
{                  unsigned char LineSpacing;
    unsigned char pnt=0;
            while (txt[pnt] != '\0') {
            Serial_xGLCD_WRITE_CHAR(table1, width, length, row,col,txt[pnt], dispType);
            LineSpacing = table1[(txt[pnt++] - 0x20)* ((width*((length/8)+1))+1)];
            col = col+LineSpacing+2;
            }
}



void Serial_GLCD_WRITE_DATA_CHAR(const unsigned short *table1, unsigned char width, char length, char roww, char coll, unsigned char chrr, char dispTyper)
{
     unsigned char pos_x=0, ByteChar=0;
     // ByteChar = FONT_5x7[((chrr - 0x20)*width) + pos_x];
    while(pos_x<width){
      //  ByteChar = table1[chrr - 0x20][pos_x];
         ByteChar = table1[((chrr - 0x20)*width) + pos_x];
        switch(dispTyper){
            case Clear: ByteChar= ~ByteChar; break;
            case Set:   ByteChar = ByteChar;  break;
        }
        Serial_GLCD_Write((63-roww),coll+pos_x++, ByteChar,0);
    }
}


void Serial_GLCD_WRITE_DATA_TEXT(const unsigned short *table1, unsigned char width, char length, unsigned char row, unsigned char col,unsigned char *txt, char dispType)
{
    unsigned char pnt=0;
            while (txt[pnt] != '\0') {
                 
                   Serial_GLCD_WRITE_DATA_CHAR(table1, width, length, row,col,txt[pnt++], dispType);
            col = col + width+1;
            }
}

void Serial_GLCD_IMAGE_WRITE(const char *ImgWr,unsigned int ImgWrLength, unsigned int ImgWrHeight, unsigned int posX,unsigned int posY){
        unsigned int ImageXPnter=posX,ImageYPnter=posY,ImageCounter=0,PickerX=0,PickerY=0;

           while(ImageCounter < (((ImgWrHeight/8)+1)*ImgWrLength)) {
           Serial_GLCD_Write(ImageYPnter,ImageXPnter,ImgWr[(ImgWrLength*PickerY) + PickerX++],1);
        ImageXPnter++; ImageCounter++;
          if(ImageXPnter>=(ImgWrLength + posX)){
            ImageYPnter++; PickerY++;
           ImageXPnter=posX; PickerX=0;
        }

      }
}

void Serial_GLCD_IMAGE(const char *image){
    unsigned int ImagePnter=0,ImageYPnter=0,ImageCounter=0;
    while(ImageCounter < 1024) {
        Serial_GLCD_Write(ImageYPnter,ImagePnter,image[(128*ImageYPnter) + ImagePnter],1);
        ImagePnter++; ImageCounter++;
          if(ImagePnter>=128){
            ImageYPnter++;
           ImagePnter=0;
        }
    }
}


void Serial_GLCD_CLEAR(){
    unsigned int ImagePnter=0,ImageYPnter=0,ImageCounter=0;
    while(ImageCounter < 1024) {
        Serial_GLCD_Write(ImageYPnter,ImagePnter,0,1);
        ImagePnter++; ImageCounter++;
          if(ImagePnter>=128){
            ImageYPnter++;
           ImagePnter=0;
        }
    }
}