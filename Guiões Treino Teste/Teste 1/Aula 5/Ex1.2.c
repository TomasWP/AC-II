# include <detpic32.h>

void send2displays(unsigned char value);
void delay(int ms);

int main(void){
    TRISB = TRISB & 0x80FF;         // RB14 to RB8 as output
    TRISD = TRISD & 0xFF9F;         // Displays high/low as output

    unsigned char cont = 0;
    while (1)
    {
        cont = cont & 0xFF;         // Mask the 8 LSB from the counter
        send2displays(cont);        
        delay(200);                 // Delay 200ms -> 5Hz
        cont++;
    }
    return 0;
}

void send2displays(unsigned char value){
	
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
                           
        unsigned char dh = value >> 4;          // Get the index of the decimal part
        unsigned char dl = value & 0x0F;        // Get the index of the unitary part
        dh = display7Scode[dh];
        dl = display7Scode[dl];
        
        LATDbits.LATD6 = 1;
        LATDbits.LATD5 = 0;
        LATB = (LATB & 0X80FF) | dh << 8;       // 1000 0000 1111 1111  
        //delay(2);                             // Debug (see the first display light up slightly)
        
        LATDbits.LATD6 = 0;
        LATDbits.LATD5 = 1; 
        LATB = (LATB & 0X80FF) | dl << 8;
}

void delay(int ms){

	while(ms > 0){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
		ms--;
	}
}
