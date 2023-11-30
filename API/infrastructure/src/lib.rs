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

    let res = Database::get_by_id(1);
}
#[test]
fn find_by_id_non_existing_item(){
    use crate::database::Database;
    use repository::idistresscallrepo::*;

    let res = Database::get_by_id(-200);

    assert_eq!(res, DistressCallFind::DoesNotExists);
}