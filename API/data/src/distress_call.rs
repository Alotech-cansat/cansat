use crate::cordiantes::*;

#[allow(dead_code)]
pub struct DistressCall{
    pub id : i32, // id of a distress call
    pub secret_key: String, // key generated that is neede in order to change data
    pub call_cordinates: Cordinates, // Cordinates of a Distress Call
    pub details:String //details for now String
}