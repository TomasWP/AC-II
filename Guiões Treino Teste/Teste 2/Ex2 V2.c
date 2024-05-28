#include <detpic32.h>

#define ADCsamples 2
#define VECTOR_ADC, 12

volatile int temp;

void delay(int ms){
	
	resetCoreTimer();
	while(readCoreTimer()<20000*ms);
}

void send2displays(unsigned char value){
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

int main(void){					// EX 2

	// Configure Analogic

	TRISBbits.TRISB4 = 1;			// disconnect
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC =7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON2BITS.SMPI = ADCsamples - 1;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;

	// Configure Displays
	
	TRISB = TRISB &	0x80FF;			// 1000 0000 1111 1111

	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	// Configure Timers

						// kprescaler = PBCLK/65536*140 = 2,17 -> 4
	T3CONbits.TCKPS = 2;			// 4(2^2)
	PR3 = (PBCLK/4/140)-1			// PR3 = PBCLK/kprescaler/fout - 1
	TMR3 = 0;				
	T3CONbits.TON = 1	
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;

	EnableInterrupts();	

	temp = 0;	
	
	while(1){
	
		AD1CON1bits.ASAM = 1;
		while(IFS1bits.AD1IF == 0);

				int i, media = 0;
                int *buf = (int *)(&ADC1BUF0);
                for (i = 0; i < ADCsamples; i++) {
                        media += buf[i * 4];
                }
                media = media / ADCsamples;
                temp = ((media * 65 + 511) / 1023) + 10;	// 75 valor max(75-valor min = 65), 10 valor min
		
		IFS1bits.AD1IF = 0;
		delay(200);			// (1/5)*1000= 0,2*1000 = 200
	}
	return 0;
}

void_int_(VECTOR_ADC) isr_T3(void){
	
	send2displays(temp);
	IFS0bits.T3IF = 0;
}

		