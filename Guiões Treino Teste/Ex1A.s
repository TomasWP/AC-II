	.equ	ADDR_BASE_HIGH, 0xBF88
	.equ	TRISB, 0x6040
	.equ	TRISE, 0x6100
	.equ	PORTB, 0x6050
	.equ	LATE, 0x6120
	.data
	.text
	.globl main
main:
	lui	$t0, ADDR_BASE_HIGH		# configurar RB0-RB3 como input
	lw	$t1, TRISB($t0)
	ori	$t1, $t1, 0x000F
	sw	$t1, TRISE($t0)
	
	lui	$t0, ADDR_BASE_HIGH		# configurar RE0-RE3 como output
	lw	$t1, TRISE($t0)
	andi	$t1, $t1, 0xFFF0
	sw	$t1, TRISE($t0)
while:
	lui	$t0, ADDR_BASE_HIGH
	lw	$t1, PORTB($t0)			# ler valor dip-switch
	andi	$t1, $t1, 0x000F		# definir mascara
	sw	$t1, LATE($t0)
	j while
	jr	$ra
