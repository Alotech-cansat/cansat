use data::{distress_call::DistressCall, cordiantes::{Cordinates, self}};

#[derive(PartialEq, Debug)]
pub enum DistressCallFind{
    Ok(DistressCall),
    DoesNotExists,

}


pub enum DistressCallCreation{
    Ok(String),
    FailedToCreate,

}

pub trait IDistressCallRepository{


    fn create(location : Cordinates, details:String) -> DistressCallCreation; // returns SecretKey

    fn get_by_id(id:i32) -> DistressCallFind;

    fn get_by_secret_key(secret_key:String) -> DistressCallFind;

    fn get_all() -> Vec<DistressCall>;

    fn delete(secret_key:String);

    fn update(secret_key:String, location: Option<Cordinates>, details:Option<String>) -> DistressCallCreation; // will return the Same SecretKey

    fn get_closest(cordiantes: Cordinates) -> Result<DistressCall, String>;

}