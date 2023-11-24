

struct Cordinates{
    pub latitude: f64,
    pub longitude: f64,

}


impl Cordinates{

    pub fn NewFromDecimal(latitude: f64, longitude:f64) -> Cordinates{
        todo!();
    }

    pub fn NewFromString(latitude: String, longitude:String) -> Cordinates{
        todo!();
    }

    pub fn GetDecimals(self) -> (f64, f64){
        (self.latitude, self.longitude)
    }

    pub fn GetString() -> (String, String){
        todo!();
    }


}