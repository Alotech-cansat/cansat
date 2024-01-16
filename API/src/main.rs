use data::{distress_call::DistressCall, cordiantes::Cordinates};
use repository::idistresscallrepo::*;
use infrastructure::database::*;
use rocket::serde::json::Json;
use rocket::http::Status;


#[macro_use] extern crate rocket;


#[get("/get_closest/<cordinates>")]
fn get_closest(cordinates:String) -> Result<Json<DistressCall>, Status>{
    let cord = match Cordinates::new_from_string(cordinates){
        Ok(x) => x,
        Err(x) => {
            println!("{:?}", x);
            return  Err(Status::NotAcceptable)}
    };

    match Database::get_closest(cord){
        Ok(x) => return Ok(Json(x)),
        _ => Err(Status::NotAcceptable)
    }
}

#[get("/get_by_id/<id>")]
fn get_by_id(id:i32) -> Result<Json<DistressCall>, Status> {
    
    match Database::get_by_id(id){
        DistressCallFind::Ok(x) => return Ok(Json(x)),
        _ => Err(Status::NotAcceptable)
    }
}

#[get("/get_by_secret_key/<secret_key>")]
fn get_by_secret_key(secret_key:String) -> Result<Json<DistressCall>, Status> {
    
    match Database::get_by_secret_key(secret_key){
        DistressCallFind::Ok(x) => return Ok(Json(x)),
        _ => Err(Status::NotAcceptable)
    }
}


#[get("/new_distress_call/<cordinates>/<details>")]
fn create(cordinates:String, details:String) -> Result<String, Status> {
    let cord = match Cordinates::new_from_string(cordinates){
        Ok(x) => x,
        Err(x) => {
            println!("{:?}", x);
            return  Err(Status::NotAcceptable)}
    };

    match Database::create(cord, details){
        DistressCallCreation::Ok(x) => return Ok(x),
        _ => Err(Status::NotAcceptable)
    }
}


#[get("/delete/<secret_key>")]
fn delete(secret_key:String) -> String {
    let key = secret_key.clone();

    Database::delete(secret_key);
    return format!{"deleted distress call with secret_key {:?}", key};
    
}

#[get("/")]
fn get_all() -> Json<Vec<DistressCall>> {

    Json(Database::get_all())


    
}


#[get("/update/<secret_key>?<cordinates>&<details>")]
fn update(secret_key:String, cordinates:Option<String>, details:Option<String>) -> Result<String, Status> {
    
    let cords:Option<Cordinates> = match cordinates{
        Some(x) => match Cordinates::new_from_string(x){
            Ok(y) => Some(y),
            Err(_) => return Err(Status::NotAcceptable)

        },
        None => None
    };

    match Database::update(secret_key, cords, details){
        DistressCallCreation::Ok(x) => Ok(x),
        DistressCallCreation::FailedToCreate => Err(Status::BadRequest),
    }



    
}





#[rocket::main]
async fn main() {
    rocket::build().mount("/", routes![get_by_id, get_by_secret_key, create, delete, get_all, update, get_closest] ).launch().await.unwrap();
}

