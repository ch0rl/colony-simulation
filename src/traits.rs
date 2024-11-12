use crate::map::Map;

/// A model containing creatures to live on the map
pub(crate) trait Model {
    /// The name of the model's species
    fn species_name(&self) -> String;
    /// Move the creatures according to the current `map_state`
    fn move_creatures(&mut self, map_state: &mut Map);
}