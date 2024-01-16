use serde::{Serialize, Deserialize};


#[derive(PartialEq,PartialOrd, Debug, Serialize, Deserialize, Clone)]
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

    pub fn new_from_string(cordinates:String) -> Result<Cordinates, String>{
        let parts:Vec<&str> = cordinates.split(" ").collect();

        if parts.len() == 2{
            if let (Ok(latitude), Ok(longitude)) = (parts[0].parse(), parts[1].parse()){
                Ok(Cordinates{
                    latitude: latitude,
                    longitude: longitude,
                })      
            }else{
                Err(String::from("failed to convert"))
            }
        }else{
            Err(String::from("failed to convert"))
        }

    }

    pub fn get_decimals(self) -> (f64, f64){
        (self.latitude, self.longitude)
    }

    pub fn get_string(self) -> String{

        return format!("{} {}", self.latitude, self.longitude);

       
    }

    pub fn get_distance(&self, cord: &Cordinates) -> f64{
        f64::sqrt(f64::powf(cord.latitude - self.latitude, 2.0) +  f64::powf(cord.longitude - self.longitude, 2.0))
    }


}
