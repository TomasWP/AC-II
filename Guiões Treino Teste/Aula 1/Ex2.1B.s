	.equ	inKey,1
	.equ	putChar,3
	.equ	printInt,6
	.data
	.text
	.globl main
main:				# int main(void){
	li	$t0, 0		#	$t0 = 0;
do:				#	do{
	li	$v0, inKey
	syscall
	move	$t1,$v0		#		c = inKey();
if:
	beq	$t1, 0, else	#		if(c != 0){
	li	$v0, putChar
	move	$a0,$t1
	syscall			#			putChar(c);
	j	endif
else:				#		}else{
	li	$v0,putChar
	li	$a0, '.'
	syscall			#			putChar('.');
endif:				#		}
	addiu	$t0,$t0,1	#		cnt++;
while:
	bne	$t1, '\n',do	#	}while(c != '\n');
	li	$v0,printInt
	move	$a0,$t0
	li	$a1, 10
	syscall			#	printInt(cnt, 10);
	li	$v0,0		#	return 0;
	jr	$ra		# }
