use diesel::prelude::*;
use data::{distress_call::DistressCall, cordiantes::Cordinates};
use crate::schema::distress_calls::{self, };


#[derive(Queryable, PartialEq, Debug)]
#[diesel(table_name = distress_calls)]
pub struct DataBaseDistressSignal{
    pub id : i32, 
    pub secret_key: String, 
    pub call_cordinates: String, 
    pub details:String 

}

impl DataBaseDistressSignal{

    pub fn get(self) -> DistressCall{

        let cordinates_string = self.call_cordinates;

        let cordiantes = Cordinates::new_from_string(cordinates_string).expect("failed to convert form string");

        DistressCall{
            id:self.id,
            secret_key:self.secret_key,
            call_cordinates: cordiantes,
            details: self.details.split(',').map(|s| s.parse().unwrap()).collect()

        }

    }
}

#[derive(Insertable)]
#[diesel(table_name = distress_calls)]
#[diesel(check_for_backend(diesel::sqlite::Sqlite))]
pub struct NewDistressCall {
    pub secret_key: String,
    pub call_cordinates: String,
    pub details: String,
}

