#ifndef PART1_PORTING_ASSEMBLY
#define PART1_PORTING_ASSEMBLY

/* DO NOT MODIFY FILE */

#include <stdio.h>

#define UNUSED(x) ((void)x)

// Implement these functions in `part1-porting_assembly.c`
extern int compare(int a, int b);
extern int modulus(int a, int b);
extern void toUppercase(char string[]);
extern int shift_right(int original, int amount);
extern int shift_left(int original, int amount);
extern unsigned int collatz(unsigned int n);
extern int dot_product(int vecA[], int vecB[], int len);

#endif // ndef PART1_PORTING_ASSEMBLY
