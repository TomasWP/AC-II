#include <detpic32.h>

void delay(int ms)
{
	resetCoreTimer();
	while (readCoreTimer() < (20000 * ms));
}

void send2displays(unsigned char value)
{
	static const char display7Scodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

	static char select_display = 0;

	if (select_display == 1) {

		LATDbits.LATD6 = 1;
		LATDbits.LATD5 = 0;		// LATD = (LATD & 0xFF9F) | 0xFFDF;
		LATB = (LATB & 0x80FF) | (display7Scodes[(value >> 4)] << 8);	// <<8 -> mover bits para posicao de RB desejada
		select_display = 0;
	} else {
		LATDbits.LATD6 = 0;
		LATDbits.LATD5 = 1;		//LATD = (LATD & 0xFF9F) | 0xFFBF;
		LATB = (LATB & 0x80FF) | (display7Scodes[(value & 0x0F)] << 8);
		select_display = 1;
}
}

int main(void){

	TRISB = TRISB & 0x80FF;		// selecionar de RB8 a RB14 como output
	TRISD = TRISD & 0xFF9F;		// selecionar RD5 E RD6 como output

	int counter = 0;
	while(1){
		int i = 0;
		do{
			send2displays(counter);
			delay(10);
		}while(++i < 10);

		delay(10);
		counter++;
		if (counter == 256){
			counter = 0;
		}
	}
}
