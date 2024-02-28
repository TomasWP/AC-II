# RB0: INPUT
# RE0: OUTPUT

	.equ ADDR_BASE_HI, 0xBF88

	.equ TRISE, 0x6100
	.equ PORTE, 0x6110
	.equ LATE, 0x6120

	.equ TRISB, 0X6040
	.equ PORTB, 0X6050
	.equ LATB, 0X6060

	.data
	.text
	.globl main

main:					# int main(void){
	lui	$t0, ADDR_BASE_HI	#
	lw	$t1, TRISE($t0)		#	$t1 = [TRISE]
	andi	$t1, $t1, 0xFFFE	#	RE0 = 0 (OUTPUT)
	sw	$t1, TRISE($t0)		#	WRITE TRISE REGISTER

	lw	$t1, TRISB($t0)		#	$t1 = [TRISB]
	ori	$t1, $t1, 0X0001	#	RB0 = 1 (INPUT)
	sw	$t1, TRISB($t0)		#	WRITE TRISB REGISTER

while:					#	while(1){
	lw	$t1, PORTB($t0)		#		$t1 = [PORTB]
	andi	$t1, $t1, 0x0001	#		$t1 = RB0 (arrange mask)
	lw	$t2, LATE($t0)		#		$t2 = [LATE]
	andi	$t2, $t2, 0xFFFE	#		RE0 = 0 (reset bit 0)
	move	$t2, $t1		#		$t2 = $t1 (RE0 = RB0)
	sw	$t2, LATE($t0)		#
	j	while			#	}
	li	$v0, 0			#	return 0
	jr	$ra			# }
