#define JOYSTICK_UP 0
#define JOYSTICK_DOWN 5
#define JOYSTICK_LEFT 0
#define JOYSTICK_RIGHT 5

JOYSTICK_Y(unsigned char y){
	               if(analogRead(y) < 200) return JOYSTICK_UP;
				   else if(analogRead(y) >1000) return JOYSTICK_DOWN;
				   else return 0xFF;

}

JOYSTICK_X(unsigned char x){
	               if(analogRead(x) < 200) return JOYSTICK_LEFT;
				   else if(analogRead(x) >1000) return JOYSTICK_RIGHT;
				   else return 0xFF;
}

JOYSTICK_CENTRE(unsigned char cntre){
	   if(readPin(cntre) == LOW) return LOW;
	   else return HIGH;
}



