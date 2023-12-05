use data::distress_call::DistressCall;
use repository::idistresscallrepo::*;
use infrastructure::database::*;
use rocket::serde::json::Json;
use rocket::http::Status;


#[macro_use] extern crate rocket;


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

#[rocket::main]
async fn main() {
    rocket::build().mount("/", routes![get_by_id, get_by_secret_key]).launch().await.unwrap();
}

