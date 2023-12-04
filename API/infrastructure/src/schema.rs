// @generated automatically by Diesel CLI.

diesel::table! {
    distress_calls (id) {
        id -> Integer,
        secret_key -> Text,
        call_cordinates -> Text,
        details -> Text,
    }
}
