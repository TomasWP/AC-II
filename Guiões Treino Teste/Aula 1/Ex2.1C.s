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
main:
while:
	li	$v0, printStr
	la	$a0, str1
	syscall

