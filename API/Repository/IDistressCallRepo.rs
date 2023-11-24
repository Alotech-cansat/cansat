
enum DistressCallFind{
    Ok(x),
    DoesNotExists,

}


enum DistressCallCreation{
    Ok(x),
    FailedToCreate,

}

trait IDistressCallRepository{


    pub fn Create(location : String, Details:String) -> String; // returns SecretKey

    pub fn GetById(id:int) -> DistressCallFind;

    pub fn GetBySecretKey(SecretKey:String) -> DistressCallFind;



}