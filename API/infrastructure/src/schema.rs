// @generated automatically by Diesel CLI.

diesel::table! {
    distress_calls (id) {
        id -> Nullable<Integer>,
        secret_key -> Text,
        call_cordinates -> Text,
        details -> Nullable<Text>,
    }
}
