/*
 * random_ext.h
 * ------------
 * General randomness helpers.
 */

#include <stdlib.h>

#ifndef RANDOM_EXT_H
#define RANDOM_EXT_H

typedef unsigned int uint;

uint rand_uint(uint max) {
    return rand() % max;
}

float rand_float(float max) {
    return max * (rand() / (float)RAND_MAX);
}

#endif  // RANDOM_EXT_H
