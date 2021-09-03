;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments


<<<<<<< HEAD
;EXPLANATION FOR CODE: For MP1, the preceeding lab and class materials helped guide the process of the MP. Upon realizing this relation, it became clear that there were three parts to the MP1, or rather three loops: printing a hexadecimal (converting the binary representation to hexadecimal representation), isolating four bits of a bit string at a time to convert each into hexadecimal, and the formatting of representing the number of appearances in hexadecimal, or the histogram, next to their repsective characters. Each of the preceeding assignments coded these sections. We started with the formatting, which didn't take long, and understood that the value within the histogram address was the starting address of where the data was kept. We understood also that this address, x3F00, needed to be iterated. Then we thought the printing of the hexadecimal would be easy, until we realized there was no TRAP instruction we could use to print a number, except for TRAP 26, but that isn't alowed to be used. Thus we had to use the two parts stated above, to print the hexadecimal to the screen: splitting the bits into four parts then converting each set to hexadecimal. These four hexadecimal values together would provide the hold number in that representation. And after each iteration, we used OUT to print each char one at a time. Lastly, there were no registers left to use as a counter for a hexadecimal loop (loop four times), so we had to copy and paste it four times.

; Partners: jumanas2, macraew2

	
	AND R0, R0, #0		; init R0	

	LD R1, ASCII		; load first ascii value
	LD R2, HIST_ADDR	; load histogram

	AND R3, R3, #0		; init hex loop counter (x4)

	AND R4, R4, #0		; init counter
	LD R4, NUM_BINS		; set counter to 27

	AND R5, R5, #0		; init
	
	AND R6, R6, #0		; init
	
	
	; outer loop for formatting
LOOP	ADD R0, R1, #0		; load ascii value
	OUT			; print to display
	ADD R1, R1, #1		; iterate to next ascii value
	
	LD R0, SPACE		; load space
	OUT			; print

	;ADD R0, R2, #0 		; load histogram value


	ADD R3, R3, #4		; set hex loop counter to 4


	AND R0, R0, #0		; reset R5

	LDR R5, R2, #0		; load value at x3F00 into R0

	; loop to isolate first binary numbers
HEXLOOP ADD R5, R5, #0		; check R0	
	BRzp ZERO		; if zero or positive jump to ZERO label

	ADD R0, R0, R0
	ADD R0, R0, #1
	BRnzp END
	
ZERO	ADD R0, R0, R0
	
END	ADD R5, R5, R5

	ADD R3, R3, #-1		; decrement hex loop counter
	BRp HEXLOOP

	; hexadecimal representation of four digits found from hex loop
	AND R6, R6, #0		; reset R6
	ADD R6, R6, #-10	; set R6 to -10
	
	ADD R6, R0, R6		; subtract 10 from four bits from hex number to check if it's A-F or 0-9
	BRn INT			; if four digits are negative then it's a integer

	ADD R0, R0, #15		; add 65 to ascii representation to get letter part of hex repres.
	ADD R0, R0, #15	
	ADD R0, R0, #5	
	ADD R0, R0, #15	
	ADD R0, R0, #5	

	BRnzp PRINT

INT	ADD R0, R0, #15		; add 48 to ascii representation to get integer part of hex
	ADD R0, R0, #15	
	ADD R0, R0, #15
	ADD R0, R0, #3		

PRINT	ADD R0, R0, #0		; load hex digit in R0 into R0
	OUT			; print

; SECOND REPEAT

	; outer loop for formatting
LOOP1	ADD R3, R3, #4		; set hex loop counter to 4


	AND R0, R0, #0		; reset R5

	; loop to isolate first binary numbers
HEXLOOP1 ADD R5, R5, #0		; check R0	
	BRzp ZERO1		; if zero or positive jump to ZERO label

	ADD R0, R0, R0
	ADD R0, R0, #1
	BRnzp END1
	
ZERO1	ADD R0, R0, R0
	
END1	ADD R5, R5, R5

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

; THIRD REPEAT

	; outer loop for formatting
LOOP2	ADD R3, R3, #4		; set hex loop counter to 4


	AND R0, R0, #0		; reset R5

	; loop to isolate first binary numbers
HEXLOOP2 ADD R5, R5, #0		; check R0	
	BRzp ZERO2		; if zero or positive jump to ZERO label

	ADD R0, R0, R0
	ADD R0, R0, #1
	BRnzp END2
	
ZERO2	ADD R0, R0, R0
	
END2	ADD R5, R5, R5

	ADD R3, R3, #-1		; decrement hex loop counter
	BRp HEXLOOP2

	; hexadecimal representation of four digits found from hex loop
	AND R6, R6, #0		; reset R6
	ADD R6, R6, #-10	; set R6 to -10
	
	ADD R6, R0, R6		; subtract 10 from four bits from hex number to check if it's A-F or 0-9
	BRn INT2		; if four digits are negative then it's a integer

	ADD R0, R0, #15		; add 65 to ascii representation to get letter part of hex repres.
	ADD R0, R0, #15	
	ADD R0, R0, #5	
	ADD R0, R0, #15	
	ADD R0, R0, #5	

	BRnzp PRINT2

INT2	ADD R0, R0, #15		; add 48 to ascii representation to get integer part of hex
	ADD R0, R0, #15	
	ADD R0, R0, #15
	ADD R0, R0, #3		

PRINT2	ADD R0, R0, #0		; load hex digit in R0 into R0
	OUT			; print
	
; FOURTH REPEAT

	; outer loop for formatting
LOOP3	ADD R3, R3, #4		; set hex loop counter to 4


	AND R0, R0, #0		; reset R5

	; loop to isolate first binary numbers
HEXLOOP3 ADD R5, R5, #0		; check R0	
	BRzp ZERO3		; if zero or positive jump to ZERO label

	ADD R0, R0, R0
	ADD R0, R0, #1
	BRnzp END3
	
ZERO3	ADD R0, R0, R0
	
END3	ADD R5, R5, R5

	ADD R3, R3, #-1		; decrement hex loop counter
	BRp HEXLOOP3

	; hexadecimal representation of four digits found from hex loop
	AND R6, R6, #0		; reset R6
	ADD R6, R6, #-10	; set R6 to -10
	
	ADD R6, R0, R6		; subtract 10 from four bits from hex number to check if it's A-F or 0-9
	BRn INT3		; if four digits are negative then it's a integer

	ADD R0, R0, #15		; add 65 to ascii representation to get letter part of hex repres.
	ADD R0, R0, #15	
	ADD R0, R0, #15	
	ADD R0, R0, #5	
	ADD R0, R0, #5	

	BRnzp PRINT3

INT3	ADD R0, R0, #15		; add 48 to ascii representation to get integer part of hex
	ADD R0, R0, #15	
	ADD R0, R0, #15
	ADD R0, R0, #3		

PRINT3	ADD R0, R0, #0		; load hex digit in R0 into R0
	OUT			; print
	
	


ADD R2, R2, #1 		; increment histogram value

	LD R0, NEWLINE		; linebreak
	OUT			; print
	
	ADD R4, R4, #-1		; decrement 27x counter
	
	BRp LOOP		; if counter is positive keep looping, otherwise stop
	
=======
>>>>>>> release/master

DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

<<<<<<< HEAD
NEWLINE		.FILL x0A	; newline
ASCII		.FILL x40	; starting ascii value for "@"
SPACE		.FILL x20	; ascii for space
DECDIFF		.FILL x48	; difference in ascii representation to display the 0-9 hex digits
LETTERDIFF	.FILL x65	; difference in ascii representation to display the A-F hex digits

; for testing, you can use the lines below to include the string in this
; program...
; STR_START		.FILL STRING	; string starting address
=======
; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
>>>>>>> release/master
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
