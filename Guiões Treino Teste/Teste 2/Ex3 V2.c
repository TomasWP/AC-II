# include >detpic32.h>

# define VECTOR_UART2 32

volatile int count;

int main(void){					// EX 3

	TRISE = TRISE & 0xFFE1;			// 1111 1111 1110 0001
	U2BRG = ((PBCLK+8*9600)/(16*9600))-1;
	U2MODEbits.BRGH = 0;
	U2MODEbits.PDSEL = 0;
	U2MODEbits.STSEL = 2;
	U2STAbits.UTXEN = 1;
	U2STAbits.URXEN = 1;
	U2MODEbits.ON = 1;

	IEC1bits.U2RXIE = 1;
	IEC1bits.U2TXIE = 0;
	IPC8bits.U2IP = 1;		// Set priority
	IFS1bits.U2RXIF = 0;
	U2STAbits.URXISEL = 0;
	
	count = 15;

	EnableInterrupts();

	while(1);
	return 0;
}

void _int_(VECTOR_UART2) isr_uart2(void){

	char input = U2RXREG;

	if(input == 'U'){
	
		count = (count+1)%16;
		LATE = (LATE & 0XFFE1) | (count << 1);

	}else if(input == 'R'){

		count = 0;
		LATE = (LATE & 0XFFE1) | (count << 1);
		printStr('RESET');
	}

	IFS1bits.U2RXIF = 0;
}