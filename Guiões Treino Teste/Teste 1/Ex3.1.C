# include <detpic32.h>

int main(void){
	
	unsigned char value;
	while(1){
	      TRISB = TRISB | 0x000F;			// Configurar RB0-RB3 como input
	      TRISE = TRISE & 0xFFF0;			// Configurar RE0-RE3 como output
	      value = PORTB & 0x000F;			// ler valores
	      LATE = (LATE & 0xFFF0) | value;		// escrever valor
	}
}
