;; =============================================================
;; CS 2110 - Fall 2021
;; Project 3 - Compare
;; =============================================================
;; Name: Jake Eaves
;; =============================================================

;; Suggested Pseudocode (see PDF for explanation)
;;
;; a = mem[A];
;; b = mem[B];
;; diff = a - b;
;; if (diff > 0) {
;;   return 1;
;; } else if (diff < 0) {
;;   return -1;
;; } else {
;;   return 0;
;; } 

.orig x3000
    LD R0, A
    LD R1, B

    NOT R1, R1
    ADD R1, R1, 1 ;; -B

    ADD R2, R0, R1 ; A - B

    BRz ELSE
    BRn ELIF
    AND R2, R2, 0
    ADD R2, R2, 1
    ST R2, RESULT
    HALT
    ELIF
    AND R2, R2, 0
    ADD R2, R2, -1
    ST R2, RESULT
    HALT
    ELSE
    AND R2, R2, 0
    ADD R2, R2, 0
    ST R2, RESULT
    HALT

    A       .fill 3
    B       .fill 4
    RESULT  .blkw 1
.end
