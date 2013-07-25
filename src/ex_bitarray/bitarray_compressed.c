/* Implementation of a BINARY ARRAY. This is the slighly more sophisticated
 * version, and uses sub-byte indexing (through bit-masking tricks) to pack 
 * 8x more binary elements into the same amount of memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bitarray.h"

/* 8 bits can be stored in a single cell (byte) */
#define BITS_PER_CELL 8 

void *ba_build(unsigned int num_elements) {
    /* Dynamically allocate heap space for the array.*/

    unsigned int array_size;
    void *array;

    array_size = (unsigned int)ceil(num_elements / BITS_PER_CELL);
    array = malloc(sizeof(unsigned char) * array_size);
    memset(array, (unsigned char)0, array_size);
    return array;
}

void ba_set(void *bitarray, unsigned int index) {
    /* Set the indexed bit in the right cell to "1" */
    unsigned int cell_index;
    unsigned char bit_offset;
    unsigned char cell_value;

    cell_index = index / BITS_PER_CELL;
    bit_offset = index % BITS_PER_CELL;

    cell_value = ((char *)bitarray)[cell_index];

    /* Bit-hack to set the Nth bit of byte to 1. */
    ((char *)bitarray)[cell_index] = (cell_value | (1<<bit_offset));
}

char ba_get(void *bitarray, unsigned int index) {
    /* Return the true/false value for the indexed bit". N.B. this will return
     * an appropriate boolean expression:  0/not zero (not necessarily 0/1).*/
    unsigned int cell_index;
    unsigned char bit_offset;
    unsigned char cell_value;

    cell_index = index / BITS_PER_CELL;
    bit_offset = index % BITS_PER_CELL;

    cell_value = ((char *)bitarray)[cell_index];

    /* Bit-hack to get boolean expression for Nth the bit of byte. */
    return (cell_value & (1<<bit_offset));
}

int main() {
    return 0;
}
