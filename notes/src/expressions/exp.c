#include <stdio.h>
#include "expressions/exp.h"

void expressions() {

    printf(" -- Expressions --\n");
    
    /*
     * In C, 0 is always false, and all other numbers are true
     */
    if (!0) {
        printf("0 evaluates to false\n");
    }

    if (1) {
        printf("1 evaluates to true\n");
    }

    if (-1) {
        printf("Negative numbers evaluate to true\n");
    }

    /*
     * 'Booleans' in C are just 0 and 1. There is a <stdbool.h> library that 
     * allows values to be assigned 'true' and 'false' but they're equivalent
     * to 1 and 0 anyway, so there's little point in using it.
     */
    int zeroIsZero = 0 == 0;
    int zeroIsOne = 0 == 1;
    printf("0 == 0: %d\n", zeroIsZero);
    printf("0 == 1: %d\n\n", zeroIsOne);

}

