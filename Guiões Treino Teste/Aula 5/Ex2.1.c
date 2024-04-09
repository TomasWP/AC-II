# include <detpic32.h>

void send2displays(unsigned char value);
void delay(int ms);
unsigned char toBcd(unsigned char value);

int main(void){
	
	int i;
	unsigned char counter = 0;
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;         // Displays high/low as output
	TRISB = TRISB | 0x0001;         // Configure RB0 as input
	
	while(1){
		int up_down = PORTB & 0x0001;
		i = 0;
		do{
			send2displays(toBcd(counter));
			LATE = (LATE & 0xFF00) | counter;
			delay(10);       // Should be 20 but still flickers, not with 10
		}while(++i < 50);        // Counter frequency
                                         // ms = 1/2Hz = 0,5s = 500ms
                                         // 500ms/10ms = 50
                                         
                if (up_down == 1){
                        if (--counter == 0){
		              counter = 59;   
		        }
	        }else if(up_down == 0){
		        if (++counter == 60){
		              counter = 0;
		        }
		}
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
        
        static char displayFlag = 0;
        
        unsigned char dh = value >> 4;          // Get the index of the decimal part
        unsigned char dl = value & 0x0F;        // Get the index of the unitary part
        dh = display7Scode[dh];
        dl = display7Scode[dl];
        
        if(displayFlag == 0){
                LATDbits.LATD6 = 0;
		LATDbits.LATD5 = 1; 
		LATB = (LATB & 0X80FF) | dl << 8;
	}else{
		LATDbits.LATD6 = 1;
		LATDbits.LATD5 = 0;
		LATB = (LATB & 0X80FF) | dh << 8;       // 1000 0000 1111 1111  
	}
	displayFlag = !displayFlag;
}

void delay(int ms){

      resetCoreTimer();
      while(readCoreTimer() < 20000 * ms);
}

 unsigned char toBcd(unsigned char value) 
 { 
 return ((value / 10) << 4) + (value % 10); 
 } 
