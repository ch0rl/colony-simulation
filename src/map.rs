use rand;

pub(crate) struct MapLocation {
    food: f32,
    pheromone: f32,
    travel_cost: f32,
}

impl MapLocation {
    pub(crate) fn new(food: f32, pheromone: f32, travel_cost: f32) -> Self {
        Self { food, pheromone, travel_cost }
    }
}

pub(crate) struct Map {
    dimensions: (usize, usize),
    map: Vec<Vec<MapLocation>>,
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
        let _map = vec!();
        for i in 0..x {
            _map[i] = vec!();
            for j in 0..y {
                _map[i][j] = MapLocation::new(
                    if rand::random() >= food_chance {
                        1.0
                    } else {
                        0.0
                    },
                    0.0,
                    if rand::random() >= barrier_chance {
                        1.0
                    } else {
                        0.0
                    },
                )
            }
        }

        _map
    }
}