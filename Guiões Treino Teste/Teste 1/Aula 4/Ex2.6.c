# include <detpic32.h>

int main(void){

    	static const char display7Scode[] = {	0x3F, //0
                                        	0x06, //1
		                                0x5B, //2
		                                0x4F, //3
		                                0x66, //4
		                                0x6D, //5
		                                0x7D, //6
		                                0x07, //7
		                                0x7F, //8
		                                0x6F, //9
		                                0x77, //A
		                                0x7C, //b
		                                0x39, //C
		                                0x5E, //d
		                                0x79, //E
		                                0x71  //F
                                    		};
	TRISB = TRISB | 0x000F;		// Configure RB0-RB3 as input 0000 0000 0000 1111
	TRISB = TRISB & 0x80FF;		// Configure RB8-RB14 as output 1000 0000 1111 1111
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	LATDbits.LATD6 = 1;
	LATDbits.LATD5 = 0;
	int index;
	int value;
	
	while(1){
		index = PORTB & 0x000F;
		value = display7Scode[index];
		LATB = (LATB & 0x80FF) | value << 8;
	}
	return 0;
}
