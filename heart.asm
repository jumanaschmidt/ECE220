.ORIG x3000

	LD R0, LESS
	OUT
	LD R0, THREE
	OUT

HALT

LESS	.FILL x3C
THREE	.FILL x33

.END
