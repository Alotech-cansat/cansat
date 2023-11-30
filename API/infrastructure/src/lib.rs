pub mod Database;



#[test]
fn database_test(){
    use Database::Database;
    let _x = Database::new();
}



#[test]
fn add_to_database_test(){
    use Database::Database;
    use data::cordiantes::*;
    use repository::idistresscallrepo::*;

    let mut x = Database::new();
    let cordiantes = Cordinates::new_from_decimal(4.32, 4.32);


    x.create(cordiantes , String::from("xyz"));
}
