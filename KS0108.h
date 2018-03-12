#define Clear 0
#define Set 1
#define Invert 2

void GLCD_ENABLE()
{
    EN=1;
    __delay_us(1);
    EN=0;
    __delay_us(1);
}


void GLCD_START_ROW(unsigned char row){
    RS = 0;
    RW = 0;
    DataLine |= (0xB8 | row);
    GLCD_ENABLE();
      DataLine &=0xFF00;

}

void CLEAR_CMD(){
    CS1=0; CS2=0;
     RS = 0;
     RW = 0;
    DataLine |= 0xC0;
    GLCD_ENABLE();
      DataLine &=0xFF00;

}
void GLCD_START_ROW_LINE(unsigned char row){
    RS = 0;
    RW = 0;
    DataLine |= (0xC0 | row);
    GLCD_ENABLE();
    DataLine &=0xFF00;

}



void GLCD_START_COL(unsigned char col){
    RS=0;
    RW=0;
    if(col < 64){
        CS1=0;
        CS2=1;
    }
    else {
        CS1=1;
        CS2=0;
        col = col-64;
    }
    DataLine |= (col | 0x40);
    GLCD_ENABLE();
      DataLine &=0xFF00;

}

void GLCD_WRITE(char row1,unsigned char col1,unsigned char chr,char levell){

    if(col1>128);
    else{ GLCD_START_COL(col1);
    switch (levell)
    {
        case 0:  GLCD_START_ROW_LINE(row1); break;
        case 1:  GLCD_START_ROW(row1);      break;
    }
    
    RS=1;
    RW=0;
    DataLine |=  chr;
    GLCD_ENABLE();
    }
    DataLine &=0xFF00;
   
}


void xGLCD_WRITE_CHAR(const unsigned short *table1, unsigned char FontLength, char FontHeight, char roww, char coll, unsigned char chrr, char dispTyper){
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
        GLCD_WRITE(TempRow++,coll, ByteChar,1);
    }
                coll++;
}
           
}

void xGLCD_WRITE_TEXT(const unsigned short *table1, unsigned char width, char length, unsigned row, unsigned col,unsigned char *txt, char dispType)
{                  unsigned char LineSpacing;
    unsigned char pnt=0;
            while (txt[pnt] != '\0') {
            xGLCD_WRITE_CHAR(table1, width, length, row,col,txt[pnt], dispType);
            LineSpacing = table1[(txt[pnt++] - 0x20)* ((width*((length/8)+1))+1)];
            col = col+LineSpacing+2;
            }
}





void GLCD_WRITE_CHAR(const unsigned short *table1, unsigned char width, char length, char roww, char coll, unsigned char chrr, char dispTyper)
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
        GLCD_WRITE(roww,coll+pos_x++, ByteChar,1);
    }
}

void GLCD_WRITE_DATA_CHAR(const unsigned short *table1, unsigned char width, char length, char roww, char coll, unsigned char chrr, char dispTyper)
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
        GLCD_WRITE((63-roww),coll+pos_x++, ByteChar,0);
    }
}


void GLCD_WRITE_TEXT(const unsigned short *table1, unsigned char width, char length, unsigned row, unsigned col,unsigned char *txt, char dispType)
{
    unsigned char pnt=0;
            while (txt[pnt] != '\0') {
           
               GLCD_WRITE_CHAR(table1, width, length, row,col,txt[pnt++], dispType);
            col = col + width+1;
            }
}

void GLCD_WRITE_DATA_TEXT(const unsigned short *table1, unsigned char width, char length, unsigned char row, unsigned char col,unsigned char *txt, char dispType)
{
    unsigned char pnt=0;
            while (txt[pnt] != '\0') {
                 
                   GLCD_WRITE_DATA_CHAR(table1, width, length, row,col,txt[pnt++], dispType);
            col = col + width+1;
            }
}



void GLCD_DISPLAY_ON(void){
    CS1= 1; CS2=1;
    RS = 0;
    RW = 0;
    DataLine |=  0x3F;
    GLCD_ENABLE();
    DataLine &=0xFF00;
}


void GLCD_FILL_ALL(unsigned char clr){
    unsigned char x=0,y=0;
    CLEAR_CMD();
    for(y=0; y<8; y++){
          GLCD_WRITE(y,0,clr,1);
        for(x=0; x<128; x++)
            GLCD_WRITE(y,x,clr,1);
    }
}

void GLCD_FILL(unsigned char clr,unsigned char page,unsigned char FromX, unsigned char toX ){
         CLEAR_CMD();
          while(FromX<toX)
            GLCD_WRITE(page,FromX++,clr,1);
    
}

void DrawRectangle(char FromX, char FromY, char toX,char  toY){
    unsigned char x,y;
    for(y=FromY; y<toY; y++){
        for(x=FromX; x<toX; x++){
             GLCD_WRITE(y,x,0x40,0);
        }
    }
}

void GLCD_IMAGE(const char *image){
    unsigned int ImagePnter=0,ImageYPnter=0,ImageCounter=0;
    while(ImageCounter < 1024) {
        GLCD_WRITE(ImageYPnter,ImagePnter,image[(128*ImageYPnter) + ImagePnter],1);
        ImagePnter++; ImageCounter++;
          if(ImagePnter>=128){
            ImageYPnter++;
           ImagePnter=0;
        }
    }
    
}
void GLCD_INIT(){
	   TRISDataLine =0x00;
	   DataLine=0;
       RST =1;
       GLCD_DISPLAY_ON();
       GLCD_FILL_ALL(0);
}


void GLCD_IMAGE_WRITE(const char *ImgWr,unsigned int ImgWrLength, unsigned int ImgWrHeight, unsigned int posX,unsigned int posY){
        unsigned int ImageXPnter=posX,ImageYPnter=posY,ImageCounter=0,PickerX=0,PickerY=0;

           while(ImageCounter < (((ImgWrHeight/8)+1)*ImgWrLength)) {
           GLCD_WRITE(ImageYPnter,ImageXPnter,ImgWr[(ImgWrLength*PickerY) + PickerX++],1);
        ImageXPnter++; ImageCounter++;
          if(ImageXPnter>=(ImgWrLength + posX)){
            ImageYPnter++; PickerY++;
           ImageXPnter=posX; PickerX=0;
        }

      }
}
