#include <detpic32.h>

void setDutyCycle(unsigned int dc){

	OC2RS = ((PR3+1)*dc)/100;
}

int main(void){					// EX 1

	TRISB = TRISB | 0x0005;			// configure RB0 and RB2 xxxx xxxx xxxx 0101

						// kprescaler = PBCLK/65536*120 = 2,5 -> 4
	T3CONbits.TCKPS = 2;			// 4(2^2)	
	PR3 = PBCLK/4/120-1;			// PR3 = (PBCLK/fout)-kprescaler
	TMR3 = 0;
	T3CONbits.TON = 1;
	OC3CONbits.OCM = 6;
	OC3CONbits.OCTSEL = 0;
	OC3CONbits.ON = 1;

	setDutyCycle(75);

	while(1){

		if (PORTBbits.RB0 == 0 && PORTbits.RB2 == 0){

			setDutyCycle(30);
		}else if(PORTbits.RB0 == 1 && PORTbits.RB2 == 1){
		
			setDutyCycle(55);
		}

		resetCoreTimer();
		while(readCoreTimer()<PBCLK/1000/1000/360);

		return 0;
	}
}