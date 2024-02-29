use crate::cordiantes::*;
use serde::{Serialize, Deserialize};

#[allow(dead_code)]
#[derive(PartialEq, Debug, Serialize, Deserialize, Clone)]
pub struct DistressCall{
    pub id : i32, // id of a distress call
    pub secret_key: String, // key generated that is neede in order to change data
    pub call_cordinates: Cordinates, // Cordinates of a Distress Call
    pub details:Vec<i64> //details for now String
}