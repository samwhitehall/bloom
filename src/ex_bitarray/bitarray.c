/* Implementation of a BINARY ARRAY. This is the naive (un-optimised)
 * version, where each bit is represented by a byte (as this is the finest
 * level that can be indexed).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitarray.h"

void *ba_build(unsigned int num_elements) {
    /* Dynamically allocate heap space for the array.*/
    void *array;

    array = malloc(sizeof(unsigned char) * num_elements);
    memset(array, (unsigned char)0, num_elements);
    return array;
}

char ba_set(void *bitarray, unsigned int index) {
    /* Set the array at position "index" to be 1.*/
    ((char *)bitarray)[index] = (unsigned char)1;
}

char ba_get(void *bitarray, unsigned int index) {
    /* Get the value at position "index".*/
    return ((char *)bitarray)[index];
}

int main() {
    return 0;
}
