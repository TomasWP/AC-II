str1:	.asciiz "\nIntroduza um inteiro (sinal e módulo): "
str2:	.asciiz	"\nValor em base 10 (signed): ";
str3:	.asciiz	"\nValor em base 2: "
str4:	.asciiz "\nValor em base 16: "
str5:	.asciiz "\nValor em base 10 (unsigned): "
str6:	.asciiz "\nValor em base 10 (unsigned), formatado: "
	.equ printStr, 8
	.equ printInt, 6
	.equ printInt10, 7
	.equ readInt10, 5
	.data
	.text
	.globl main
main:					# int main(void){
while:					#	while(1){
	li	$v0, printStr
	la	$a0, str1
	syscall				#		printStr(str1);
	li	$v0, readInt10
	syscall			
	move	$t0, $v0		#		value = readInt10();
	li	$v0, printStr
	la	$a0, str2		
	syscall				#		printStr(str2);
	li	$v0, printInt10
	move	$a0, $t0
	syscall				#		printInt10(value);
	li	$v0, printStr
	la	$a0, str3
	syscall				#		printStr(str3);
	li	$v0, printInt	
	move	$a0, $t0
	li	$a0, 2			
	syscall				#		printInt(value, 2);
	li	$v0, printStr
	la	$a0, str4
	syscall				#		printStr(str4);
	li	$v0, printInt
	move	$a0, $t0
	li	$a1, 16
	syscall				#		printInt(value, 16);
	li	$v0, printStr
	la	$a0, str5
	syscall				#		printStr(str5);
	li	$v0, printInt
	move	$a0, $t0
	li	$a1, 10			
	syscall				#		printInt(value, 10);
	li	$v0, printStr
	la	$a0, str6
	syscall				#		printStr(str6);
	li	$v0, printInt
	move	$a0, $t0
	li	$t1, 5
	sll	$t1, $t1, 16
	ori	$t1, $t1, 10
	move	$a1, $t1
	syscall				#		printInt(value, 10 | 5 << 16);
					#	}
	li	$v0, 0			#	return 0;	
	jr	$ra			# }
