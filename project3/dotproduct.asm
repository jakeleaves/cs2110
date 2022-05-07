;; =============================================================
;; CS 2110 - Fall 2021
;; Project 3 - Dot Product
;; =============================================================
;; Name: Jake Eaves
;; =============================================================

;; Suggested Pseudocode (see PDF for explanation)
;;
;; vector_A_init = mem[VECTOR_A];
;; vector_B_init = mem[VECTOR_B];
;; index = mem[LENGTH];
;; index -= 1;
;; result = 0
;; 
;; while (index >= 0) {
;;   elementA = mem[vector_A_init + index];
;;   elementB = meM[vector_B_init + index];
;;   multSum = 0
;;   
;;   while (elementB != 0) {
;;     multSum += elementA;
;;     if (elementB < 0) {
;;       elementB++;
;;     } else if (elementB > 0) {
;;       elementB--;
;;     }
;;   }
;;   if (elementA > 0 || element A  < 0) {
;;     if (elementB < 0) {
;;        multSum = ~multSum + 1;
;;     }
;;   }
;;   
;;   result += multSum;
;;   index--;
;; }
;;
;; mem[RESULT] = result;

.orig x3000
    LD R0, VECTOR_A
    LD R1, VECTOR_B
    LD R2, LENGTH   ;; index = mem[LENGTH];
    ADD R2, R2, -1 ;; index -= 1;
    AND R3, R3, 0 ;; result = 0
    AND R5, R5, 0
    AND R6, R6, 0 ;; elemtn B

    WHILE
    ADD R2, R2, 0
    BRn ENDWHILE ;; while (index >= 0)
    AND R4, R4, 0 ;; multSum
    
    ADD R5, R2, R0
    LDR R5, R5, 0
    ADD R6, R2, R1
    LDR R6, R6, 0

    AND R7, R7, 0
    ADD R7, R7, R6
    ADD R5, R5, 0
    INNERWHILE
    ADD R7, R7, 0
    BRz SKIPINNERWHILE ;;   while (elementB != 0)
    ADD R4, R4, R5 ;;multSum += elementA;
    ADD R7, R7, 0 ;; calling element B for if condition
    BRz ELSE
    BRp ELSEIF
    ADD R7, R7, 2 ;; elementB++;
    ELSEIF
    ADD R7, R7, -1 ;; elementB--;
    ELSE
    BRNZP INNERWHILE
    SKIPINNERWHILE


    ADD R6, R6, 0 ;; calling element A
    BRz SKIP ;; if element A = 0
    ADD R6, R6, 0 ;; calling element B
    BRzp SKIP
    NOT R4, R4
    ADD R4, R4, 1 ;; multSum = ~multSum + 1;
    SKIP

    ADD R3, R3, R4;;   result += multSum;
    ADD R2, R2, -1;;   index--;

    BRnzp WHILE
    ENDWHILE
    
    ST R3, RESULT

HALT

VECTOR_A    .fill x4000
VECTOR_B    .fill x4100
LENGTH      .fill 4
RESULT      .blkw 1
.end

.orig x4000
    .fill -2
    .fill 3
    .fill 4
    .fill -5
.end

.orig x4100
    .fill -2
    .fill 3
    .fill -4
    .fill 5
.end