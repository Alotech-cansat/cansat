
use std::cmp::Ordering;

use diesel::sqlite::SqliteConnection;
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

    fn get_closest(cordinates: Cordinates) -> Result<DistressCall, String>{
        let mut distress_calls_vec = Database::get_all();
        
        distress_calls_vec.sort_by(|a, b| {
            let distance_a = a.call_cordinates.get_distance(&cordinates);
            let distance_b = b.call_cordinates.get_distance(&cordinates);
    
            distance_a.partial_cmp(&distance_b).unwrap_or(Ordering::Equal)
        });

    match distress_calls_vec.get(0).cloned(){
        Some(x) => Ok(x),
        None => Err(String::from("empty db"))

    }


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

    fn update(distress_call_secret_key:String, distress_call_cordinates: Option<Cordinates>, distress_call_details:Option<String>) -> DistressCallCreation{
        let connection = &mut Database::get_connection();
        let mut succes = 0;

        match distress_call_cordinates{
            Some(x) => {
                let string_cordinates = x.get_string();
                let res = diesel::update(distress_calls.filter(secret_key.eq(distress_call_secret_key.clone())))
                    .set(call_cordinates.eq(string_cordinates))
                    .execute(connection);
                match res{
                    Ok(_) => {succes += 1}
                    _ => {}
                }
            },
            _ => {succes+=1;}
        }

        match distress_call_details{
            Some(x) => {
                let res = diesel::update(distress_calls.filter(secret_key.eq(distress_call_secret_key.clone())))
                .set(details.eq(x))
                .execute(connection);

                match res{
                    Ok(_) => {succes += 1}
                    _ => {}
                }
            },
            _ => {succes+=1}
        }
        

        if succes == 2{
            DistressCallCreation::Ok(distress_call_secret_key)}
            else
        {
            DistressCallCreation::FailedToCreate
        }
        
    } // will return the Same SecretKey

}