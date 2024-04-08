# include <detpic32.h>

int main(void){

	TRISB = TRISB & 0x80FF;		// Configurar RB8-RB14 como output (1000 0000 1111 1111)
	TRISDbits.TRISD5 = 0;		// Configurar RD5 como output
	TRISDbits.TRISD6 = 0;		// Configura RD6 como output
	LATDbits.LATD6 = 1;		// Ativar display menos significativo ("CNTL_DISP_H"=1 <=> RD6 = 1;)
	
	while(1){
		char input = getChar();

		if (input == 'a' || input == 'A'){
		  LATB = (LATB & 0x80FF) | 0x7700;        //   A = 0111 0111 0000 0000
		}else if (input == 'b' || input == 'B'){
		  LATB = (LATB & 0x80ff) | 0x7C00;        //   B = 0111 1100 0000 0000
		}else if (input == 'c' || input == 'C'){
		  LATB = (LATB & 0x80FF) | 0x3900;        //   C = 0011 1001 0000 0000
	        }else if (input == 'd' || input == 'D'){
		  LATB = (LATB & 0x80ff) | 0x5E00;        //   D = 0101 1110 0000 0000
		}else if (input == 'e' || input == 'E'){
		  LATB = (LATB & 0x80ff) | 0x7900;        //   E = 0111 1001 0000 0000
		}else if (input == 'f' || input == 'F'){
		  LATB = (LATB & 0x80ff) | 0x7100;        //   F = 0111 0001 0000 0000
		}
	}       
}
