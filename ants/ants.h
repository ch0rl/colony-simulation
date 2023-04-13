/*
 * ants.h
 * ------
 * Helpers for managing ants.
 */

#include <stdbool.h>
#include "../include/map-gen.h"

#ifndef ANTS_H
#define ANTS_H

#define PI 3.14159265358979323846       // Probably good enough
#define ANT_VIEW_ANGLE PI / (float)2    // Quarter circle of vision
#define ANT_FOOD_VIEW_RANGE 3           // Number of squares ants can see food
#define ANT_SMELL_RANGE 10              // Number of squares ants can smell
#define ANT_PHEROMONE_MAX 25            // Number of ticks a pheromone should last
#define ANT_SPEED 1                     // How far ants can move per tick
#define ANT_PATH_BUFF_INC 20            // How much to increment the path buffer

typedef struct {
    Vector2_uint pos;
    float facing;  // Radians from North
    bool has_food;
} Ant;

/*
 * make_ants
 * ---------
 * Generate ants.
 */
Ant *make_ants(uint ant_num, Vector2_uint init_pos) {
    Ant *ants = (Ant *)malloc(sizeof(Ant) * ant_num);
    if (ants == NULL) {
        err_loc("ants.h > make_ants", "Failed to allocate ants.", ERR_CODE_ALLOC);
    }

    // Init all ants
    for (uint i = 0; i < ant_num; i++) {
        ants[i] = (Ant){
            .pos = init_pos,
            .facing = rand_float(2 * PI),
            .has_food = false
        };
    }

    return ants;
}

/*
 * tick
 * ----
 * Update each ant:
 *
 *  if no food:
 *  - turn towards the closest visible pheromone (forward if none; plus some randomness)
 *  - move that direction
 *  - add to path
 *
 *  if food:
 *  - re-trace path
 *  - drop pheromone
 */
void tick_ants(Ant *ants, uint ant_num, Map *map) {
    // Tick ants
    for (uint i = 0; i < ant_num; i++) {
        Ant *ant = &ants[i];

        if (ant->has_food) {
            // Check if back home
            if (ant->pos.x == map->home.x && ant->pos.y == map->home.y) {
                ant->has_food = false;
            } else {
                // Move towards home
                ant->pos = vector_uint_add(ant->pos, vector_round(vector_float_times_k(
                    unit_vector_int(vector_uint_sub(map->home, ant->pos)), ANT_SPEED
                )));
                
                // Drop pheromone
                map->grid[ant->pos.x][ant->pos.y].pheromone_lvl = ANT_PHEROMONE_MAX;
            }
        } else {
            // TODO: View range
            // Check if food is within range
            uint num_neighbours;
            Vector2_uint *neighbours = neighbour_points(ant->pos, ANT_FOOD_VIEW_RANGE, &num_neighbours);
            for (uint n_i = 0; n_i < num_neighbours; n_i++) {
                Vector2_uint neighbour = neighbours[n_i];

                // Make sure neighbour in bounds
                if (0 <= neighbour.x && neighbour.x < map->width
                    && 0 <= neighbour.y && neighbour.y < map->height) {
                    // Check if there is food
                    if (map->grid[neighbour.x][neighbour.y].food_amount > 0) {
                        ant->pos = vector_uint_add(ant->pos, vector_round(vector_float_times_k(
                            unit_vector_int(vector_uint_sub(neighbour, ant->pos)), ANT_SPEED
                        )));
                        free(neighbours);
                        goto AFTER_MOVE_ANT;
                    }
                }
            }
            free(neighbours);

            // Get direction based on nearby pheromones
            neighbours = neighbour_points(ant->pos, ANT_SMELL_RANGE, &num_neighbours);
            Vector2_int new_dir = (Vector2_int){ 0, 0 };

            uint p_level;
            for (uint n_i = 0; n_i < num_neighbours; n_i++) {
                // new_dir += (pos->neighbour) * (MAX - level)
                Vector2_uint neighbour = neighbours[n_i];

                // Make sure neighbour in bounds
                if (0 <= neighbour.x && neighbour.x < map->width
                    && 0 <= neighbour.y && neighbour.y < map->height) {

                    // Only take into account trails that exist
                    p_level = map->grid[neighbour.x][neighbour.y].pheromone_lvl;
                    if (p_level > 0) {
                        new_dir = vector_int_add(
                            new_dir, vector_int_sub_k(
                                vector_uint_sub(neighbour, ant->pos), ANT_PHEROMONE_MAX - p_level
                            )
                        );
                    }
                }
            }

            free(neighbours);

            // If new_dir = 0, make random
            if (new_dir.x == 0 && new_dir.y == 0) {
                // 0-100 gives enough precision for now...
                new_dir = random_vec_int(100, 100);
            }

            // Set new direction and move
            ant->pos = vector_uint_add(ant->pos, vector_round(vector_float_times_k(
                unit_vector_int(new_dir), ANT_SPEED
            )));

AFTER_MOVE_ANT:
            // Check if out of bounds
            if (ant->pos.x < 0) {
                ant->pos.x = 0;
            } else if (ant->pos.x >= map->width) {
                ant->pos.x = map->width - 1;
            }

            if (ant->pos.y < 0) {
                ant->pos.y = 0;
            } else if (ant->pos.y >= map->height) {
                ant->pos.y = map->height - 1;
            }

            // Check if collided with food
            if (map->grid[ant->pos.x][ant->pos.y].food_amount > 0) {
                // nom nom
                ant->has_food = true;
                map->grid[ant->pos.x][ant->pos.y].food_amount--;
            }
        }
    }
}

/*
 * tick_pheromones
 * ---------------
 * Decrement pheromones.
 */
void tick_pheromones(Map *map) {
    for (uint x = 0; x < map->width; x++) {
        for (uint y = 0; y < map->height; y++) {
            if (map->grid[x][y].pheromone_lvl > 0) {
                map->grid[x][y].pheromone_lvl--;
            }
        }
    }
}

#endif  // ANTS_H
