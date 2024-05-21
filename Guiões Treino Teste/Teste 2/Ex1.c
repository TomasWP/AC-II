#include <detpic32.h>


void setDutyCycle(unsigned int dc){

	OC2RS = ((PR2 + 1) * dc) / 100;
}

int main(void){

	TRISBbits.TRISB2 = 1;		// Configurar RB2 E RB0 como inputs
	TRISBbits.TRISB0 = 1;		// ou TRISB = TRISB | 0x0005	(xxxx xxxx xxxx xx1x1)

					// Kprescaler = (fpbclk/(65535+1)*fout)		Aula 8
					// kprescaler = (20 000 000/65536*120) = 2,543 -> logo teremos que arredondar para o numero acima, 4
					// PR3 = (fpbclk/fout/kprescaler)-1
	T3CONbits.TCKPS = 2;		// 2 pois como o kprescaler é 4 temos de arranjar uma potencia para a base 2 que de 4 2^2=4
	PR3 = PBCLK/120/4 - 1;		// PR3 = (20 000 000/120/4)-1 = 41665
	TMR3 = 0;			// valor fixo
	T3CONbits.TON = 1;		// valor fixo

	OC3CONbits.OCM = 6;		//valor fixo	Aula 8/9
	OC3CONbits.OCTSEL = 0;		//valor fixo
	setDutyCycle(75);
	OC1CONbits.ON = 1;		//valor fixo

	while(1){

		if(PORTBbits.RB2 == 0 && PORTBbits.RB0 == 0){
		
			setDutyCycle(30);

		}else if(PORTBbits.RB2 == 1 && PORTBbits.RB0 == 1){
			
			setDutyCycle(55);
		}

		resetCoreTimer();
		while(readCoreTimer()<(PBCLK/1000/1000)*360);	// 360 microsegundos
	}
	return 0;
}