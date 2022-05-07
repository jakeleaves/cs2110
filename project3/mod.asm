;; =============================================================
;; CS 2110 - Fall 2021
;; Project 3 - Modulus
;; =============================================================
;; Name: Jake Eaves
;; =============================================================

;; Suggested Pseudocode (see PDF for explanation)
;;
;; a = mem[A];
;; b = mem[B];
;; 
;; if (a < 0) {
;;   a = ~a + 1;
;; }
;; 
;; if (b < 0) {
;;   b = ~b + 1;
;; }
;; 
;; while (a >= b) {
;;   a = a - b;
;; }
;; 
;; mem[RESULT] = a

.orig x3000
    LD R0, A
    BRp END
    NOT R0, R0
    ADD R0, R0, 1
    END

    LD R1, B
    BRp END2
    NOT R1, R1
    ADD R1, R1, 1
    END2

    NOT R4, R1  
    ADD R4, R4, 1   ;; -b
    
    AND R5, R5, 0
    ADD R5, R0, R4 ;; a - b
    BRn ENDWHILE
    WHILE
    ADD R0, R0, R4
    ADD R0, R0, 0
    AND R5, R5, 0
    ADD R5, R0, R4 ;; a - b
    BRzp WHILE
    ENDWHILE
    ST R0, RESULT
    HALT
    A       .fill 1
    B       .fill 4
    RESULT  .blkw 1
.end
