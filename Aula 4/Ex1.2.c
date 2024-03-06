#include <detpic32.h>

int main(void){

	TRISE = TRISE & 0xFF87;	// COnfigurar portos RE6-RE3 como saida (1111 1111 1000 0111)
	int counter = 0;
	while(1){
		LATE = (LATE & 0XFF87) | counter<<3;
		resetCoreTimer();
		while(readCoreTimer() < 4347826);
		counter = (counter+1) %10;
	}
	return 0;
}
