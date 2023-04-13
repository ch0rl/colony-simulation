/*
 * map-gen.h
 * ---------
 * Helpers for generating 'maps', 'food', and 'barriers'.
 */

#include <stdbool.h>
#include "vectors.h"
#include "error.h"
#include "random_ext.h"

#ifndef MAP_GEN_H
#define MAP_GEN_H

#define MAX_FOOD_AMOUNT 100

// Structures
// Food are points with an "amount"
typedef struct {
    bool is_blocked;    // True if barrier
    uint food_amount;   // 0 = no food
    int pheromone_lvl;  // <0 = bad; >0 = good 
} Grid_item;

// Maps have a size and a grid
typedef struct {
    uint seed;
    
    uint width;
    uint height;

    Grid_item **grid; // 2d array

    Vector2 home;
} Map;

/*
 * gen_map
 * -------
 * Generates a map.
 */
Map gen_map(uint width, uint height, uint f_num, uint b_num, uint seed) {
    // Seed random
    srand(seed);

    // Initialise map
    Grid_item **__grid = (Grid_item **)malloc(sizeof(Grid_item *) * width);
    if (__grid == NULL) {
        err_loc("map-gen.h > gen_map", "Failed to allocate __grid.", ERR_CODE_ALLOC);
    }
    
    Map map = {
        .seed = seed,
        .width = width,
        .height = height,
        .grid = __grid,
        .home = (Vector2) { (int)width / 2, (int)height / 2 }
    };

    for (uint x = 0; x < width; x++) {
        map.grid[x] = (Grid_item *)malloc(sizeof(Grid_item) * height);

        if (map.grid[x] == NULL) {
            err_loc("map-gen.h > gen_map", "Failed to allocate map.grid[x].", ERR_CODE_ALLOC);
        }

        for (uint y = 0; y < height; y++) {
            map.grid[x][y] = (Grid_item){
                .is_blocked = false,
                .food_amount = 0,
                .pheromone_lvl = 0
            };
        }
    }

    // Set random food locations
    for (uint i = 0; i < f_num; i++) {
        Vector2 pos = random_vec_uint(width, height);
        map.grid[(uint)pos.x][(uint)pos.y].food_amount = rand_uint(MAX_FOOD_AMOUNT);
    }

    // Set random barriers
    for (uint i = 0; i < b_num; i++) {
        Vector2 pos = random_vec_uint(width, height);
        map.grid[(uint)pos.x][(uint)pos.y].is_blocked = true;
    }

    return map;
}

#endif  // MAP_GEN_H
