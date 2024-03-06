#include <detpic32.h>

void delay(int ms);

int main(void){

	TRISCbits.TRISC14 = 0;	// Configure port RC14 as output
	LATCbits.LATC14 = 0;	// Output value as 0
	while (1){
		delay(500);	// Wait 0.5s (freq = 2Hz)
		LATCbits.LATC14 = !LATCbits.LATC14;	// Toggle RC14 port value
	}
	return 0;
}

void delay(int ms){

	while (ms>0){
		resetCoreTimer();
		while(readCoreTimer () < 20000);
		ms--;
	}
}
