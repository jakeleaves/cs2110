;; =============================================================
;; CS 2110 - Fall 2021
;; Project 3 - Collatz Conjecture
;; =============================================================
;; Name: Jake Eaves
;; =============================================================

;; !!!! PLEASE READ !!!!!
;; - The specification for each subroutine can be found right after the corresponding
;;   label for the subroutine. It contains information about the input register(s),
;;   output register(s), and the operation that needs to be carried out
;; 
;; - For some subroutines, we ask that you follow the pseudocode provided in the pdf.
;;   You are welcome to deviate from it, but we won't be able to help you in case you
;;   run into issues with the autograder 
;; 
;; - To test your subroutines, we highly recommend that you to use complx before
;;	 running the autograder. Details on how to run subroutines in complx can be found
;;   in the project pdf. We have covered this in lab too, so feel free to rewatch one
;;   of the lab recordings on this. Doing it this way will save you a TON of time.

.orig x3000

;; DO NOT CHANGE THIS CODE

	LD R0, COLLATZ_ADDY
	JMP R0

	HALT

COLLATZ_ADDY	.fill x3300
.end

.orig x3100

SHIFTLEFT
;; Shifts a binary number a certain number of times to the left.
;;
;; input:		R1 = num_of_times
;; output:		R0 = value

;; SHIFTLEFT Suggested Pseudocode (see PDF for explanation)
;;
;; while (num_of_times > 0) {
;;	 value += value;
;;	 num_of_times -= 1;
;; }
	ADD R1, R1, 0
	WHILESL
	AND R1, R1, R1 ;; calling value
	BRnz ENDWHILESL
	ADD R0, R0, R0
	ADD R1, R1, -1
	BRnzp WHILESL
	ENDWHILESL
	RET
.end

.orig x3200

SHIFTRIGHT
;; Shifts a binary number a certain number of times to the right.
;;
;; input:		R1 = num_of_times
;; output:		R0 = value

;; SHIFTRIGHT Suggested Pseudocode (see PDF for explanation)
;;
;; result = 0
;;    
;; while (num_of_times < 16) {
;;     result = result + result;
;;     if (value < 0) {
;;         result++;
;;     }
;;     value = value + value;
;;     num_of_times++;
;; }
;;
;;
	AND R4, R4, 0 ;; result = 0
	AND R3, R3, 0
	ADD R3, R3, -8
	ADD R3, R3, -8 ;; R3 = -16
	WHILEsr
	AND R2, R2, 0
	ADD R2, R1, R3 ;;(num_of_times - 16 < 0)
	BRzp SKIPWHILEsr
	ADD R4, R4, R4 ;; result = result + result
	ADD R0, R0, 0 ;; calling value
	BRzp ELSEsr ;; if value is 0 or positive
	ADD R4, R4, 1 ;; result++
	ELSEsr
	ADD R0, R0, R0 ;; value  = value + value
	ADD R1, R1, 1 ;; num_of_times++
	BRnzp WHILEsr
	SKIPWHILEsr
	AND R0, R0, 0
	ADD R0, R4, R0
	RET
.end

.orig x3300

COLLATZCONJECTURE
;; Performs the Collatz Conjecture algorithm:
;;		Even Numbers: Divide by 2
;;		Odd Numbers: Multiply by 3 and add 1
;;      Count the number of iterations it takes to reach 1
;;
;; Examples:
;;		value = 6
;;					(1) 6   /   2	=  3
;;					(2) 3 * 3 + 1   =  10
;;					(3) 10  /	2	=  5
;;					(4) 5 * 3 + 1   =  16
;;					(5) 16  /	2	=  8
;;					(6) 8   /	2	=  4
;;					(7) 4   /	2	=  2
;;					(8) 2   /	2	=  1
;;											num_of_iterations = 8
;;		value = 64
;;					(1) 64  /   2	=  32
;;					(2) 32  /	2	=  16
;;					(3) 16  /	2	=  8
;;					(4) 8   /	2	=  4
;;					(5) 4   /	2	=  2
;;					(6) 2   /	2	=  1
;;											num_of_iterations = 6

;; COLLATZCONJECTURE Suggested Pseudocode (see PDF for explanation)
;;
;; value = mem[VALUE];
;; num_of_iterations = 0;
;; while (value > 1) {
;;   if (value % 2 != 0) {
;;      temp = value;
;;      value = shiftleft(value, 1);
;;      value += temp;
;;      value += 1;
;;   }else {
;;      value = shiftright(value, 1);
;;   }
;;	 num_of_iterations += 1;
;; }
;;
;; mem[RESULT] = num_of_iterations;

;; Your code here!!
	LD R0, VALUE ;;value = mem[VALUE]
	AND R5, R5, 0 ;;num_of_iterations = 0
	WHILEcc
	ADD R2, R0, -1 ;; R2 = value - 1
	BRz ENDWHILEcc
	AND R3, R0, 1 ;; =1 if value is off, =0 is value is even
	BRnz ELSEcc ;; if value is odd, go to else statement
	AND R4, R4, 0 ;; creation of temp
	ADD R4, R4, R0 ;; temp = value
	AND R1, R1, 0
	ADD R1, R1, 1
	JSR SHIFTLEFT
	ADD R0, R0, R4 ;; value += temp
	ADD R0, R0, 1 ;; value ++
	ADD R5, R5, 1 ;; num_of_iterations+=1
	ELSEcc
	AND R1, R1, 0
	ADD R1, R1, 1
	JSR SHIFTRIGHT
    ADD R5, R5, 1 ;; num_of_iterations+=1
	BRnzp WHILEcc
    ENDWHILEcc
	ST R5, RESULT
	HALT

VALUE		.fill 6
RESULT      .blkw 1
.end
