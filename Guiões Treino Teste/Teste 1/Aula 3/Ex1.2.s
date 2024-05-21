# RB0: INPUT
# RE0: OUTPUT
	.equ	ADDR_BASE_HI, 0xBF88
	.equ	TRISE, 0x6100
	.equ 	TRISB, 0X6040
	.equ	PORTB, 0X6050
	.equ 	LATE, 0x6120
	.data
	.text
	.globl main
main:
	lui	$t0, ADDR_BASE_HI
	lw	$t1, TRISE($t0)
	andi	$t1, $t1, 0xFFFE		# configurar RE0 como output
	sw	$t1, TRISE($t0)
	
	lw	$t1, TRISB($t0)
	andi	$t1, $t1, 0x0001		# configurar RB0 como input
	sw	$t1, TRISB($t0)
while:
	lw	$t1, PORTB($t0)
	andi	$t1, $t1, 0x0001		# mascara
	xori	$t1, $t1, 0x0001
	lw	$t2, LATE($t0)			# ler valor
	andi	$t2, $t2, 0xFFFE		# dar reset ao bit
	move	$t2, $t1			# passar valor de entrada no porto de saida
	sw	$t2, LATE($t0)			# guardar valor(escrever valor de entrada no porto de saida)
	j	while
	li	$v0, 0
	jr	$ra
