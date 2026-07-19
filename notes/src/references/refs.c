#include <stdio.h>
#include "references/refs.h"


struct RefExample {
    int number;
    char letter;
};


void fn_that_copies_num(struct RefExample r) {

   r.number = 50;
   printf("New value: %d\n", r.number);

}


void fn_that_modifies_num(struct RefExample* r) {

   r->number = 50;
   printf("New value: %d\n", r->number);

}


void fn_that_modifies_char(struct RefExample* r) {

    int numFromChar = r->letter;

    if (numFromChar < 97) {
        if (numFromChar >= 65 || numFromChar <= 90) {
            numFromChar = numFromChar + 32;
            printf("Converting %c to lowercase\n", r->letter);
        }
        else {
            return;
        }
    }

    if (numFromChar >= 122) {
        numFromChar = 96;
    }

    else if (numFromChar < 97) {
        numFromChar = 121;
    }

    numFromChar++;

    r->letter = numFromChar;

}


void references() {

    printf(" -- References --\n");
    struct RefExample ex;
    ex.number = 29;
    ex.letter = 'A';

    /*
     * When non-reference data is passed into a function, the data is copied
     */
    printf("NON REFERENCE:\nOld value before: %d\n", ex.number);
    fn_that_copies_num(ex);
    printf("Old value after: %d\n", ex.number);

    /*
     * When reference data is passed into a function, the data can be modified 
     */ 
    printf("REFERENCE:\nOld value before: %d\n", ex.number);
    fn_that_modifies_num(&ex);
    printf("Old value after: %d\n", ex.number);

    // The & operator is used to create a reference to some data. 
    struct RefExample* ref = &ex;
    printf("Letter before: %c\n", ref->letter);
    fn_that_modifies_char(ref); // Notice how we don't use & here because &
                                // was used when the reference value was 
                                // declared
    printf("Letter after: %c\n", ref->letter);

}

