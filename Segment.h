
/*
  Programmer: AYINDE OLAYIWOLA
  Date:       24 / 5 / 2017
  Time:       09 : 36 AM
  Lab:        Mbed Studio 
  Version:    0.01

 
Example:
         int NumberOfDigit =4;
         char segmentDataPins[]= {1,2,3,4,5,6,7,8};
         char segmentScanPins[]= {9,10,11,12};

         segmentSetting(CCathode,NumberOfDigit,segmentScanPins,segmentDataPins);
         segmentWrite("4567",100);
*/




////////////////////////////////////////////////////////////
//Segment Configuration defined libary
////////////////////////////////////////////////////////////
#define  CCathode  0
#define  CAnode  1

char segScan[9],segData[9],_SC;
void segmentSetting(char segType,unsigned char segNoDigit, unsigned char *segScanA,unsigned char *segDataA){

#define Ten 0x3A
                 _SC= segType; char segLoader;
                 for(segLoader=0; segLoader<9; segLoader++) segData[segLoader]= segDataA[segLoader];
                 for(segLoader=0; segLoader<segNoDigit; segLoader++) segScan[segLoader]= segScanA[segLoader];

                 segLoader=0;
                   while(segData[segLoader]< 8)
                          PortMode(segData[segLoader++],OUTPUT);
                 segLoader=0;
                   while(segScan[segLoader]!=0)
                          PortMode(segScan[segLoader++],OUTPUT);

}


unsigned char segDispData(unsigned char segByte){
    if(_SC==CCathode){
        switch(segByte){
            case 0:   return 0x3F;
            case 1:   return 0x06;
            case 2:   return 0x5B;
            case 3:   return 0x4F;
            case 4:   return 0x66;
            case 5:   return 0x6D;
            case 6:   return 0x7D;
            case 7:   return 0x07;
            case 8:   return 0x7F;
            case 9:   return 0x6F;
            default:    return 0x3F;
        }
    }
    
    if(_SC==CAnode){
        switch(segByte){
            case 0:   return 0xC0;
            case 1:   return 0xF9;
            case 2:   return 0xA4;
            case 3:   return 0xB0;
            case 4:   return 0x99;
            case 5:   return 0x92;
            case 6:   return 0x82;
            case 7:   return 0xF8;
            case 8:   return 0x80;
            case 9:   return 0x90;
            default:  return 0xC0;
        }
    }
}


void segClear(){
    char segClrCounter=0;
    while(segScan[segClrCounter] != 0){
             if(_SC==CCathode)PinSelect(segScan[segClrCounter++],HIGH);
             if(_SC==CAnode)PinSelect(segScan[segClrCounter++],LOW);
    }
             while(segClrCounter<8)
                PinSelect(segScan[segClrCounter++],(0x00&0x01));

}




void segmentWrite(unsigned char *segDisp, unsigned long segDel){
    while(segDel-- !=0){
    char segScanpnter=0, segDatapnter=0,segStore;
        while(segScan[segScanpnter] != 0) {
            segClear();
           if(_SC==CCathode) PinSelect(segScan[segScanpnter++],LOW);
           if(_SC==CAnode) PinSelect(segScan[segScanpnter++],HIGH);
            segDatapnter=0;
            segStore= segDisp[segScanpnter-1] - 0x30;
            segStore = segDispData(segStore);
            while(segDatapnter<8) {
                PinSelect(segData[segDatapnter++],(segStore&0x01));
                segStore = segStore>>1;}
            delayMs(2);
        }
    }
    segClear();
    }