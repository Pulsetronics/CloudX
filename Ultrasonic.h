      /* This code is written by Ayinde Olayiowla
	     05- 02 -18
		written under the license of ByteHub Embedded at mbed studio lab
        Users of the library should take permission for using this code at
        request@ByteHubEmbedded@gmail.com
      
        This code is written as a opensource library for CloudX microcontroller

      */		
	
 char triggg,echooo;	
void ultrasonic_Init(unsigned char trigg, unsigned char echoo){
                        	T1CON = 0x10;
                            PortMode(trigg,OUTPUT);
							PortMode(echoo,INPUT);
							triggg = trigg; echooo = echoo;
							
}

#define trig triggg
#define echo echooo

float readDistance(){
	     
             TMR1H = 0;
             TMR1L = 0;
             PinSelect(trig,HIGH);
             delayUs(10);
             PinSelect(trig,LOW);
 
             while(!readPin(echo));
             T1CONbits.TMR1ON = 1;
             while(readPin(echo));
             T1CONbits.TMR1ON = 0;
            
            return ((TMR1L | (TMR1H<<8))/58.82 - 10);
         }