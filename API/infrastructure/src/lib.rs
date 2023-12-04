pub mod database;
mod model;
mod schema;




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

    let res: i32 =  match Database::get_by_id(1) {
        DistressCallFind::Ok(x) => x.id,
        DistressCallFind::DoesNotExists => -1   
        
    };

    assert_eq!(res, 1);
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

    let res: String =  match Database::get_by_secret_key(String::from("secret_key")) {
        DistressCallFind::Ok(x) => x.secret_key,
        DistressCallFind::DoesNotExists => String::from("-1")   
        
    };

    let expected_res = String::from("secret_key");

    assert_eq!(res, expected_res);
}

#[test]
fn get_all(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    Database::get_all();
}