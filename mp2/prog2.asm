;
;
;
.ORIG x3000
	
;your code goes here

; For this MP, we didn't use the lab to approach the problem, but, instead, largely used the flow chart to help guide our train of logic. We started in the main code by reading an input and echoing it to the screen. Then checking if the value was an = and then space. We realized all the desired inputs, apart from "^," were in a range between ascii decimal 42 to 57. So we checked if it was in that range then, using the same range-ascii logic, checked if the input was an operator or operand. Then we used the rest of the flow chart to either pop or push depending on the input as well as jump to the operator subroutines if the input was such. Lastly, we had to figure out how to print the output in hex, so we just used the code from our last mp. Thankfully we didn't have to copy and paste the code four times this time because of a lack of registers, due to no subroutines. Of course we had to load the "Invalid Expression" string into the error subroutine to make it and save & restore registers along the way. 

READ
	; read charcter and echo to screen
	GETC			; read next character
	OUT			; print to screen
	
	; check if input's ascii value represents "="
	LD R1, EQUALS		; load ascii value of "[space]"
	NOT R1, R1		; make "=" ascii value negative by NOTing first
	ADD R1, R1, #1		; add one to inverted value to make negative
	ADD R1, R0, R1		; subtract ascii value of equals sign from input
	BRz PRINTH		; if difference is zero (input is "=") go to print hex subroutine
	
	; check if input's ascii represents "[space]"
	LD R1, SPACE 		; load negative ascii value of "[space]"
	ADD R1, R0, R1		; subtract ascii value of space from input
	BRz READ		; read another chacter if value is a space

	; check if input's ascii represents "^"	
	LD R2, POWERASC		; load negative ascii value of "[space]"
	ADD R2, R0, R2		; subtract ascii value of power sign from input
	BRz	SKIP		; if value is "^" then go to operator section under SKIP

	; make sure input is in wanted range
	LD R2, NEG57		; load negative ascii value of 9 (end of range)
	ADD R2, R0, R2		; subtract ascii value of start of range from input
	BRp ERROR		; if it's above 57 then go to error

	LD R2, NEG42		; load negative ascii value of "*" (start of range)
	ADD R1, R0, R2		; subtract ascii value of end of range from input
	BRn ERROR		; if it's less than 42 then go to error
	
	; testing for special unwanted cases within range
	LD R1, COMMA		; load negative ascii value of ","
	ADD R1, R0, R1		; subtract ascii value of comma sign from input
	BRz ERROR		; if the input is a comma go to error

	LD R1, PERIOD		; load negative ascii value of "."
	ADD R1, R0, R1		; subtract ascii value of period sign from input
	BRz ERROR		; if the input is a period go to error

SKIP

; check if input is a number or operator or operand
	LD R1, NEG48		; #-48
	ADD R1, R0, R1		; check which part of range
	BRn OPERATOR			

	LD R1, NEG57		; #-57
	ADD R1, R0, R1		; check which part of range
	BRp OPERATOR		; if positive then value is operator
	LD R1, NEG48		; #-48
	ADD R0, R0, R1		; push subtracted input
	JSR PUSH		; push if input is a number (negative or zero)
	BRnzp READ		
	
OPERATOR JSR EVALUATE		; label to jsr to evaluate
BRnzp READ			; loop to start of main code
PRINTH JSR PRINT_HEX		; label to jsr to printing output in hex to screen



BRnzp STOP			; skip error label section
ERROR
	LEA R0, ERROROUT	; load error string into R0
	PUTS			; print to screen
	JSR STOP
	

STOP
	
	LD R5, OUTPUT		; put output for all types of evaluations in R5
HALT				; stop code


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	ST R7, SEVENPRINT	; save R7 value

	AND R3, R3, #0		; init R3

	JSR POP			; pop value from stack
	ADD R1, R0, #0		; save R0 in R1
	ST R0, OUTPUT		; store output to OUTPUT label which will be stored in R5
	JSR POP			; pop value from stack
	ADD R5, R5, #0		
	BRz ERROR
	ADD R5, R1, #0

	AND R4, R4, #0
	ADD R4, R4, #4
	
; outer loop for formatting
LOOP1	ADD R3, R3, #4		; set hex loop counter to 4

	
	AND R0, R0, #0		; reset R5

	; loop to isolate first binary numbers
HEXLOOP1 ADD R5, R5, #0		; check R0	
	BRzp ZERO1		; if zero or positive jump to ZERO label

	ADD R0, R0, R0		; leftshit R0
	ADD R0, R0, #1		; add one
	BRnzp END1
	
ZERO1	ADD R0, R0, R0
	
END1	ADD R5, R5, R5		; leftshift R5

	ADD R3, R3, #-1		; decrement hex loop counter
	BRp HEXLOOP1

	; hexadecimal representation of four digits found from hex loop
	AND R6, R6, #0		; reset R6
	ADD R6, R6, #-10	; set R6 to -10
	
	ADD R6, R0, R6		; subtract 10 from four bits from hex number to check if it's A-F or 0-9
	BRn INT1		; if four digits are negative then it's a integer

	ADD R0, R0, #15		; add 65 to ascii representation to get letter part of hex repres.
	ADD R0, R0, #15	
	ADD R0, R0, #5	
	ADD R0, R0, #15	
	ADD R0, R0, #5	

	BRnzp PRINT1

INT1	ADD R0, R0, #15		; add 48 to ascii representation to get integer part of hex
	ADD R0, R0, #15	
	ADD R0, R0, #15
	ADD R0, R0, #3		

PRINT1	ADD R0, R0, #0		; load hex digit in R0 into R0
	OUT			; print

	ADD R4, R4, #-1		; decrement counter
	BRp LOOP1

	LD R7, SEVENPRINT


	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
;your code goes here
	ST R7, SEVENEVAL	; store R7 value

	; pop two values and save in R3 and R4
	ADD R1, R0, #0		; save R0 in R1 to use as handler
	JSR POP
	ADD R3, R0, #0
	JSR POP
	ADD R4, R0, #0

	ADD R5, R5, #0		; if overflow/underflow go to error
	BRp JERROR

	; check what operator the input is
	LD R2, MULTIPLYASC	; check if input is "*"
	ADD R2, R1, R2		; check difference
	BRz JMUL

	LD R2, ADDASC 		; check if input is "+"
	ADD R2, R1, R2
	BRz JPLUS

	LD R2, SUBTRASC		; check if input is "-"
	ADD R2, R1, R2
	BRz JMIN

	LD R2, DIVIDEASC	; check if input is "/"
	ADD R2, R1, R2
	BRz JDIV

	LD R2, POWERASC		; check if input is "^"
	ADD R2, R1, R2
	BRz JPOW

	BRnzp SKIP1		; skip labels that allow program to jump to operator subroutines

	; labels that jump to each opperator's subroutine and error subroutine
JERROR
	JSR ERROR
	BRnzp SKIP1

JMUL
	JSR MUL
	BRnzp SKIP1

JPLUS
	JSR PLUS
	BRnzp SKIP1

JMIN
	JSR MIN
	BRnzp SKIP1

JDIV
	JSR DIV
	BRnzp SKIP1

JPOW
	JSR EXP
	BRnzp SKIP1

SKIP1
	JSR PUSH		; push to stack

	LD R7, SEVENEVAL	; restore R7 value	

	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0, R3, R4		; R3 + R4
	
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	; R4 - R3
;your code goes here
	NOT R3, R3		; invert R3
	ADD R3, R3, #1		; add 1 to inverted R3 to make R3 negative
	ADD R0, R3, R4		; R4 - R3

	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	; store registers used
	ST R7, SEVENMUL
	ST R2, TWOMUL
	ST R3, THREEMUL
	ST R4, FOURMUL

	AND R2, R2, #0		; init R2
LP	ADD R2, R3, R2		; leftshift and don't change input R3 b/c it needs to be static
	ADD R4, R4, #-1		; decrement input R4 which is used as a counter
	BRp LP			; if positive keep looping/leftshifting

	ADD R0, R2, #0		; put R2 in output register R0

	; restore registers used
	LD R7, SEVENMUL
	LD R2, TWOMUL
	LD R3, THREEMUL
	LD R4, FOURMUL

	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 --> R4/R3
;out R0
DIV	
;your code goes here
	ADD R3, R3, #0		; add R3 to itself	
	BRz JERROR1

	AND R0, R0, #0		; init R0

	NOT R3, R3		; make R3 negative
	ADD R3, R3, #1

DIVLOOP	
	ADD R0, R0, #1		; output is calculated by counting how many times subtracted until zero
	ADD R4, R4, R3
	BRn SKIP3
	BRz END3
	BRp DIVLOOP

	BRnzp END3
JERROR1
	JSR ERROR

SKIP3 ADD R0, R0, #-1
END3
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP	; Exponent subroutine: R4^R3
;your code goes here
	; store registers use & R7
	ST R7, SEVENEXP
	ST R5, FIVEEXP
	ST R4, FOUREXP
	ST R3, THREEXP
	ST R2, TWOEXP
	ST R1, ONEXP

	AND R0, R0, #0		; init R0

	;check for two special cases
	ADD R3, R3, #0
	BRz ZERO
	ADD R3, R3, #-1		; subtract one from input to see if it's zero
	BRz ONE

	
	ADD R1, R3, #0		; put R3 into R1 as handler/counter
	ADD R3, R4, #0		; to multiply by itself
	AND R2, R2, #0		; init R2
PLP	JSR MUL			; jump to multiply subroutine
	ADD R4, R0, #0
	ADD R1, R1, #-1		; decremet counter
	BRp PLP


BRnzp END2			; skip special cases section
ZERO 	; if R3 input is zero
	AND R0, R0, #0		; init R0 or output register
	ADD R0, R0, #1		; output will always be zero because x^0 = 1

BRnzp END2
ONE 	;if R3 input is one
	AND R0, R0, #0		; init R0 or ouput register
	ADD R0, R4, #0		; make other input R4 the output because x^1 = x

END2

	; restore registers used
	LD R7, SEVENEXP
	LD R5, FIVEEXP
	LD R4, FOUREXP
	LD R3, THREEXP
	LD R2, TWOEXP
	LD R1, ONEXP

	RET
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		; failure
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET



POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
EQUALS		.FILL #61	; negative ascii value of equals sign (FFC3)
SPACE		.FILL xFFE0	; negative ascii value of [space]
COMMA		.FILL #-44	; negative ascii value of ","
PERIOD		.FILL #-46	; negative ascii value of "."
POWERASC	.FILL #-94	; negative ascii value of the power symbol "^"
MULTIPLYASC	.FILL #-42
ADDASC		.FILL #-43
SUBTRASC	.FILL #-45
DIVIDEASC	.FILL #-47
NEG57		.FILL #-57
NEG42		.FILL #-42
NEG48		.FILL #-48
ERROROUT	.STRINGZ "\nInvalid Expression\n"	
SEVENEVAL	.BLKW #1
SEVENEXP	.BLKW #1
FOUREXP		.BLKW #1
THREEXP		.BLKW #1
TWOEXP		.BLKW #1
ONEXP		.BLKW #1
SEVENMUL	.BLKW #1
TWOMUL		.BLKW #1
THREEMUL	.BLKW #1
FOURMUL		.BLKW #1
SEVENPRINT	.BLKW #1
FIVEEXP		.BLKW #1
OUTPUT		.BLKW #1

.END
