#include <detpic32.h>

int main(void){

	TRISBbits.TRISB4 = 1;		// RB4 digital output disconnected
	AD1PCFGbits.PCFG4 = 0;		// Configure RB4 as analog Input (AN4)

	// Block of code always the same changing only values from samples and the analog input
	AD1CON1bits.SSRC = 7;		// Always the same code
	AD1CON1bits.CLRASAM = 1;	// Always the same code
	AD1CON3bits.SAMC = 16;		// Always the same code
	AD1CHSbits.CH0SA = 4;		// Always the same code only change value o to 15(Select AN4 as input for the A/D converter)
	AD1CON2bits.SMPI = 0;		// Always the same code only change value N-1(1 sample will be converted and stored)
	AD1CON1bits.ON = 1;		// Always the same code (Enable A/D Converter)

	while(1){
		AD1CON1bits.ASAM = 1;		// Start A/D Conversion
		while (IFS1bits.AD1IF == 0);	// Wait while conversion not done
		printInt(ADC1BUF0, 16 |3 << 16);	// Read conversion result (ABC1BUF0 value) and print it
		putChar('\r');
		IFS1bits.AD1IF = 0;		// Reset AD1IF bit
	}
	return 0;
}
