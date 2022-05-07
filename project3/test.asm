.orig   x3000
    LEA R1, buffer

    START

    ;; Code section 1
    LDI R0, kbsr

    BRzp START

    ;; Code section 2
    ldi R1, kbdr

    STR R0, R1, 0
    ADD R0, R0, 0
    BRz END
    ADD R1, R1, 1
    BR START
    END HALT

    kbsr .fill xfe00
    kbdr .fill xfe02
    buffer .blkw 100
.end