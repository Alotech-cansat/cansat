
use diesel::sqlite::{SqliteConnection, Sqlite};
use diesel::prelude::*;

use uuid::Uuid;

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
        Uuid::new_v4().to_string()
    }

    pub fn get_highest_id() -> i32{
        let connection = &mut Database::get_connection();

        distress_calls
            .order(id.desc())
            .first::<DataBaseDistressSignal>(connection)
            .expect("error cannot retive highest id").id


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

        return DistressCallCreation::Ok(new_call.secret_key);
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

    fn get_by_secret_key(distress_call_secret_key: String) -> DistressCallFind {
        let connection = &mut Database::get_connection();
    
        let result = distress_calls
            .filter(secret_key.eq(&distress_call_secret_key))
            .first::<DataBaseDistressSignal>(connection);
    
        match result {
            Ok(record) => DistressCallFind::Ok(record.get()),
            Err(x) => {println!("halo {:?}", x); DistressCallFind::DoesNotExists},
        }
    }

    fn get_all() -> Vec<DistressCall>{
        let connection = &mut Database::get_connection();
    
        let result = distress_calls
            .load::<DataBaseDistressSignal>(connection);
            

            match result {
                Ok(record) => record.into_iter().map(|x| {
                        x.get()
                    }).collect(),
                Err(_) => vec![],
            }
    }

    fn delete(distress_call_secret_key:String){
        let connection = &mut Database::get_connection();
        let _ = diesel::delete(distress_calls.filter(secret_key.eq(distress_call_secret_key)))
            .execute(connection);
    }

    fn update(distress_call_secret_key:String, distress_call_cordinates: Cordinates, distress_call_details:String) -> DistressCallCreation{
        let connection = &mut Database::get_connection();
        let string_cordinates = distress_call_cordinates.get_string();

        let res = diesel::update(distress_calls.filter(secret_key.eq(distress_call_secret_key.clone())))
            .set((
                call_cordinates.eq(string_cordinates),
                details.eq(distress_call_details)
            ))
            .execute(connection);

        match res{
            Ok(x) => DistressCallCreation::Ok(distress_call_secret_key),
            _ => DistressCallCreation::FailedToCreate
        }
        
    } // will return the Same SecretKey

}