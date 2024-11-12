use std::ops::Index;
use rand;

#[derive(Clone)]
/// Represents a single square on the map
pub(crate) struct MapLocation {
    /// The amount of food
    pub food: f32,
    /// The amount of pheromones
    pub pheromone: f32,
    /// The 'difficulty' of travel across this square
    pub travel_cost: f32,
}

impl MapLocation {
    pub(crate) fn new(food: f32, pheromone: f32, travel_cost: f32) -> Self {
        Self { food, pheromone, travel_cost }
    }

    pub(crate) fn empty() -> Self {
        Self { food: 0.0, pheromone: 0.0, travel_cost: 0.0 }
    }
}

/// Represents the whole map
pub(crate) struct Map {
    /// The (x, y) size of the map
    pub dimensions: (usize, usize),
    /// The map itself, indexed as `[x][y]`
    pub map: Vec<Vec<MapLocation>>,
}

impl Map {
    pub(crate) fn new(x: usize, y: usize, food_chance: f32, barrier_chance: f32) -> Result<Self, String> {
        if food_chance < 0.0 || food_chance > 1.0 {
            return Err(format!("food_chance must be in [0, 1] but you passed {food_chance}."))
        }
        if barrier_chance < 0.0 || barrier_chance > 1.0 {
            return Err(format!("barrier_chance must be in [0, 1] but you passed {barrier_chance}."))
        }

        let map = Self::gen_map(x, y, food_chance, barrier_chance);

        Ok(Self {
            dimensions: (x, y),
            map,
        })
    }

    pub(crate) fn gen_map(x: usize, y: usize, food_chance: f32, barrier_chance: f32) -> Vec<Vec<MapLocation>> {
        let mut _map = vec![vec![MapLocation::empty(); y]; x];
        for i in 0..x {
            for j in 0..y {
                _map[i][j].food = if rand::random::<f32>() <= food_chance {
                    1.0
                } else {
                    0.0
                };
                _map[i][j].travel_cost = if rand::random::<f32>() <= barrier_chance {
                    0.2
                } else {
                    0.0
                };
            }
        }

        _map
    }
    
    pub(crate) fn get_neighbours(self, pos: (usize, usize)) -> Vec<Vec<Option<MapLocation>>> {
        let surrounding = vec![vec![None; 3]; 3];
        for x in (pos.0 - 1) .. (pos.0 + 1) {
            for y in (pos.1 - 1) .. (pos.1 + 1) {
                if x < self.dimensions.0 && y < self.dimensions.1 {
                    
                }
            }
        }
        
        surrounding
    }
}

impl Index<(usize, usize)> for Map {
    type Output = MapLocation;

    /// Returns the `MapLocation` at (x, y). Equivalent to `map.map[x][y]`
    fn index(&self, index: (usize, usize)) -> &Self::Output {
        &self.map[index.0][index.1]
    }
}