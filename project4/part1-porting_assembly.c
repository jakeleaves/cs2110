/* DO NOT REMOVE INCLUDES */
#include "part1-porting_assembly.h"


/**
    Compare

    Implement the compare function below. You are given two parameters: `a` and
    `b`. The value you return depends on whether `a` is greater than `b`.

    return -1 if b is larger
    return 0 if equal
    return 1 if a is larger
*/
int compare(int a, int b) {
    int c;
    if (a < b) {
        c = -1;
    } else if (a > b) {
        c = 1;
    } else {
        c = 0;
    }
    return c;
}


/**
    Modulus

    Since there are different interpretations of modulus for negative numbers,
    you should take the absolute value of both of your parameters and then
    perform the operation. Return the result of the modulus operation.
*/
int modulus(int a, int b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    return a % b;
}


/**
    String Manipulation

    You will write a function that takes in a string stored in memory, changes
    any lowercase letters in the string to uppercase characters.

    * Strings are essentially a contiguous array of ASCII values. In this case,
      the first character is stored at the address given by the parameter
      `string`.
    * The string continues until the first instance of a null terminator, which
      has the value of 0.
    * Memory addresses in C can be treated as arrays. In particular, writing
      `string[i]` will give the i-th character in `string`. You can read from
      that character, as well as assign to it.

    ```
        Example:
        string = x4000
         ---------------------------------------
        | 'h'   | 'A'   | 'h'   | 'A'   | '\0'     |
        | x4000 | x4001 | x4002 | x4003 | x4004 |
         ---------------------------------------
    ```

    The string that you receive can contain any characters, and you should
    change all letters to uppercase, and leave non-letters as is.
*/
void toUppercase(char string[]) {
    int i = 0;
    while (string[i] != '\0') {
        if ((string[i] >= 97) & (string[i] <= 122)) {
            string[i] -= 32;
        }
        i++;
    }
    printf("%s\n", string);
}


/**
    Bit Shifting

    You will be given an unsigned original value, and an amount of bits to shift by.
    Return the shifted value. You will not have to handle overflow.
*/
int shift_right(int original, int amount) {
    return original >> amount;
}
int shift_left(int original, int amount) {
    return original << amount;
}


/**
    Collatz Conjecture

    You will be implementing a calculator for iterations of the Collatz
    Conjecture.

    The Collatz Conjecture is a famous unsolved math problem, which operates
    under a few simple rules. We have our Collatz function, C(n), which takes in
    exclusively positive integers. If n is an odd number, C(n) = 3n + 1. If n is
    an even number, C(n) = n/2. From here, we seek to calculate how many times
    we need to run n (and its subsequent results) through the Collatz function
    in order for it to reach the value 1.
*/
unsigned int collatz(unsigned int n) {
    int temp;
    int iterations = 0;
    while (n > 1) {
        if (n % 2 != 0) {
            temp = n;
            n = shift_left(n, 1);
            n += temp;
            n += 1;
        } else {
            n = shift_right(n, 1);
        }
        iterations += 1;
    }
    return iterations;
}


/**
    Dot Product

    The last method you will be writing is a dot product calculator. Given two
    arrays in memory, your job is to compute the dot product and return it back
    into memory. In mathematics, the dot product is calculated as the sum of
    multiplication between each pair of vector components. If A = [ a1 a2 a3 ]
    and B = [ b1 b2 b3 ], then the dot product between A and B would be

        (a1*b1) + (a2*b2) + (a3*b3)

    The values inside vectors can be positive or negative integers.

    You are given three input values:
      * `vecA` represents the address of the first vector in memory
      * `vecB` represents the address of the second vector in memory
      * `len` represents the length of each individual vector
*/
int dot_product(int vecA[], int vecB[], int len) {
    int i = 0;
    int result = 0;
    int temp;
    while (i < len) {
        result += (vecA[i] * vecB[i]);
        i++;
        temp = result;
    }
    return temp;
}
