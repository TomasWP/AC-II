# RE4-RE1: OUTPUT
# RB1: INPUT
	.equ	ResetCoreTimer, 12
	.equ	ReadCoreTimer, 11
	.equ	ADDR_BASE_HI, 0xBF88
	.equ	TRISE, 0x6100
	.equ	TRISB, 0x6040
	.equ	LATE, 0x6120
	.data
	.text
	.globl main
main:
	# 1
	lui	$t0, ADDR_BASE_HI
	lw	$t1, TRISE($t0)
	andi	$t1, $t1, 0xFFE1
	sw	$t1, TRISE($t0)
	lw	$t1, TRISB($t0)
	andi	$t1, $t1, 0x0001
	sw	$t1, TRISB($t0)
	
	# 2
	li	$t2, 0
while:
	# 3
	lw	$t1, LATE($t0)
	andi	$t1, $t1, 0xFFE1
	sll	$t3, $t2, 1			# shift counter value to position 1(led RE1)
	or	$t1, $t1, $t3
	sw	$t1, LATE($t0)
	
	# 4
	li	$v0, ResetCoreTimer	
	syscall
wait:
	li	$v0, ReadCoreTimer
	syscall
	blt	$v0, 4347826, wait
	
	# 5
	addi	$t2, $t2, 1
	andi	$t2, $t2, 0x000F
	j while
	jr	$ra
