/* Header files for character checks, console input/output, and number conversion. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Keep the two input bits together in one structure. */
typedef struct {
    int a; /* First input bit. */
    int b; /* Second input bit. */
} InputPair;

/* Read one bit from the user.
   Return 1 when the input is valid, or 0 if no input is available. */
static int read_bit(const char *label, int *value) {
    char line[64]; /* Buffer for the line typed by the user. */

    for (;;) { /* Repeat until the user enters 0 or 1. */
        char *end; /* strtol stores where number parsing stopped. */
        long parsed;

        printf("%s (0 or 1): ", label); /* Show which input is requested. */

        /* Read the user's line. Stop if the input stream has ended. */
        if (fgets(line, sizeof line, stdin) == NULL) {
            return 0;
        }

        /* Convert the text to a decimal number. */
        parsed = strtol(line, &end, 10);

        /* Skip spaces and the newline after the number. */
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        /* Accept only a complete number that is exactly 0 or 1. */
        if (end != line && *end == '\0' && (parsed == 0 || parsed == 1)) {
            *value = (int)parsed; /* Save the bit in the caller's variable. */
            return 1; /* Tell the caller that the input is valid. */
        }

        /* The input was not valid, so explain and ask again. */
        puts("Please enter 0 or 1.");
    }
}

int main(void) {
    InputPair input; /* Stores the user's A and B values. */
    int sum;         /* Stores the Sum output bit. */
    int carry;       /* Stores the Carry output bit. */

    /* Print a simple title and instructions. */
    puts("========================");
    puts("      HALF ADDER");
    puts("========================");
    puts("Enter the two input bits.\n");

    /* Read both bits. If either read fails, print an error and stop. */
    if (!read_bit("Input A", &input.a) || !read_bit("Input B", &input.b)) {
        fputs("Input ended before both bits were entered.\n", stderr);
        return 1; /* A non-zero return value means the program failed. */
    }

    /* XOR gives Sum: it is 1 when the input bits are different. */
    sum = input.a ^ input.b;

    /* AND gives Carry: it is 1 only when both input bits are 1. */
    carry = input.a & input.b;

    /* Display the inputs and the two calculated outputs. */
    puts("\n--- OUTPUT ---");
    printf("A      : %d\n", input.a);
    printf("B      : %d\n", input.b);
    printf("Sum    : %d  (A XOR B)\n", sum);
    printf("Carry  : %d  (A AND B)\n", carry);

    return 0; /* Zero means the program finished successfully. */
}
