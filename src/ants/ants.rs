use crate::map::Map;

struct Ant {
    /// The (x, y) position of the ant
    pos: (usize, usize),
    /// The direction that the ant is facing
    facing: crate::structs_enums::CARDINAL,
}

impl Ant {
    pub fn new(pos: (usize, usize), facing: crate::structs_enums::CARDINAL) -> Self {
        Self { pos, facing }
    }
}

struct Ants {
    ants: Vec<Ant>,
}

impl crate::traits::Model for Ants {
    fn species_name(&self) -> String {
        String::from("Ants")
    }

    fn move_creatures(&mut self, map_state: &mut Map) {
        for ant in &self.ants {
            
        }
    }
}