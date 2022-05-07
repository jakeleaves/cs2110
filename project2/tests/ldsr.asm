.orig x0000
AND R1, R1, 0
ADD R1, R1, 2
ADD R2, R1, 2
LDSR R3, R1, R2
HALT

MYLABEL .fill x0002
MYLABEL2 .fill xBEEF

.end

;; R1 = x0002, R2 = x0004, R3 = xBEEF
