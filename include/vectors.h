/*
 * vectors.h
 * ---------
 * Helpers for dealing with vectors.
 */

#include <stdlib.h>
#include <math.h>
#include "random_ext.h"

#ifndef VECTORS_H
#define VECTORS_H

#ifndef PI
#define PI 3.14159265358979323846

#endif  // PI

 // Macro
typedef unsigned int uint;

typedef struct {
    uint x;
    uint y;
} Vector2_uint;

typedef struct {
    int x;
    int y;
} Vector2_int;

typedef struct {
    float x;
    float y;
} Vector2_float;

/*
 * random_vec
 * ----------
 * Generate a random (uint) vector.
 */
Vector2_uint random_vec_uint(uint x_max, uint y_max) {
    return (Vector2_uint) {
        .x = rand() % x_max,
        .y = rand() % y_max
    };
}

/*
 * random_vec_float
 * ----------------
 * Generate a random (float) vector.
 */
Vector2_int random_vec_int(uint x_max, uint y_max) {
    int x_mod = 1, y_mod = 1;
    
    if (rand() & 1) {
        x_mod = -1;
    }

    if (rand() & 1) {
        y_mod = -1;
    }

    return (Vector2_int) {
        .x = x_mod * (rand() % x_max),
        .y = y_mod * (rand() % y_max)
    };
}

/*
 * neighbour_points
 * ----------------
 * Get all points strictly within n units (not including pos).
 * (return will need freeing)
 */
Vector2_uint *neighbour_points(Vector2_uint pos, uint n, uint *num) {
    *num = 0;
    // https://en.wikipedia.org/wiki/Gauss_circle_problem
    uint num_points = PI * n * (n + 2 * sqrt(2));
    
    Vector2_uint *points = (Vector2_uint *)malloc(sizeof(Vector2_uint) * num_points);

    // Inefficient but oh well
    // Assume circle at (0, 0), add pos to points within
    // If (x, y) in circle, so are (-x, y), (x, -y), and (-x, -y)
    Vector2_uint p_mods[4] = {
        (Vector2_uint){1, 1},
        (Vector2_uint){-1, 1},
        (Vector2_uint){1, -1},
        (Vector2_uint){-1, -1}
    };
    
    uint points_i = 0;
    uint n_squared = n * n;
    
    for (uint x = 0; x < n; x++) {
        for (uint y = 0; y < n; y++) {
            if (x * x + y * y <= n_squared) {
                // (x, y) in circle
                // Check not pos
                if (x != pos.x || y != pos.y) {
                    *num += 4;
                    for (uint p_i = 0; p_i < 4; p_i++) {
                        points[points_i++] = (Vector2_uint){
                            .x = pos.x + x * p_mods[p_i].x,
                            .y = pos.y + y * p_mods[p_i].y
                        };
                    }
                }
            }
        }
    }

    return points;
}

/*
 * vector_add
 * ----------
 * Add two vectors.
 */
Vector2_uint vector_uint_add(Vector2_uint a, Vector2_uint b) {
    return (Vector2_uint) {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

/*
 * vector_add_int
 * --------------
 * Add two vectors.
 */
Vector2_int vector_int_add(Vector2_int a, Vector2_int b) {
    return (Vector2_int) {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

/*
 * vector_add_int
 * --------------
 * Add two vectors.
 */
Vector2_int vector_u_int_add(Vector2_int a, Vector2_uint b) {
    return (Vector2_int) {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

/*
 * vector_sub
 * ----------
 * Subtract two vectors.
 */
Vector2_int vector_uint_sub(Vector2_uint a, Vector2_uint b) {
    return (Vector2_int) {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}

/*
 * vector_uint_times_k
 * -------------------
 * Multiply a vector by a constant.
 */
Vector2_uint vector_uint_times_k(Vector2_uint v, int k) {
    return (Vector2_uint) {
        .x = v.x * k,
        .y = v.y * k
    };
}

/*
 * vector_int_times_k
 * ------------------
 * Multiply a vector by a constant.
 */
Vector2_int vector_int_times_k(Vector2_int v, int k) {
    return (Vector2_int) {
        .x = v.x * k,
        .y = v.y * k
    };
}

/*
 * vector_float_times_k
 * --------------------
 * Multiply a vector by a constant.
 */
Vector2_float vector_float_times_k(Vector2_float v, int k) {
    return (Vector2_float) {
        .x = v.x * k,
        .y = v.y * k
    };
}

/*
 * vector_int_sub_k
 * ----------------
 * Subtract a constant from a vector.
 */
Vector2_int vector_int_sub_k(Vector2_int v, uint k) {
    return (Vector2_int) {
        .x = v.x - k,
        .y = v.y - k
    };
}

/*
 * unit_vector_int
 * ---------------
 * Find the unit vector of v.
 */
Vector2_float unit_vector_int(Vector2_int v) {
    float size = sqrt(v.x * v.x + v.y * v.y);
    return (Vector2_float) {
        .x = (float)v.x / size,
        .y = (float)v.y / size
    };
}

/*
 * unit_vector_uint
 * ----------------
 * Find the unit vector of v.
 */
Vector2_float unit_vector_uint(Vector2_uint v) {
    float size = sqrt(v.x * v.x + v.y * v.y);
    return (Vector2_float) {
        .x = (float)v.x / size,
        .y = (float)v.y / size
    };
}

/*
 * vector_round
 * ------------
 * Round a vector's elements.
 */
Vector2_uint vector_round(Vector2_float v) {
    return (Vector2_uint) {
        .x = (uint)round(v.x),
        .y = (uint)round(v.y)
    };
}

#endif  // VECTORS_H
