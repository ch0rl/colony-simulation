# Ant Simulation
A simple simulation of ants finding food.

## Mechanics
Each ant moves randomly until either:
- It can 'see' food - in which case it will move toward it
- It can 'smell' pheromones - in which case it will move according to the sum of all nearby pheromones, multiplied by the maximum value minus their value.
  This means that ants will move vaguely towards the oldest pheromone.

Once an ant reaches 'food', it will return directly 'home', leaving a trail of pheromones as it goes.

## How to Run (from [..](../))
1. Compile the C source: `make ants`
2. Run the generator: `./ant-sim`
3. Run the python 'visualiser': `python ants/show-ants.py`
4. Press `SPACE` to start the replay
5. Consider changing some variables in [ant-sim-gen.c](./ant-sim-gen.c) or [ants.h](./ants.h) (remember to recompile - this will be changed soon).
   If you change the dimensions or number of ants, remember to update [show-ants.py](./show-ants.py) accordingly.

## Known Issues
- Ants move similarly after returning home (with no pheromones to follow)
- Config should be done at runtime, not compile-time
- Ants can see 360 (they shouldn't be able to)
