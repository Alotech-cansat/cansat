
use diesel::sqlite::{SqliteConnection, Sqlite};
use diesel::prelude::*;

use crate::model::*;
use crate::schema::distress_calls;
use crate::schema::distress_calls::dsl::*;

use repository::idistresscallrepo::*;
use data::{distress_call::DistressCall, cordiantes::Cordinates};

const DATABASE_URL: &str = "C:/Users/Staś/Desktop/CANSAT/api/infrastructure/cansat.db";


pub struct Database{}



impl Database{


    pub fn get_connection() -> SqliteConnection{
        SqliteConnection::establish(DATABASE_URL)
            .expect(&format!("Error while connecting to {}", DATABASE_URL))
    }

    pub fn generate_secret_key() -> String{
        //TODO:
        return String::from("secret_key");
    }
}




impl IDistressCallRepository for Database{

    fn create(distress_call_cordinates: Cordinates, distress_call_details: String) -> DistressCallCreation {

        let distress_call_secret_key = Database::generate_secret_key();
        let distress_call_cordinates = distress_call_cordinates.get_string();

        let new_call = NewDistressCall {  
            secret_key:distress_call_secret_key, 
            call_cordinates:distress_call_cordinates, 
            details: distress_call_details };

        diesel::insert_into(distress_calls::table)
            .values(&new_call)
            .execute(&mut Database::get_connection())
            .expect("Error");

        return DistressCallCreation::Ok(String::from("xyz"));
    }

    fn get_by_id(distress_call_id:i32) -> DistressCallFind{
        

        let connection = &mut Database::get_connection();

        let result = distress_calls
            .find(distress_call_id)
            .first::<DataBaseDistressSignal>(connection);

        match result{
            Ok(record) => DistressCallFind::Ok(record.get()),
            Err(_) => DistressCallFind::DoesNotExists
        }
        
    }

    fn get_by_secret_key(distress_call_secret_key:String) -> DistressCallFind{
        todo!()
    }

    fn get_all() -> Vec<DistressCall>{
        todo!()
    }

    fn delete(distress_call_secret_key:String){
        todo!()
    }

    fn update(distress_call_secret_key:String, distress_call_cordinates: Cordinates, distress_call_details:String) -> DistressCallCreation{
        todo!()
    } // will return the Same SecretKey

}