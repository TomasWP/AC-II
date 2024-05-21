#include <detpic32.h>

void delay(int ms);

int main(void){

    TRISCbits.TRISC14 = 0;        // Configure RC14 as ouput
    while(1){
      delay(500);                 // Delay 0.5s     freq = 2Hz
      LATCbits.LATC14 = !LATCbits.LATC14;
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
