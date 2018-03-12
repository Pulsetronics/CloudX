
#define backward 	0  //direction
#define forward 	1  //
#define stop 		2  //command
#define start		3  //
#define leftSide	4  // side
#define rightSide	5  //

// pin defination from CloudX controller
char PIN1,PIN2,PIN3,PIN4;

void L298Settings(char pin1,char pin2, char pin3, char pin4){
PortMode(pin1,OUTPUT);
PortMode(pin2,OUTPUT);
PortMode(pin3,OUTPUT);
PortMode(pin4,OUTPUT);

PIN1 = pin1;
PIN2 = pin2;
PIN3 = pin3;
PIN4 = pin4;
}

void L298_start(char cmd,char port,char direction){

if(cmd==start && port==leftSide && direction== forward){
PIN1=HIGH;
PIN2=LOW;
}
if(cmd==start && port==leftSide && direction== backward){
PIN1 = LOW;
PIN2 = HIGH;
}


if(cmd==start && port== rightSide && direction== forward){
PIN3=HIGH;
PIN4=LOW;
}
if(cmd==start && port== rightSide && direction== backward){
PIN3 = LOW;
PIN4 = HIGH;
}

}

void L298_stop(char port){
if(port==leftSide ){
PIN1 = LOW;
PIN2 = LOW;
}
if(port==rightSide ){
PIN3 = LOW;
PIN4 = LOW;
}
}


