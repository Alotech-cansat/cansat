-- Your SQL goes here
CREATE TABLE distress_calls (
    id INTEGER PRIMARY KEY NOT NULL,
    secret_key TEXT NOT NULL,
    call_cordinates TEXT NOT NULL,
    details TEXT NOT NULL
);