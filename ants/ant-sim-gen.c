/*
 * ant-sim-gen.c
 * -------------
 * Generates data representing the simulation of an ant colony finding food.
 */

#include <stdio.h>
#include <time.h>
#include "ants.h"

int main(int argc, char *argv[]) {
    // TODO: input these values
    uint width = 100;
    uint height = 100;
    uint f_num = 20;
    uint b_num = 0;
    uint seed = time(NULL);
    uint runtime = 500;

    // Tell the user what values we're using
    printf("[Map Variables] size: (%dx%d), f_num: %d, b_num: %d, seed: %d\n",
        width, height, f_num, b_num, seed);

    // Get map
    Map map = gen_map(width, height, f_num, b_num, seed);

    // Get ants
    uint ant_num = 30;
    Ant *ants = make_ants(ant_num, map.home);

    // Output file
    FILE *outfile = fopen("map-state", "w");

    for (uint tick = 0; tick < runtime; tick++) {
        tick_ants(ants, ant_num, &map);
        tick_pheromones(&map);

        // Output
        fprintf(outfile, "Tick %d\n", tick);
        // Map state
        for (uint x = 0; x < width; x++) {
            for (uint y = 0; y < height; y++) {
                fprintf(outfile, "%d,%d ", map.grid[x][y].pheromone_lvl, map.grid[x][y].food_amount);
            }
            fputs("\n", outfile);
        }
        // Ants
        for (uint i = 0; i < ant_num; i++) {
            fprintf(outfile, "%d,%d ", ants[i].pos.x, ants[i].pos.y);
        }
        fputs("\n", outfile);
    }

    free(ants);
    free(map.grid);

    fclose(outfile);
}
