mod traits;
mod map;
mod sim;
mod ants;
mod structs_enums;

fn main() {
    let map = map::Map::new(1_000, 1_000, 0.2, 0.1).unwrap();
}
