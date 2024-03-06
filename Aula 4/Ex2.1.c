#include <detpic32.h>

int main(void){

	TRISB = TRISB & 0x80FF;	// Configurar portos RB14-RB8 como saida (1000 0000 1111 1111)
	TRISD = TRISD & 0xFF9F; // Configurar portos RD5, RD6 como saidas (1111 1111 1001 1111)
	LATDbits.LATD5 = 1;	// Configurar qual display está ON(CNTL_DISP_L = 1)
	LATDbits.LATD6 = 0;
	while(1){
		do{
			char input = getchar();
		}while(input > 'g' || input < 'a');
