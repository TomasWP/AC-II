# Mapa de registos
# counter:	$t3

	.equ putChar, 3
	.equ printInt, 6
	.equ resetCoreTimer, 12
	.equ readCoreTimer, 11
	.data
	.text
	.globl main

main:
	li	$t3, 0
while1:
	li	$a0, '\r'
	li	$v0, putChar
	syscall
	li	$t0, 4
	li	$t1, 10
	sll	$t0, $t0, 16
	or	$a1, $t1, $t0
	move	$a0, $t3
	li	$v0, printInt
	syscall
	li	$v0, resetCoreTimer
	syscall
while2:
	li	$v0, readCoreTimer
	syscall
	bge	$v0,10, endwhile2
	j	while2
endwhile2:
	addi	$t3, $t3, 1
	j	while1
endwhile1:
	li	$v0, 0
	jr	$ra

