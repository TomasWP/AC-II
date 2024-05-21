# Mapa de registos:
# cnt:	$t0

	.equ	getchar, 2
	.equ	putchar, 3
	.equ	printint, 6
	.data
	.text
	.globl main
	
main:					# int main(void){					
	li	$t0, 0			#	int cnt = 0;
do:					#	do{
	li	$v0, getchar
	syscall				#		$a0 = getchar(); 
	move	$a0, $v0
	addiu	$a0,$a0,1		#		$a0++;
	li	$v0, putchar
	syscall				#		putchar($a0);
	addiu	$t0,$t0,1		#		cnt++;
while:					
	bne	$t1, '\n', do		#	}while(c != '\n');
	move	$a0,$t0
	li	$a1,10
	li	$v0,printint
	syscall				#	printint(cnt, 10);
	li	$v0,0			#	return 0;
	jr	$ra			# }
