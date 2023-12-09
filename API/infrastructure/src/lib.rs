pub mod database;
mod model;
mod schema;


//NOTE: Tests are run by default in diffrent threads, since sqlite can support only one db manipulation at the time 
// we have to avoid testing 2 things at once use 
//cargo test -- --test-threads=1

#[test]
fn get_highest_id(){
    use crate::database::Database;

    Database::get_highest_id();

}

#[test]
fn add_to_database_test(){
    use crate::database::Database;
    use data::cordiantes::*;
    use repository::idistresscallrepo::*;

    
    let cordiantes = Cordinates::new_from_decimal(4.32, 4.32);


    Database::create(cordiantes , String::from("xyz"));
}


#[test]
fn find_id(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    let res: i32 =  match Database::get_by_id(Database::get_highest_id()) {
        DistressCallFind::Ok(x) => x.id,
        DistressCallFind::DoesNotExists => -1   
        
    };

    assert_eq!(res, Database::get_highest_id());
}

#[test]
fn find_by_id_non_existing_item(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    let res = Database::get_by_id(-200);

    assert_eq!(res, DistressCallFind::DoesNotExists);
}

#[test]
fn find_by_secret_key(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    match Database::get_by_id(Database::get_highest_id()) {
        DistressCallFind::Ok(x) => {
            let secret_key = x.secret_key.clone();
            match Database::get_by_secret_key(x.secret_key) {
                DistressCallFind::Ok(y) => assert_eq!(secret_key, y.secret_key),
                DistressCallFind::DoesNotExists => panic!("error")  
                
            };
        },
        DistressCallFind::DoesNotExists => panic!("error") 
        
    };



}

#[test]
fn get_all(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    Database::get_all();
}

#[test]
fn update(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    match Database::get_by_id(Database::get_highest_id()) {
        DistressCallFind::Ok(x) => Database::update(x.secret_key, Some(x.call_cordinates), Some(x.details)),
        DistressCallFind::DoesNotExists => panic!("error") 
        
    };
}

#[test]
fn delete(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    match Database::get_by_id(Database::get_highest_id()) {
        DistressCallFind::Ok(x) => Database::delete(x.secret_key),
        DistressCallFind::DoesNotExists => panic!("error") 
        
    };
}

#[test]
fn convert_from_string(){
    use data::cordiantes::Cordinates;
    
    match Cordinates::new_from_string(String::from("123.12 123.21")){
        Ok(_) => println!("working"),
        _ => panic!("failed")
    }


}