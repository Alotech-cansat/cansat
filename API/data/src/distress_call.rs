use crate::cordiantes::*;

#[allow(dead_code)]
pub struct DistressCall{
    id : i32, // id of a distress call
    secret_key: String, // key generated that is neede in order to change data
    call_cordinates: Cordinates, // Cordinates of a Distress Call
    details:String //details for now String
}