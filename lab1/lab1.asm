.ORIG x3000
; write your code here

	AND R4, R4, #0	
	ADD R4, R4, #4	

	AND R2, R2, #0
	LD R1, LABEL



LOOP	ADD R1, R1, #0	
	BRzp ZERO

	ADD R2, R2, R2
	ADD R2, R2, #1
	BRnzp END
	
ZERO	ADD R2, R2, R2
	
END	ADD R1, R1, R1

	ADD R4, R4, #-1

	BRp LOOP
	

HALT

LABEL .FILL X6C75

.END
