# include <detpic32.h>

void delay(int ms);

int main(void){

	TRISE = TRISE & 0xFF87;		// Configurar RE6-RE3 como output (1111 1111 1000 0111)
	int counter = 0;
	while(1){
		LATE = (LATE & 0xFF87) | counter << 3;
		delay(370);
		counter = (counter + 1) % 10;
	}
}

void delay(int ms){

	while(ms > 0){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
		ms--;
	}
}
