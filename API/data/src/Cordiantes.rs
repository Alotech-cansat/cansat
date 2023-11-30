

pub struct Cordinates{
    pub latitude: f64,
    pub longitude: f64,

}


impl Cordinates{

    pub fn new_from_decimal(latitude: f64, longitude:f64) -> Cordinates{
        Cordinates{
            latitude,
            longitude
        }
    }

    pub fn new_from_string(cordinates:String) -> Cordinates{

        //TODO:
        Cordinates{
            longitude:10.0,
            latitude: 10.0
        }
    }

    pub fn get_decimals(self) -> (f64, f64){
        (self.latitude, self.longitude)
    }

    pub fn get_string(self) -> String{

        return format!("{} {}", self.latitude, self.longitude);

       
    }


}