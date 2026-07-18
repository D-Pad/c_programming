#include <stdio.h>
#include "expressions/exp.h"

void expressions() {

    int x = 0;
    int y = 1;

    if (!x) {
        printf("0 evaluates to false\n");
    }

    if (y) {
        printf("1 evaluates to true\n");
    }

}

