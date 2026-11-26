#include <stdio.h> /* Provides printf(), puts(), fgets(), and sscanf(). */

/* A structure stores related data under one name. */
typedef struct {
    int a;      /* Stores the first input bit. */
    int b;      /* Stores the second input bit. */
    int sum;    /* Stores the result of A XOR B. */
    int carry;  /* Stores the result of A AND B. */
} HalfAdder;

/*
 * Reads and validates one input bit.
 * label is the text shown to the user.
 * value is the variable where the valid bit is stored.
 * The function returns 1 for valid input and 0 if input ends.
 */
static int read_bit(const char *label, int *value) {
    char line[32]; /* Stores one line of text entered by the user. */

    for (;;) {
        /* Print the input label, such as "Input A (0 or 1): ". */
        printf("%s (0 or 1): ", label);

        /* Read an entire line; return 0 if the input stream ends. */
        if (fgets(line, sizeof line, stdin) == NULL) {
            return 0;
        }

        int parsed; /* Stores the number extracted from the entered line. */
        char extra; /* Stores extra text to detect invalid input. */

        /*
         * Read one integer and optionally one extra character.
         * sscanf() returns 1 only when one valid integer was read.
         */
        if (sscanf(line, "%d %c", &parsed, &extra) == 1 &&
            (parsed == 0 || parsed == 1)) {
            /* Copy the validated bit into the caller's variable. */
            *value = parsed;
            return 1; /* Successful input. */
        }

        /* Repeat until the user enters exactly 0 or 1. */
        puts("Please enter 0 or 1.");
    }
}

int main(void) {
    HalfAdder half_adder; /* Creates a HalfAdder structure variable. */

    /* Print a simple program title and instructions. */
    puts("========================");
    puts("      HALF ADDER");
    puts("========================");
    puts("Enter the two input bits.\n");

    /*
     * Read input A and input B.
     * Stop if either read fails or the input stream ends.
     */
    if (!read_bit("Input A", &half_adder.a) ||
        !read_bit("Input B", &half_adder.b)) {
        fputs("Input ended before both bits were entered.\n", stderr);
        return 1; /* Return a non-zero value to indicate failure. */
    }

    /* XOR compares the two bits and gives 1 when they are different. */
    half_adder.sum = half_adder.a ^ half_adder.b;

    /* AND gives 1 only when both input bits are 1. */
    half_adder.carry = half_adder.a & half_adder.b;

    /* Print all inputs and calculated outputs. */
    puts("\n--- OUTPUT ---");
    printf("A      : %d\n", half_adder.a);
    printf("B      : %d\n", half_adder.b);
    printf("Sum    : %d  (A XOR B)\n", half_adder.sum);
    printf("Carry  : %d  (A AND B)\n", half_adder.carry);

    return 0; /* Return zero to indicate successful completion. */
}
