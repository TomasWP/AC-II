# include <detpic32.h>

int main(void){

	// Configure UART2:
	
	// 1 - Configure BaudRate Generator
	
	U2BRG = ((PBCLK+8*115200)/(16*115200))-1;
	U2MODEbits.BRGH = 0;				// Divide by 16
	
	// 2 - Configure number of data bits, parity and number of stop bits (see U2MODE register)
	
	U2MODEbits.PDSEL = 0;				// 8 bits without parity
	U2MODEbits.STSEL = 0;				// 1 stop bit	
	
	// 3 - Enable the transmitter and receiver modules (see register U2STA)
	
	U2STAbits.UTXEN = 1;				// Disable transmission module
	U2STAbits.URXEN = 1;				// Enable receiver module
	
	// 4 - Enable UART2 (see register U2MODE)
	
	U2MODEbits.ON = 1;
	
	
	// Configure UART2 interrupts, with RX interrupts enabled and TX interrupts disabled
	
	IEC1bits.U2RXIE = 1;
	IEC1bits.U2TXIE = 0;
	IPC8bits.U2IP = 1;		// Set priority
	IFS1bits.U2RXIF = 0;
	U2STAbits.URXISEL = 0;
	
	EnableInterrupts();
	
	while(1);
	return 0;
}
