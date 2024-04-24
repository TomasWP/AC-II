# include <detpic32.h>

void setupADC(unsigned int samples);
volatile int voltage = 0; 						// Global variable 
int n_samples = 8;

int main(void) { 
    TRISB = TRISB & (0x80FF); 						// set displays as outputs 0x1000 0000 1111 1111
    TRISDbits.TRISD5 = 0; 						// set RD6-5 as outputs
    TRISDbits.TRISD6 = 0;

    PR1 = PBCLK/64/5-1;						   	// Timer 1 config
    T1CONbits.TCKPS = 2;						// Fout = 5Hz   PBCLK = 20MHz   PR1(max) = 65535
    TMR1 = 0;								// Kpresc = PBCLK/(65536*5) = 61
    T1CONbits.TON = 1;							// Kpresc = 64
									    

    IPC1bits.T1IP = 2;							// Timer 1 interrupts
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;							// Reset T1IF bit
    
    
    
									
    PR3 = PBCLK/4/100-1; 						// Timer 3 config
    T3CONbits.TCKPS = 2;    						// Fout = 100Hz   PBCLK = 20MHz   PR3(max) = 65535
    TMR3 = 0;    							// Kpresc = PBCLK/(65536*100) = 3,05
    T3CONbits.TON = 1;   						// Kpresc = 4


    IPC3bits.T3IP = 2;						    	// Timer 3 interrupts
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0; 							// Reset T3IF bit
    
    

    setupADC(n_samples);    						// ADC config

    IPC6bits.AD1IP = 2;							// ADC interrupts
    IEC1bits.AD1IE = 1;
    IFS1bits.AD1IF = 0;							// Reset AD1IF bit

    EnableInterrupts();

    while(1);

    return 0; 
} 

void setupADC(unsigned int samples) {
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = samples-1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;
}
