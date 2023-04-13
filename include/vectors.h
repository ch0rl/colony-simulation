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
    double x;
    double y;
} Vector2;

/*
 * random_vec_uint
 * ---------------
 * Generate a random vector:
 *  .x in [0, x_max]
 *  .y in [0, y_max]
 */
Vector2 random_vec_uint(uint x_max, uint y_max) {
    return (Vector2) {
        .x = (double)rand_uint(x_max),
        .y = (double)rand_uint(y_max)
    };
}

/*
 * random_vec_int
 * --------------
 * Generate a random vector:
 *  .x in [-x_max, x_max]
 *  .y in [-y_max, y_max]
 */
Vector2 random_vec_int(uint x_max, uint y_max) {
    int x_mod = 1, y_mod = 1;
    
    if (rand() & 1) {
        x_mod = -1;
    }

    if (rand() & 1) {
        y_mod = -1;
    }

    return (Vector2) {
        .x = x_mod * (double)rand_uint(x_max),
        .y = y_mod * (double)rand_uint(y_max)
    };
}

/*
 * neighbour_points
 * ----------------
 * Get all points strictly within n units (not including pos).
 * (return will need freeing)
 */
Vector2 *neighbour_points(Vector2 pos, uint n, uint *num) {
    *num = 0;
    // https://en.wikipedia.org/wiki/Gauss_circle_problem
    uint num_points = PI * n * (n + 2 * sqrt(2));
    
    Vector2 *points = (Vector2 *)malloc(sizeof(Vector2) * num_points);

    // Inefficient but oh well
    // Assume circle at (0, 0), add pos to points within
    // If (x, y) in circle, so are (-x, y), (x, -y), and (-x, -y)
    Vector2 p_mods[4] = {
        (Vector2){1, 1},
        (Vector2){-1, 1},
        (Vector2){1, -1},
        (Vector2){-1, -1}
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
                        points[points_i++] = (Vector2){
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
Vector2 vector_add(Vector2 a, Vector2 b) {
    return (Vector2) {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

/*
 * vector_sub
 * ----------
 * Subtract two vectors.
 */
Vector2 vector_sub(Vector2 a, Vector2 b) {
    return (Vector2) {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}

/*
 * vector_uint_times_k
 * -------------------
 * Multiply a vector by a constant.
 */
Vector2 vector_times_k(Vector2 v, double k) {
    return (Vector2) {
        .x = v.x * k,
        .y = v.y * k
    };
}

/*
 * vector_int_sub_k
 * ----------------
 * Subtract a constant from a vector.
 */
Vector2 vector_sub_k(Vector2 v, double k) {
    return (Vector2) {
        .x = v.x - k,
        .y = v.y - k
    };
}

/*
 * unit_vector
 * -----------
 * Find the unit vector of v.
 */
Vector2 unit_vector(Vector2 v) {
    float size = sqrt(v.x * v.x + v.y * v.y);
    return (Vector2) {
        .x = (float)v.x / size,
        .y = (float)v.y / size
    };
}

/*
 * vector_round
 * ------------
 * Round a vector's elements.
 */
Vector2 vector_round(Vector2 v) {
    return (Vector2) {
        .x = round(v.x),
        .y = round(v.y)
    };
}

#endif  // VECTORS_H
