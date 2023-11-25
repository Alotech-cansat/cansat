use diesel::prelude::*;
use diesel::sqlite::SqliteConnection;

use data::distress_call::*;
use repository::*;

const DATABASE_URL: &str = "C:/Users/Staś/Desktop/CANSAT/api/infrastructure/cansat.db";


mod schema {
    diesel::table! {
        distress_calls {
            id -> Integer,
            secret_key -> Text,
            call_cordinates -> Text,
            details -> Text,

        }
    }
}

use schema::distress_calls;

#[derive(Queryable, PartialEq, Debug)]
pub struct DataBaseDistressSignal{
    id : i32, 
    secret_key: String, 
    call_cordinates: String, 
    details:String 

}

#[derive(Insertable)]
#[diesel(table_name = distress_calls)]
pub struct NewDistressCall<'a> {
    pub secret_key: &'a str,
    pub call_cordinates: &'a str,
    pub details: &'a str,
}

pub struct Database{

    connection: SqliteConnection,
    next_id:i32
}



impl Database{
    pub fn new() -> Self{
        let connection = SqliteConnection::establish(DATABASE_URL)
            .expect(&format!("Error while connecting to {}", DATABASE_URL));

        Self{
            connection: connection,
            next_id:0

        }

    }

    pub fn add_distress_call(&mut self, secret_key: &str,call_cordinates: & str, details: & str,){

        let new_call = NewDistressCall {  secret_key, call_cordinates, details };

        diesel::insert_into(distress_calls::table)
            .values(&new_call)
            .execute(&mut self.connection)
            .expect("Error");
    }
}

/* 
impl IDistressCallRepository for Database{

    
}*/