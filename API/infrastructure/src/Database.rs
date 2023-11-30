use diesel::prelude::*;
use diesel::sqlite::{SqliteConnection, Sqlite};


use data::{distress_call::DistressCall, cordiantes::Cordinates};
use repository::idistresscallrepo::*;


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
#[diesel(table_name = distress_calls)]
pub struct DataBaseDistressSignal{
    id : i32, 
    secret_key: String, 
    call_cordinates: String, 
    details:String 

}

impl DataBaseDistressSignal{

    pub fn get(self) -> DistressCall{
        DistressCall{
            id:self.id,
            secret_key:self.secret_key,
            call_cordinates: Cordinates::new_from_string(self.call_cordinates),
            details: self.details

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

pub struct Database{
}



impl Database{


    pub fn get_connection() -> SqliteConnection{
        SqliteConnection::establish(DATABASE_URL)
            .expect(&format!("Error while connecting to {}", DATABASE_URL))
    }

    pub fn generate_secret_key<'a>(&mut self) -> String{
        //TODO:
        return String::from("secret_key");
    }
}




impl IDistressCallRepository for Database{

    fn create(&mut self,call_cordinates: Cordinates, details: String) -> DistressCallCreation {

        let secret_key = self.generate_secret_key();
        let call_cordinates = call_cordinates.get_string();

        let new_call = NewDistressCall {  secret_key, call_cordinates, details };

        diesel::insert_into(distress_calls::table)
            .values(&new_call)
            .execute(&mut Database::get_connection())
            .expect("Error");

        return DistressCallCreation::Ok(String::from("xyz"));
    }

    fn get_by_id(&mut self, id:i32) -> DistressCallFind{
        use schema::distress_calls::dsl::*;

        let connection = &mut Database::get_connection();

        let result = distress_calls
            .find(id)
            .first::<DataBaseDistressSignal>(connection);

        match result{
            Ok(record) => DistressCallFind::Ok(record.get()),
            Err(_) => DistressCallFind::DoesNotExists
        }
        
    }

    fn get_by_secret_key(secret_key:String) -> DistressCallFind{
        todo!()
    }

    fn get_all() -> Vec<DistressCall>{
        todo!()
    }

    fn delete(secret_key:String){
        todo!()
    }

    fn update(secret_key:String, location: Cordinates, details:String) -> DistressCallCreation{
        todo!()
    } // will return the Same SecretKey

}