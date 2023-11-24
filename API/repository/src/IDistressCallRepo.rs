
enum DistressCallFind{
    Ok(x),
    DoesNotExists,

}


enum DistressCallCreation{
    Ok(x),
    FailedToCreate,

}

trait IDistressCallRepository{


    pub fn Create(location : Cordinates, Details:String) -> DistressCallCreation; // returns SecretKey

    pub fn GetById(id:int) -> DistressCallFind;

    pub fn GetBySecretKey(SecretKey:String) -> DistressCallFind;

    pub fn GetAll() -> Vec<DistressCall>;

    pub fn Delete(SecretKey:String);

    pub fn Update(SecretKey:String, location: Cordinates, Details:String) -> DistressCallCreation; // will return the Same SecretKey

    

}