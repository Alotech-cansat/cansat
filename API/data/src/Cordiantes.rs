

pub struct Cordinates{
    pub latitude: f64,
    pub longitude: f64,

}


impl Cordinates{

    pub fn new_from_decimal(latitude: f64, longitude:f64) -> Cordinates{
        todo!();
    }

    pub fn new_from_string(latitude: String, longitude:String) -> Cordinates{
        todo!();
    }

    pub fn get_decimals(self) -> (f64, f64){
        (self.latitude, self.longitude)
    }

    pub fn get_string() -> (String, String){
        todo!();
    }


}