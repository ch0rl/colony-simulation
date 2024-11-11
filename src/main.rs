use crate::map::Map;

mod traits;
mod map;

fn main() {
    let map = Map::new(5, 5, 0.2, 0.1, 1);

    let mut s;
    let mut loc;
    for i in 0..5 {
        s = String::from("");
        for j in 0..5 {
            loc = map[i][j];
            s += format!("{} {} {} ", loc.food, loc.pheromone, loc.travel_cost).as_str();
        }
        println!("{s}");
    }
}
