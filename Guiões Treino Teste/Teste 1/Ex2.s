	.equ	ADDR_BASE_HIGH, 0xBF88
	.equ	READ_CORE_TIMER, 11
	.equ	RESET_CORE_TIMER, 12
	.equ	TRISE, 0x6100
	.equ	LATE, 0x6120
	.equ	getChar, 2
	.data
	.text
	.globl main
main:
	lui	$t0, ADDR_BASE_HIGH
	lw	$t1, TRISE($t0)
	andi	$t1, $t1, 0xFFF0
	sw	$t1, TRISE($t0)			# Configurar RE0-RE3 como output
	
while:
	li	$v0, getChar
	syscall
	
if:	
	bne	$v0, 'f', elseif
	li	$t1, 0x0001
elseif:
	bne	$v0, 'd', elseif1
	li	$t1, 0x0002
elseif1:
	bne	$v0, 's', elseif2
	li	$t1, 0x0004
elseif2:
	bne	$v0, 'a', elseif3
	li	$t1, 0x0008
elseif3:
	bne	$v0, 'g', endif
	li	$t1, 0x000F
endif:
	sw	$t1, LATE($t0)
	j	while
	jr	$ra
