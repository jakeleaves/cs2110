.orig x0000

LD R1, MYLABEL
ADD R1, R1, 3
ST R1, MYLABEL2

LD R2, MYLABEL2

HALT

MYLABEL .fill x0002
MYLABEL2 .fill x0000
.end

;; R1: x0005, R2: x0005
