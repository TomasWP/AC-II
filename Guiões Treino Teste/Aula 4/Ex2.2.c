# include <detpic32.h>

void delay(int ms);
void print_char(int input);

int main(void){

	TRISB = TRISB & 0x80FF;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	int flag = 0;
	int i;
	while(1){
		
		if (flag == 0){
			LATDbits.LATD6 = 0;
			LATDbits.LATD5 = 1;
			for(i = 0; i < 6; i++){
				print_char(i);
				delay(500);
			}
			flag = 1;
		}else{
			LATDbits.LATD5 = 0;
			LATDbits.LATD6 = 1;
			for(i = 0; i < 6; i++){
				print_char(i);
				delay(500);
			}
			flag = 0;
		}
	}
	return 0;
}

void delay(int ms){

	while(ms > 0){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
		ms--;
        }
}

void print_char(int input){

		if (input == 0){
		  LATB = (LATB & 0x80FF) | 0x7700;        //   A = 0111 0111 0000 0000
		}else if (input == 1){
		  LATB = (LATB & 0x80ff) | 0x7C00;        //   B = 0111 1100 0000 0000
		}else if (input == 2){
		  LATB = (LATB & 0x80FF) | 0x3900;        //   C = 0011 1001 0000 0000
	        }else if (input == 3){
		  LATB = (LATB & 0x80ff) | 0x5E00;        //   D = 0101 1110 0000 0000
		}else if (input == 4){
		  LATB = (LATB & 0x80ff) | 0x7900;        //   E = 0111 1001 0000 0000
		}else if (input == 5){
		  LATB = (LATB & 0x80ff) | 0x7100;        //   F = 0111 0001 0000 0000
		}
}
