#include <detpic32.h>

#define ADCsamples 2

volatile int temp;

void delay(int ms){

	resetCoreTimer();
	while(readCoreTimer()<20000*ms);
}

void send2displays(unsigned char value) {
        const char codes[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

        static int flag = 0;

        if (flag) {
                LATD = (LATD & 0xFF9F) | 0x0040;
                LATB = (LATB & 0x80FF) | (codes[value / 10] << 8);
                flag = 0;
        } else {
                LATD = (LATD & 0xFF9F) | 0x0020;
                LATB = (LATB & 0x80FF) | (codes[value % 10] << 8);
                flag = 1;
        }
}

int main(void){

	// Configure ADC - Aula 6

	TRISBbits.TRISB4 = 1;		// RB4 digital output disconnected	
	AD1PCFGbits.PCFG4 = 0;		// RB4 configures as analog input
	AD1CON1bits.SSRC = 7;		// Valor fixo
	AD1CON1bits.CLRASAM = 1;	// Valor fixo
	AD1CON3bits.SAMC = 16;		// Valor fixo
	AD1CON2bits.SMPI = ADCsamples-1;		// number of samples-1
	AD1CHSbits.CH0SA = 4;		// input analog channel
	AD1CON1bits.ON = 1;		// Valor fixo

	//Configure Displays

	TRISB= TRISB & 0x80FF;		// Configure RD8-RD14 as output(1000 0000 1111 1111)
	TRISDbits.TRISD5 = 0;		// both displays on (RD6 & RD5)
	TRISDbits.TRISD6 = 0;

	//Configure Timer 3

					// Kprescaler = (fpbclk/(65535+1)*fout)		Aula 8
					// kprescaler = (20 000 000/65536*140) = 2,179 -> logo teremos que arredondar para o numero acima, 4
					// PR3 = (fpbclk/fout/kprescaler)-1
	T3CONbits.TCKPS = 2;		// 2 pois como o kprescaler é 4 temos de arranjar uma potencia para a base 2 que de 4 2^2=4
	PR3 = PBCLK/140/4 - 1;		// PR3 = (20 000 000/120/4)-1 = 41665
	TMR3 = 0;			// valor fixo
	T3CONbits.TON = 1;		// valor fixo

    	IPC3bits.T3IP = 2;		// Timer 1 interrupts
    	IEC0bits.T3IE = 1;
    	IFS0bits.T3IF = 0;		// Reset T1IF bit

	EnableInterrupts();

	temp = 0;

	while(1){

		AD1CON1bits.ASAM = 1;  // Start conversion 

		while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done 

		int i, media = 0;
                int *buf = (int *)(&ADC1BUF0);
                for (i = 0; i < ADCsamples; i++) {
                        media += buf[i * 4];
                }
                media = media / ADCsamples;
                temp = ((media * 65 + 511) / 1023) + 10;	// 75 valor max(75-valor min = 65), 10 valor min
                IFS1bits.AD1IF = 0;
                delay(200);					// delay de 5Hz (1/5Hz * 1000 = 200)
	}
	return 0;
}

void _int_(12) isr_T3(void) {
        send2displays(temp);
        IFS0bits.T3IF = 0;
}