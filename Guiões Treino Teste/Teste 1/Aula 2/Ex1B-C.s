	.equ putChar, 3
	.equ printInt, 6
	.equ resetCoreTimer, 12
	.equ readCoreTimer, 11
	.data
	.text
	.globl main
main:					# int main(void){
	li	$t0, 0			#	int counter = 0;
while:					#	while(1){
	li	$a0, '\r'
	li	$v0, putChar
	syscall				#		putChar('\r');
	li	$t1, 4
	sll	$t1, $t1, 16	
	ori	$t1, $t1, 10	
	move	$a1, $t1
	move	$a0, $t0
	li	$v0, printInt
	syscall				#		printInt(counter, 10 | 4 <<16);
	li	$v0, resetCoreTimer
	syscall				#		resetCoreTimer();
while2:
	li	$v0, readCoreTimer
	syscall
	blt	$v0, 20000000, while2	#		while(readCoreTimer() < 200000);
	addiu	$t0, $t0, 1		#		counter++;
	j	while			#	}
	li	$v0, 0			#	return 0;
	jr	$ra			# }
