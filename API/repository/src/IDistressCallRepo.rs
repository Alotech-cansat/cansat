use data::{distress_call::DistressCall, cordiantes::Cordinates};


pub enum DistressCallFind{
    Ok(DistressCall),
    DoesNotExists,

}


pub enum DistressCallCreation{
    Ok(String),
    FailedToCreate,

}

pub trait IDistressCallRepository{


    fn create(&mut self, location : Cordinates, details:String) -> DistressCallCreation; // returns SecretKey

    fn get_by_id(&mut self, id:i32) -> DistressCallFind;

    fn get_by_secret_key(secret_key:String) -> DistressCallFind;

    fn get_all() -> Vec<DistressCall>;

    fn delete(secret_key:String);

    fn update(secret_key:String, location: Cordinates, details:String) -> DistressCallCreation; // will return the Same SecretKey

    

}