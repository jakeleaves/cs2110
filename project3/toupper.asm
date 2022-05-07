;; =============================================================
;; CS 2110 - Fall 2021
;; Project 3 - To Upper
;; =============================================================
;; Name: Jake Eaves
;; =============================================================

;; Suggested Pseudocode (see PDF for explanation)
;;
;; index = mem[STRING];
;; lowerBound = 97;
;; upperBound = 122;
;; 
;; while (mem[index] != 0) {
;;   char = mem[index];
;;   if (char >= lowerBound && char <= upperBound) {
;;     char = char - 32;
;;     mem[index] = char;
;;   }
;;   index++;
;; }

.orig x3000
    LD R0, STRING
    LD R1, LOWER_A ;; -97
    LD R2, LOWER_Z ;; -122

    WHILE
    LDI R3, STRING ;; R3 = mem[index]
    AND R4, R4, 0 ;; char = 0
    AND R3, R3, R3
    LDR R3, R0, 0
    BRz ENDWHILE
    ADD R4, R3, 0 ;; char = mem[index]
    AND R5, R5, 0
    ADD R5, R4, R1 ;; char - lowerbound
    BRn END
    AND R5, R5, 0
    ADD R5, R4, R2 ;; char - upperbound
    BRp END
    ADD R4, R4, -8
    ADD R4, R4, -8
    ADD R4, R4, -8
    ADD R4, R4, -8 ;; char = char - 32
    STR R4, R0, 0
    END
    ADD R0, R0, 1
    BRnzp WHILE
    ENDWHILE
    HALT

LOWER_A     .fill -97
LOWER_Z     .fill -122

STRING      .fill x4000
.end

.orig x4000
.stringz "cOtTonCANdy"
.end
