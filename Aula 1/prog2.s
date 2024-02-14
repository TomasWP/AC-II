# Mapa de regitos
# cnt 	-> $t0
# c 	-> $t1

	.equ getchar, 2
	.equ putchar, 3
	.equ printInt, 6
	.data
	.text
	.globl main
main:
	li	$t0, 0
do:
	addi	$t0, $t0, 1
	li	$v0, getchar
	syscall
	move	$t1, $v0
	addiu	$t1, $t1, 1
	move	$a0, $t1
	li	$v0, putchar
	syscall
while:
	bne	$t1,'\n', do
	move	$a0, $t0
	li	$a1, 10
	li	$v0, printInt
	syscall
	li	$v0, 0
	jr	$ra
